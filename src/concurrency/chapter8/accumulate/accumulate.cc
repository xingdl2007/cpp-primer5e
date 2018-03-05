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

using namespace std;

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

// exception-safe version
template <typename Iterator, typename T>
struct accumulate_block {
  T operator()(Iterator first, Iterator last) {
    return std::accumulate(first, last, T());
  }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  long const length = std::distance(first, last);

  if (length <= 0)
    return init;

  unsigned long const min_per_thread = 25;
  unsigned long const max_threads =
      (length + min_per_thread - 1)/min_per_thread;

  unsigned long const hardware_threads =
      std::thread::hardware_concurrency();

  unsigned long const num_threads =
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

  unsigned long const block_size = length/num_threads;

  std::vector<std::future<T> > futures(num_threads - 1);
  std::vector<std::thread> threads(num_threads - 1);
  // just for cleanup when exception happens between the first worker thread and join
  join_threads joiner(threads);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    std::packaged_task<T(Iterator, Iterator)> task{accumulate_block<Iterator, T>()};
    futures[i] = task.get_future();
    threads[i] = std::thread(std::move(task), block_start, block_end);
    block_start = block_end;
  }
  T last_result = accumulate_block<Iterator, T>()(block_start, last);
  T result = init;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
    result += futures[i].get();
  }
  result += last_result;
  return result;
}

// second version with std::async
template <typename Iterator, typename T>
T parallel_accumulate2(Iterator first, Iterator last, T init) {
  unsigned long const length = std::distance(first, last);
  unsigned long const max_chunk_size = 25;
  if (length <= max_chunk_size) {
    return std::accumulate(first, last, init);
  } else {
    Iterator mid_point = first;
    std::advance(mid_point, length/2);
    std::future<T> first_half_result =
        std::async(parallel_accumulate<Iterator, T>,
                   first, mid_point, init);
    T second_half_result = parallel_accumulate(mid_point, last, T());
    return first_half_result.get() + second_half_result;
  }
}

int main() {
  vector<int> ivec;
  // second since epoch
  // cout << time(0) << endl;
  default_random_engine e(time(0));
  uniform_int_distribution<int> u(0, 100);
  for (int i = 0; i < 10000; ++i) {
    ivec.push_back(u(e));
  }
  // version 1
  cout << parallel_accumulate(ivec.begin(), ivec.end(), 0) << endl;

  // version 2
  cout << parallel_accumulate2(ivec.begin(), ivec.end(), 0) << endl;

  cout << std::this_thread::get_id() << endl;
  return 0;
}
