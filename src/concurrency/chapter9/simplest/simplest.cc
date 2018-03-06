//
// C++ concurrency in Action.
//

#include <atomic>
#include <algorithm>
#include <condition_variable>
#include <functional>
#include <thread>
#include <vector>
#include <mutex>
#include <iostream>

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

// thread-safe version based std::mutex and std::condition_variable
template <typename T>
class thread_safe_queue {
private:
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };
  std::mutex head_mutex;
  // smart pointer for automatic memory management(node)
  std::unique_ptr<node> head;

  std::mutex tail_mutex;
  node *tail = nullptr;
  std::condition_variable data_cond;

  // helper function
  node *get_tail() {
    std::lock_guard<std::mutex> lock(tail_mutex);
    return tail;
  }

  // should be called when holding head lock
  std::unique_ptr<node> pop_head() {
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return old_head;
  }

  // make sure queue is not empty, or it will block
  std::unique_lock<std::mutex> wait_for_data() {
    std::unique_lock<std::mutex> lock(head_mutex);
    data_cond.wait(lock, [this]() { return head.get() != get_tail(); });
    return std::move(lock);
  }

  // blocked pop helper function
  // move ownership of lock
  std::unique_ptr<node> wait_pop_head() {
    std::unique_lock<std::mutex> lock(wait_for_data());
    return pop_head();
  }
  std::unique_ptr<node> wait_pop_head(T &value) {
    std::unique_lock<std::mutex> lock(wait_for_data());
    value = std::move(*head->data);
    return pop_head();
  }

  // non-blocked helper function
  std::unique_ptr<node> try_pop_head() {
    std::unique_lock<std::mutex> lock(head_mutex);
    if (head.get() == get_tail()) {
      return nullptr;
    }
    return pop_head();
  }
  std::unique_ptr<node> try_pop_head(T &value) {
    std::unique_lock<std::mutex> lock(head_mutex);
    if (head.get() == get_tail()) {
      return nullptr;
    }
    value = std::move(*head->data);
    return pop_head();
  }

public:
  thread_safe_queue() : head(new node), tail(head.get()) {};
  thread_safe_queue(const thread_safe_queue &) = delete;
  thread_safe_queue &operator=(const thread_safe_queue &) = delete;

  void push(T data) {
    std::shared_ptr<T> new_data = std::make_shared<T>(std::move(data));
    std::unique_ptr<node> p(new node);
    node *const new_tail = p.get();
    {
      std::lock_guard<std::mutex> lock(tail_mutex);
      tail->data = new_data;
      tail->next = std::move(p);
      tail = new_tail;
    }
    data_cond.notify_one();
  }

  bool empty() {
    std::unique_lock<std::mutex> lock(head_mutex);
    return head.get() == get_tail();
  }

  // non-blocked pop
  std::shared_ptr<T> try_pop() {
    auto old_head = try_pop_head();
    return old_head ? old_head->data : nullptr;
  }
  bool try_pop(T &value) {
    auto old_head = try_pop_head(value);
    return old_head != nullptr;
  }

  // blocked pop
  std::shared_ptr<T> wait_and_pop() {
    auto old_head = wait_pop_head();
    return old_head->data;
  }
  void wait_and_pop(T &value) {
    auto old_head = wait_pop_head(value);
  }
};

// For many purposes such a simple thread pool will suffice,
// especially if the tasks are entirely independent and
// don’t return any values or perform any blocking operations.
class thread_pool {
  // Note that the order of declaration of the members is important !!
  std::atomic_bool done;
  thread_safe_queue<std::function<void()>> work_queue;
  std::vector<std::thread> threads;
  join_threads joiner;

  void worker_thread() {
    while (!done) {
      std::function<void()> task;
      if (work_queue.try_pop(task)) {
        task();
      } else {
        std::this_thread::yield();
      }
    }
  }
public:
  // ctor
  thread_pool() : done(false), joiner(threads) {
    unsigned const thread_count = std::thread::hardware_concurrency();
    try {
      for (unsigned i = 0; i < thread_count; ++i) {
        threads.emplace_back(&thread_pool::worker_thread, this);
      }
    }
    catch (...) {
      done = true;
      throw;
    }
  }

  // dtor
  ~thread_pool() {
    done = true;
  }

  template <typename FunctionType>
  void submit(FunctionType f) {
    work_queue.push(std::function<void()>(f));
  }
};

int main() {
  std::atomic<int> value{0};
  thread_pool pool;
  for (int i = 0; i < 2000; i++) {
    pool.submit([&]() {
      ++value;
    });
  }
  // 50ms delay to make sure all work has done (because of no waiting mechanism)
  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::cout << value << std::endl;
  return 0;
}
