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
#include <vector>
#include <deque>
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
  thread_safe_queue<function_wrapper> work_queue;
  std::vector<std::thread> threads;
  join_threads joiner;

  void worker_thread() {
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
    if (work_queue.try_pop(task)) {
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
    work_queue.push(std::move(task));
    return res;
  }
};

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
  std::default_random_engine e(time(nullptr));
  std::uniform_int_distribution<int> d(0, 100);
  for (int i = 0; i < 10; ++i) {
    ls.push_back(d(e));
  }
  auto sorted = parallel_quick_sort(ls);
  std::for_each(sorted.begin(), sorted.end(), [](int i) { std::cout << i << " "; });
  std::cout << std::endl;
}
