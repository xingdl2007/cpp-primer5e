//
// C++ concurrency in Action.
//

#include <algorithm>
#include <future>
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <random>

template <typename T>
class thread_safe_stack {
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  thread_safe_stack() = default;

  // copy-ctor, important to held source lock across copy
  thread_safe_stack(const thread_safe_stack &other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }
  thread_safe_stack &operator=(const thread_safe_stack &) = delete;

  // move semantic
  void push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      return nullptr;
    }
    // if T support move-ctor
    std::shared_ptr<T> res = std::make_shared<T>(std::move(data.top()));
    data.pop();
    return res;
  }

  bool pop(T &value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      return false;
    }
    // if T support move-assignment
    value = std::move(data.top);
    data.pop();
    return true;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

template <typename T>
struct misc {
  struct chunk_to_sort {
    std::list<T> data;
    std::promise<std::list<T>> promise;
  };

  thread_safe_stack<chunk_to_sort> chunks;
  std::mutex m;
  std::vector<std::thread> threads;
  unsigned const max_thread_count{std::thread::hardware_concurrency() - 1};
  std::atomic<bool> end_of_data{false};

  misc() = default;

  ~misc() {
    end_of_data = true;
    for (unsigned i = 0; i < threads.size(); ++i) {
      threads[i].join();
    }
  }

  std::list<T> do_sort(std::list<T> &chunk_data) {
    if (chunk_data.empty()) {
      return chunk_data;
    }

    std::list<T> result;
    result.splice(result.begin(), chunk_data, chunk_data.begin());
    T const &partition_val = *result.begin();

    typename std::list<T>::iterator divide_point =
        std::partition(chunk_data.begin(), chunk_data.end(),
                       [&](T const &val) { return val < partition_val; });
    chunk_to_sort new_lower_chunk;
    new_lower_chunk.data.splice(new_lower_chunk.data.end(),
                                chunk_data, chunk_data.begin(),
                                divide_point);

    std::future<std::list<T>> new_lower = new_lower_chunk.promise.get_future();
    // move semantic
    chunks.push(std::move(new_lower_chunk));
    {
      std::lock_guard<std::mutex> lock(m);
      if (threads.size() < max_thread_count) {
        threads.push_back(std::thread(&misc<T>::sort_thread, this));
      }
    }

    std::list<T> new_higher(do_sort(chunk_data));
    result.splice(result.end(), new_higher);
    while (new_lower.wait_for(std::chrono::seconds(0)) !=
        std::future_status::ready) {
      try_sort_chunk();
    }

    result.splice(result.begin(), new_lower.get());
    return result;
  }

  void sort_chunk(std::shared_ptr<chunk_to_sort> const &chunk) {
    chunk->promise.set_value(do_sort(chunk->data));
  }

  void try_sort_chunk() {
    std::shared_ptr<chunk_to_sort> chunk = chunks.pop();
    if (chunk) {
      sort_chunk(chunk);
    }
  }

  void sort_thread() {
    while (!end_of_data) {
      try_sort_chunk();
      std::this_thread::yield();
    }
  }
};

template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  misc<T> s;
  return s.do_sort(input);
}

int main() {
  std::list<int> list1;
  std::default_random_engine e;
  std::uniform_int_distribution<int> d(0, 100);
  for (int i = 0; i < 1000; ++i) {
    list1.push_back(d(e));
  }

  parallel_quick_sort(list1);
}
