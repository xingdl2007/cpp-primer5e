//
// C++ concurrency in Action.
//

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <iostream>
#include <thread>

template <typename T>
class threadsafe_queue {
private:
  mutable std::mutex m;
  std::queue<T> data;
  std::condition_variable cond;

public:
  threadsafe_queue() = default;
  threadsafe_queue(const threadsafe_queue &_other) {
    std::lock_guard<std::mutex> lock(_other.m);
    data = _other.data;
  }
  threadsafe_queue &operator=(
      const threadsafe_queue &) = delete; // Disallow assignment for simplicity

  void push(T new_value) {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
    cond.notify_one();
  }

  bool try_pop(T &value) {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      return false;
    }
    value = data.front();    // T must support assignment
    data.pop();
    return true;
  }
  std::shared_ptr<T> try_pop() {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) {
      return nullptr;
    }
    std::shared_ptr<T> ret = std::make_shared<T>(data.front()); // T must support copy/move
    data.pop();
    return ret;
  }

  void wait_and_pop(T &value) {
    std::unique_lock<std::mutex> lock(m);
    cond.wait(lock, [this]() { return !data.empty(); });
    value = data.front();    // T must support assignment
    data.pop();
  }

  std::shared_ptr<T> wait_and_pop() {
    std::unique_lock<std::mutex> lock(m);
    cond.wait(lock, [this]() { return !data.empty(); });
    std::shared_ptr<T> ret = std::make_shared<T>(data.front()); // T must support copy/move
    data.pop();
    return ret;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

// prepare data
void worker1(threadsafe_queue<int> &queue) {
  std::uniform_int_distribution<int> dis(0, 100);
  std::default_random_engine e;
  while (true) {
    queue.push(dis(e));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

// processing
void worker2(threadsafe_queue<int> &queue) {
  int value;
  while (true) {
    queue.wait_and_pop(value);
    std::cout << value << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

int main() {
  threadsafe_queue<int> queue;

  std::thread t1(worker1, std::ref(queue));
  std::thread t2(worker2, std::ref(queue));
  std::thread t3(worker2, std::ref(queue));

  t1.join();
  t2.join();
  t3.join();

  return 0;
}