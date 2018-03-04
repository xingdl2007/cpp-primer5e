//
// C++ concurrency in Action.
//

#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <iostream>

struct empty_stack : std::exception {
  const char *what() const throw() override {
    return "empty stack.";
  }
};

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

  void push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }
    std::shared_ptr<T> res = std::make_shared<T>(data.top());
    data.pop();
    return res;
  }

  void pop(T &value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }
    value = data.top;
    data.pop();
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

// cout is not thread safe, so output will interleaved
template <typename T>
void worker(thread_safe_stack<T> &stack) {
  int count = 0;
  try {
    while (true) {
      stack.pop();
      count++;
    }
  } catch (empty_stack) {
    std::cout << "thread #" << std::this_thread::get_id() << " pop "
              << std::dec << count << " values" << std::endl;
  }
}

void waiting(std::thread &t) {
  if (t.joinable()) {
    t.join();
  }
}

int main() {
  thread_safe_stack<int> stack;
  for (int i = 0; i < 1000; ++i) {
    stack.push(i);
  }
  std::thread t1(worker<int>, std::ref(stack));
  std::thread t2(worker<int>, std::ref(stack));
  std::thread t3(worker<int>, std::ref(stack));

  t1.join();
  t2.join();
  t3.join();
}
