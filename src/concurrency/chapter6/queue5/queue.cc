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

  node *get_tail() {
    std::lock_guard<std::mutex> lock(tail_mutex);
    return tail;
  }

  std::unique_ptr<node> pop_head() {
    std::lock_guard<std::mutex> lock(head_mutex);
    if (head.get() == get_tail()) {
      return nullptr;
    }
    std::unique_ptr<node> old_head = std::move(head);
    head = std::move(old_head->next);
    return old_head;
  }

public:
  queue() : head(new node), tail(head.get()) {};
  queue(const queue &) = delete;
  queue &operator=(const queue &) = delete;

  std::shared_ptr<T> try_pop() {
    auto old_head = pop_head();
    return old_head ? old_head->data : nullptr;
  }

  void push(T data) {
    std::shared_ptr<T> new_data = std::make_shared<T>(std::move(data));
    std::unique_ptr<node> p(new node);
    node *const new_tail = p.get();

    std::lock_guard<std::mutex> lock(tail_mutex);
    tail->data = new_data;
    tail->next = std::move(p);
    tail = new_tail;
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
