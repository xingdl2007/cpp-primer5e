//
// C++ concurrency in Action.
//

#include <algorithm>
#include <functional>
#include <future>
#include <numeric>
#include <vector>
#include <random>
#include <thread>
#include <iostream>
#include <iterator>

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

// very interesting, hand-by-hand
template <typename Iterator>
void parallel_partial_sum(Iterator first, Iterator last) {
  typedef typename Iterator::value_type value_type;
  struct process_chunk {
    void operator()(Iterator begin, Iterator last,   // last is inclusive
                    std::future<value_type> *previous_end_value,
                    std::promise<value_type> *end_value) {
      try {
        Iterator end = last;
        ++end;
        std::partial_sum(begin, end, begin);
        if (previous_end_value) {
          const value_type &addend = previous_end_value->get();
          *last += addend;
          if (end_value) {
            end_value->set_value(*last);
          }
          std::for_each(begin, last, [&](value_type &item) {
            item += addend;
          });
        } else if (end_value) {
          end_value->set_value(*last);
        }
      }
      catch (...) {
        if (end_value) {
          end_value->set_exception(std::current_exception());
        } else {
          // just rethrow, because we are running on the main thread
          throw;
        }
      }
    }
  };

  unsigned long const length = std::distance(first, last);

  if (!length) {
    return;
  }

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1)/min_per_thread;

  unsigned long const hardware_threads =
      std::thread::hardware_concurrency();

  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length/num_threads;

  typedef typename Iterator::value_type value_type;

  std::vector<std::thread> threads(num_threads - 1);
  std::vector<std::promise<value_type> > end_values(num_threads - 1);
  std::vector<std::future<value_type> > previous_end_values;
  previous_end_values.reserve(num_threads - 1);
  join_threads joiner(threads);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_last = block_start;
    std::advance(block_last, block_size - 1);
    threads[i] = std::thread(process_chunk(),
                             block_start, block_last,
                             (i != 0) ? &previous_end_values[i - 1] : 0,
                             &end_values[i]);
    block_start = block_last;
    ++block_start;
    previous_end_values.push_back(end_values[i].get_future());
  }
  Iterator final_element = block_start;
  std::advance(final_element, std::distance(block_start, last) - 1);
  process_chunk()(block_start, final_element,
                  (num_threads > 1) ? &previous_end_values.back() : 0,
                  0);
}

// try it with std::async, seems work
// the downside of this approach is that function signature is different with std::partial_sum
// parallel version must return the last value of the range
// another downside compared with textbook implementation is thread have to wait before
// previous block done which is a major weakness (because of synchronization between threads)
template <typename Iterator>
auto partial_sum(Iterator first, Iterator last) -> typename Iterator::value_type {
  typedef typename Iterator::value_type value_type;
  unsigned long length = std::distance(first, last);
  if (length < 25) {
    std::partial_sum(first, last, first);
    return *(--last);
  } else {
    Iterator mid = first + length/2;
    std::future<value_type> second_half =
        std::async(&partial_sum<Iterator>, mid, last);
    value_type end_value = partial_sum<Iterator>(first, mid);
    // exception-safe
    second_half.get();
    std::for_each(mid, last, [&](value_type &item) {
      item += end_value;
    });
    return *(--last);
  }
};

// incremental pairwise version
class barrier {
  std::atomic<unsigned> count;
  std::atomic<unsigned> spaces;
  std::atomic<unsigned> generation;
public:
  explicit barrier(unsigned count_) :
      count(count_), spaces(count_), generation(0) {}
  void wait() {
    unsigned const my_generation = generation;
    if (!--spaces) {
      spaces = count.load();
      ++generation;
    } else {
      while (generation == my_generation)
        std::this_thread::yield();
    }
  }
  void done_waiting() {
    --count;
    if (!--spaces) {
      spaces = count.load();
      ++generation;
    }
  }
};

// barrier usage
template <typename Iterator>
void parallel_partial_sum2(Iterator first, Iterator last) {
  typedef typename Iterator::value_type value_type;
  struct process_element {
    void operator()(Iterator first, Iterator last,
                    std::vector<value_type> &buffer,
                    unsigned i, barrier &b) {
      value_type &ith_element = *(first + i);
      for (unsigned step = 0, stride = 1; stride <= i; ++step, stride *= 2) {
        value_type const &source = (step%2) ? buffer[i] : ith_element;
        value_type &dest = (step%2) ? ith_element : buffer[i];

        value_type const &addend = (step%2) ? buffer[i - stride] : *(first + i - stride);
        dest = source + addend;
        b.wait();
      }

      // buffer[i] should be the last value, other thread my use
      if (ith_element < buffer[i]) {
        ith_element = buffer[i];
      } else {
        buffer[i] = ith_element;
      }
      b.done_waiting();
    }
  };

  unsigned long const length = std::distance(first, last);
  if (length <= 1) {
    return;
  }
  std::vector<value_type> buffer(length);
  barrier b(length);
  std::vector<std::thread> threads(length - 1);
  std::vector<std::future<void>> results(length - 1);  // useless
  join_threads joiner(threads);

  for (unsigned long i = 0; i < (length - 1); ++i) {
    std::packaged_task<void(unsigned long)> task(
        [&](unsigned long i) {
          process_element()(first, last, buffer, i, b);
        });
    results[i] = task.get_future();
    threads[i] = std::thread(std::move(task), i);
  }
  process_element()(first, last, buffer, length - 1, b);
}

using namespace std;

int main() {
  vector<int> vec;
  for (int i = 0; i < 20; ++i) {
    vec.push_back(i + 1);
  }

  auto ivec = vec;
  std::partial_sum(vec.begin(), vec.end(), vec.begin());

  // textbook implementation have bugs!
  parallel_partial_sum2(ivec.begin(), ivec.end());

  // check
  if (vec != ivec) {
    std::cout << "fail" << std::endl;
  } else {
    std::cout << "pass" << std::endl;
  }
  return 0;
}
