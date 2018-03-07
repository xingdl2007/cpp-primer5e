//
// C++ concurrency in Action.
//

#include <memory>
#include <queue>
#include <iostream>
#include <thread>
#include <future>
#include <cassert>

template <typename T>
class threadsafe_queue {
private:
  mutable std::mutex m;
  std::queue<T> data;
  std::condition_variable cond;

public:
  threadsafe_queue() = default;
  threadsafe_queue(const threadsafe_queue &_other) {
    std::lock_guard<std::mutex> lock2(_other.m);
    data = _other.data;
  }
  threadsafe_queue &operator=(
      const threadsafe_queue &) = delete; // Disallow assignment for simplicity

  void push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
    cond.notify_one();
  }

  bool try_pop(T &value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      return false;
    }
    value = std::move(data.front());    // T must support assignment
    data.pop();
    return true;
  }
  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      return nullptr;
    }
    std::shared_ptr<T> ret = std::make_shared<T>(std::move(data.front())); // T must support copy/move
    data.pop();
    return ret;
  }

  void wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lock(m);
    cond.wait(lock, [this]() { return !data.empty(); });
    value = std::move(data.front());    // T must support assignment
    data.pop();
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lock(m);
    cond.wait(lock, [this]() { return !data.empty(); });
    std::shared_ptr<T> ret = std::make_shared<T>(std::move(data.front())); // T must support copy/move
    data.pop();
    return ret;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

void test_concurrent_push_and_pop_on_empty_queue() {
  threadsafe_queue<int> q;

  std::promise<void> go, push_ready, pop_ready;
  std::shared_future<void> ready(go.get_future());

  std::future<void> push_done;
  std::future<int> pop_done;

  try {
    push_done = std::async(std::launch::async,
                           [&q, ready, &push_ready]() {
                             push_ready.set_value();
                             ready.wait();
                             q.push(42);
                           }
    );
    pop_done = std::async(std::launch::async,
                          [&q, ready, &pop_ready]() {
                            pop_ready.set_value();
                            ready.wait();
                            return *q.wait_and_pop();
                          }
    );
    push_ready.get_future().wait();
    pop_ready.get_future().wait();
    go.set_value();

    push_done.get();
    assert(pop_done.get() == 42);
    assert(q.empty());
  }
  catch (...) {
    go.set_value();
    throw;
  }
}

int main() {
  test_concurrent_push_and_pop_on_empty_queue();
}