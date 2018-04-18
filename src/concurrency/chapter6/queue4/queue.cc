//
// C++ concurrency in Action.
//

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <iostream>

template <typename T>
class queue {
private:
  struct node {
    T data;
    std::unique_ptr<node> next;
    explicit node(T value) : data(std::move(value)) {}
  };

  // why head is smart_pointer, tail is raw pointer?
  // for automatic memory management?
  std::unique_ptr<node> head;
  node *tail = nullptr;

public:
  queue() = default;
  queue(const queue &) = delete;
  queue &operator=(const queue &) = delete;

  std::shared_ptr<T> try_pop() {
    if (!head) {
      return nullptr;
    }
    std::shared_ptr<T> res(std::make_shared<T>(std::move(head->data)));
    // Is it works?
    head = std::move(head->next);  // seems work
    return res;
  }

  void push(T data) {
    std::unique_ptr<node> p(new node(std::move(data)));
    const auto new_tail = p.get();
    if (head) {
      tail->next = std::move(p);
    } else {
      head = std::move(p);
    }
    tail = new_tail;
  }
};

struct Test {
  int data;
  Test(int i) : data(i) {}
  ~Test() {
    std::cout << "Test: " << data << std::endl;
  }
};

void func() {
  // test
  std::unique_ptr<Test> u1(new Test(1));
  std::unique_ptr<Test> u2(new Test(2));

  // move-assignment cause Test(1) destruct advanced
  u1 = std::move(u2);
  std::cout << std::endl;
}

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
