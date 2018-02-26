//
// C++ concurrency in Action.
//

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <random>
#include <iostream>

// thread-safe version
template <typename T>
class queue {
private:
  struct node {
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;
  };
  std::mutex head_mutex;
  std::unique_ptr<node> head;

  std::mutex tail_mutex;
  node *tail = nullptr;
  std::condition_variable data_cond;

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
  queue() : head(new node), tail(head.get()) {};
  queue(const queue &) = delete;
  queue &operator=(const queue &) = delete;

  std::shared_ptr<T> try_pop() {
    auto old_head = try_pop_head();
    return old_head ? old_head->data : nullptr;
  }

  bool try_pop(T &value) {
    auto old_head = try_pop_head(value);
    return old_head != nullptr;
  }

  bool empty() {
    std::unique_lock<std::mutex> lock(head_mutex);
    return head.get() == get_tail();
  }

  std::shared_ptr<T> wait_and_pop() {
    auto old_head = wait_pop_head();
    return old_head->data;
  }

  void wait_and_pop(T &value) {
    auto old_head = wait_pop_head(value);
  }

  // all-in-one solution
//  std::shared_ptr<T> wait_and_pop() {
//    std::unique_lock<std::mutex> lock(head_mutex);
//    std::unique_ptr<node> old_head;
//    data_cond.wait(lock, [&, this]() {
//      if (head.get() == get_tail()) {
//        return false;
//      }
//      old_head = std::move(head);
//      head = std::move(old_head->next);
//      return true;
//    });
//    return old_head->data;
//  }

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
};

int main() {
  queue<std::string> q;
  q.push(std::string("hello"));
  std::cout << *q.try_pop() << std::endl;
  q.push(std::string("c++"));
  std::cout << *q.try_pop() << std::endl;
  q.push(std::string("concurrency"));
  q.push(std::string("world"));

  std::cout << *q.try_pop() << std::endl;
  std::cout << *q.try_pop() << std::endl;
  return 0;
}
