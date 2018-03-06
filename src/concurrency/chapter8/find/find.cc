//
// C++ concurrency in Action.
//

#include <algorithm>
#include <functional>
#include <future>
#include <numeric>
#include <thread>
#include <vector>
#include <random>

#include <iostream>

// simple guard
class join_threads {
  std::vector<std::thread> &threads;
public:
  explicit join_threads(std::vector<std::thread> &threads_) :
      threads(threads_) {}
  ~join_threads() {
    for (auto &t:threads) {
      if (t.joinable()) {
        t.join();
      }
    }
  }
};

// interesting: notification with atomic<bool> flag
template <typename Iterator, typename MatchType>
Iterator parallel_find(Iterator first, Iterator last, MatchType match) {
  struct find_element {
    void operator()(Iterator begin, Iterator end,
                    MatchType match,
                    std::promise<Iterator> *result,
                    std::atomic<bool> *done_flag) {
      try {
        for (; (begin != end) && !done_flag->load(); ++begin) {
          if (*begin == match) {
            // set promise before flag
            result->set_value(begin);
            done_flag->store(true);
            return;
          }
        }
      }
      catch (...) {
        try {
          // set promise before flag
          result->set_exception(std::current_exception());
          done_flag->store(true);
        }
        catch (...) {
          // discard exception when setting promise
          // which can happen when another thread has already set promise
        }
      }
    }
  };

  unsigned long const length = std::distance(first, last);

  if (!length)
    return last;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1)/min_per_thread;

  unsigned long const hardware_threads =
      std::thread::hardware_concurrency();

  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length/num_threads;

  std::promise<Iterator> result;
  std::atomic<bool> done_flag(false);
  std::vector<std::thread> threads(num_threads - 1);
  {
    join_threads joiner(threads);

    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i) {
      Iterator block_end = block_start;
      std::advance(block_end, block_size);
      threads[i] = std::thread(find_element(),
                               block_start, block_end, match,
                               &result, &done_flag);
      block_start = block_end;
    }
    find_element()(block_start, last, match, &result, &done_flag);
    // all spawned threads joins here
  }
  // not found, return last
  if (!done_flag.load()) {
    return last;
  }
  // rethrow exception if any
  return result.get_future().get();
}

// another version
template <typename Iterator, typename MatchType>
Iterator parallel_find_impl(Iterator first, Iterator last, MatchType match,
                            std::atomic<bool> &done) {
  // take care of the try-catch block which in order to set done flag for quit
  // if omit try-catch, still correct, but not in an timely fashion
  try {
    unsigned long const length = std::distance(first, last);
    unsigned long const min_per_thread = 25;
    if (length < (2*min_per_thread)) {
      for (; (first != last) && !done.load(); ++first) {
        if (*first == match) {
          done = true;
          return first;
        }
      }
      return last;
    } else {
      Iterator const mid_point = first + (length/2);
      // the destructor will wait for possible another thread to complete, so no thread leak
      std::future<Iterator> async_result =
          std::async(&parallel_find_impl<Iterator, MatchType>,
                     mid_point, last, match, std::ref(done));
      Iterator const direct_result =
          parallel_find_impl(first, mid_point, match, done);
      return (direct_result == mid_point) ?
             async_result.get() : direct_result;
    }
  }
  catch (...) {
    done = true;
    throw;
  }
}

template <typename Iterator, typename MatchType>
Iterator parallel_find2(Iterator first, Iterator last, MatchType match) {
  std::atomic<bool> done(false);
  return parallel_find_impl(first, last, match, done);
}

using namespace std;

int main() {
  vector<int> ivec;
  for (int i = 0; i < 100; ++i) {
    ivec.push_back(i);
  }

  // version 1
  auto res = parallel_find(ivec.begin(), ivec.end(), 89);
  if (res == ivec.end()) {
    cout << "not found" << endl;
  } else {
    cout << "found" << endl;
  }

  // version 2
  res = parallel_find2(ivec.begin(), ivec.end(), 101);
  if (res == ivec.end()) {
    cout << "not found" << endl;
  } else {
    cout << "found" << endl;
  }
  return 0;
}
