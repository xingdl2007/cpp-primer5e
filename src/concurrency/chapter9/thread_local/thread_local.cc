//
// C++ concurrency in Action.
//

#include <atomic>
#include <algorithm>
#include <condition_variable>
#include <functional>
#include <numeric>
#include <thread>
#include <random>
#include <list>
#include <string>
#include <queue>
#include <future>
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

// std::packaged_task<> instances are not copyable, just movable,
// you can no longer use std::function<>.
// for the queue entries, because std::function<> requires that
// the stored function objects are copy-constructible.
// This is a simple type-erasure class with a function call operator.
class function_wrapper {
  struct impl_base {
    virtual void call() = 0;
    virtual ~impl_base() = default;
  };
  template <typename F>
  struct impl_type : impl_base {
    F f;
    // forward is necessary
    explicit impl_type(F &&f_) : f(std::forward<F>(f_)) {}
    void call() override { f(); }
  };

  std::unique_ptr<impl_base> impl;
public:
  function_wrapper() = default;
  template <typename F>
  function_wrapper(F &&f):
      impl(new impl_type<F>(std::forward<F>(f))) {}

  // functor
  void operator()() { impl->call(); }

  // movable
  function_wrapper(function_wrapper &&other) noexcept :
      impl(std::move(other.impl)) {}
  function_wrapper &operator=(function_wrapper &&other) noexcept {
    impl = std::move(other.impl);
    return *this;
  }

  // disable copy
  function_wrapper(const function_wrapper &) = delete;
  function_wrapper(function_wrapper &) = delete;
  function_wrapper &operator=(const function_wrapper &)= delete;
};

class thread_pool {
// Note that the order of declaration of the members is important !!
  std::atomic_bool done;
  thread_safe_queue<function_wrapper> pool_work_queue;

  typedef std::queue<function_wrapper> local_queue_type;
  // 1. When used with thread_local, static is implied in block-scope
  // 2. Within a class definition, a member shall not be declared with the
  // thread_local storage-class-specifier unless also declared static

  // from cpp reference:
  // The thread_local keyword is only allowed for objects declared at namespace scope,
  // objects declared at block scope, and static data members. It indicates that the
  // object has thread storage duration. It can be combined with static or extern to
  // specify internal or external linkage (except for static data members which always
  // have external linkage), respectively, but that additional static doesn't affect
  // the storage duration.

  /*
   * When you write an implementation file (.cpp, .cxx, etc) your compiler generates a translation unit.
   * This is the object file from your implementation file plus all the headers you #included in it.
   *
   * Internal linkage refers to everything only in scope of a translation unit.
   *
   * External linkage refers to things that exist beyond a particular translation unit.
   *
   * In other words, accessible through the whole program, which is the combination of all
   * translation units (or object files).
   */
  // why static? declaring
  static thread_local std::unique_ptr<local_queue_type> local_work_queue;

  std::vector<std::thread> threads;
  join_threads joiner;

  void worker_thread() {
    local_work_queue.reset(new local_queue_type);
    while (!done) {
      run_pending_task();
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

  void run_pending_task() {
    function_wrapper task;
    if (local_work_queue && !local_work_queue->empty()) {
      task = std::move(local_work_queue->front());
      local_work_queue->pop();
      task();
    } else if (pool_work_queue.try_pop(task)) {
      task();
    } else {
      std::this_thread::yield();
    }
  }

  template <typename FunctionType>
  std::future<typename std::result_of<FunctionType()>::type>
  submit(FunctionType f) {
    typedef typename std::result_of<FunctionType()>::type result_type;

    std::packaged_task<result_type()> task(std::move(f));
    std::future<result_type> res(task.get_future());

    // packaged_task is movable, implicit convert to function_wrapper
    if (local_work_queue) {
      local_work_queue->push(std::move(task));
    } else {
      pool_work_queue.push(std::move(task));
    }
    return res;
  }
};

// defining is necessary
thread_local std::unique_ptr<thread_pool::local_queue_type> thread_pool::local_work_queue;

template <typename T>
struct sorter {
  thread_pool pool;
  std::list<T> do_sort(std::list<T> &chunk_data) {
    if (chunk_data.empty()) {
      return chunk_data;
    }
    std::list<T> result;
    result.splice(result.begin(), chunk_data, chunk_data.begin());
    T const &partition_val = *result.begin();

    typename std::list<T>::iterator divide_point =
        std::partition(
            chunk_data.begin(), chunk_data.end(),
            [&](T const &val) { return val < partition_val; });

    std::list<T> new_lower_chunk;
    new_lower_chunk.splice(new_lower_chunk.end(),
                           chunk_data, chunk_data.begin(),
                           divide_point);

    std::future<std::list<T> > new_lower =
        pool.submit(
            std::bind(
                &sorter::do_sort, this,
                std::move(new_lower_chunk))); // make sure the data is moved rather than copied

    std::list<T> new_higher(do_sort(chunk_data));
    result.splice(result.end(), new_higher);

    // if new_lower is not ready, instead of block waiting
    // do something useful
    while (new_lower.wait_for(std::chrono::seconds(0)) !=
        std::future_status::ready) {
      pool.run_pending_task();
    }

    // stick low/high part together
    result.splice(result.begin(), new_lower.get());
    return result;
  }
};

template <typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
  if (input.empty()) {
    return input;
  }
  sorter<T> s;
  return s.do_sort(input);
}

int main() {
  std::list<int> ls;
  // if too much element in ls, will throw EXC_BAD_ACCESS with g++ 7.2 (macOS 10.13.3)
  // but ok with g++ 5.4 (Ubuntu 16.04)
  for (int i = 200; i > 0; --i) {
    ls.push_back(i);
  }
  auto sorted = parallel_quick_sort(ls);
  std::for_each(sorted.begin(), sorted.end(), [](int i) { std::cout << i << " "; });
  std::cout << std::endl;
}
