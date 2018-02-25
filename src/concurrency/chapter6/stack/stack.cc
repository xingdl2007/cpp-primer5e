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
class threadsafe_stack {
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  threadsafe_stack() = default;

  // copy-ctor, important to held source lock across copy
  threadsafe_stack(const threadsafe_stack &other) {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }
  threadsafe_stack &operator=(const threadsafe_stack &) = delete;

  void push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
  }

  std::shared_ptr<T> pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }
    // if T support move-ctor
    std::shared_ptr<T> res = std::make_shared<T>(std::move(data.top()));
    data.pop();
    return res;
  }

  void pop(T &value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      throw empty_stack();
    }
    // if T support move-assignment
    value = std::move(data.top);
    data.pop();
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

// cout is not thread safe, so output will interleaved
template <typename T>
void worker(threadsafe_stack<T> &stack) {
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

int main() {
  threadsafe_stack<int> stack;
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
