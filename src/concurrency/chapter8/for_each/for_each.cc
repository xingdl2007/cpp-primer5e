//
// C++ concurrency in Action.
//

#include <algorithm>
#include <functional>
#include <future>
#include <numeric>
#include <vector>
#include <random>

#include <iostream>

namespace ccia {
// simple version with std::async
template <class Iterator, class Function>
void for_each(Iterator first, Iterator last, Function f) {
  unsigned long const length = std::distance(first, last);
  unsigned int const max_size = 25;
  if (length <= max_size) {
    std::for_each(first, last, f);
  } else {
    Iterator mid = first + length/2;
    // first half
    std::future<void> second_half = std::async(ccia::for_each<Iterator, Function>, mid, last, f);
    // second half
    ccia::for_each(first, mid, f);
    second_half.get();
  }
};

class join_threads {
private:
  std::vector<std::thread> &threads;
public:
  explicit join_threads(std::vector<std::thread> &threads_) : threads(threads_) {}
  ~join_threads() {
    for (auto &t:threads) {
      if (t.joinable()) {
        t.join();
      }
    }
  }
};

// simple implementation with std::packaged_task and std::future
template <typename Iterator, typename Function>
void for_each2(Iterator first, Iterator last, Function f) {
  unsigned const length = std::distance(first, last);
  unsigned const min_size_per_thread = 25;
  unsigned max_threads = (length + min_size_per_thread - 1)/min_size_per_thread;
  unsigned hardware_threads = std::thread::hardware_concurrency();
  unsigned thread_cnt = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  std::vector<std::thread> threads(thread_cnt - 1);
  join_threads joiner(threads);

  // no result for for_each
  std::vector<std::future<void>> results(thread_cnt - 1);
  Iterator block_start = first;
  unsigned block_size = length/thread_cnt;
  for (unsigned i = 0; i < thread_cnt - 1; ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    std::packaged_task<void(Iterator, Iterator, Function)> task{std::for_each<Iterator, Function>};
    results[i] = task.get_future();
    threads[i] = std::thread(std::move(task), block_start, block_end, f);
    block_start = block_end;
  }
  std::for_each(block_start, last, f);
  for (unsigned i = 0; i < thread_cnt - 1; ++i) {
    results[i].get();
  }
};

// textbook version
template <typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f) {
  unsigned long const length = std::distance(first, last);

  if (!length)
    return;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1)/min_per_thread;

  unsigned long const hardware_threads =
      std::thread::hardware_concurrency();

  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length/num_threads;

  std::vector<std::future<void> > futures(num_threads - 1);
  std::vector<std::thread> threads(num_threads - 1);
  join_threads joiner(threads);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    std::packaged_task<void(void)> task(
        [=]() {
          std::for_each(block_start, block_end, f);
        });
    futures[i] = task.get_future();
    threads[i] = std::thread(std::move(task));
    block_start = block_end;
  }
  std::for_each(block_start, last, f);
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    futures[i].get();
  }
}
} // namespace ccia

int main() {
  std::vector<int> ivec;
  for (int i = 0; i < 100; ++i) {
    ivec.push_back(i + 1);
  }
  ccia::for_each(ivec.begin(), ivec.end(), [](int &i) { i *= 2; });
  ccia::for_each2(ivec.begin(), ivec.end(), [](int &i) { i *= 2; });
  ccia::parallel_for_each(ivec.begin(), ivec.end(), [](int &i) { i /= 2; });
  ccia::for_each(ivec.begin(), ivec.end(), [](int &i) { i /= 2; });

  // printer
  std::for_each(ivec.begin(), ivec.end(), [](int i) { std::cout << i << " "; });
  std::cout << std::endl;
  return 0;
}
