//
// C++ concurrency in Action.
//

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <atomic>

std::atomic_flag lock = ATOMIC_FLAG_INIT;

void f(int n) {
  for (int cnt = 0; cnt < 1; ++cnt) {
    while (lock.test_and_set(std::memory_order_acquire))  // acquire lock
      ; // spin
    std::cout << "Output from thread " << n << '\n';
    lock.clear(std::memory_order_release);               // release lock
  }
}

class spinlock_mutex {
private:
  std::atomic_flag flag;
public:
  spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}
  void lock() {
    while (flag.test_and_set(std::memory_order_acquire));
  }
  void unlock() {
    flag.clear(std::memory_order_release);
  }
};

int main() {
  std::vector<std::thread> v;
  for (int n = 0; n < 10; ++n) {
    v.emplace_back(f, n);
  }
  for (auto &t : v) {
    t.join();
  }

  // example usage of self-defined mutex
  spinlock_mutex m;
  std::lock_guard<spinlock_mutex> lock(m);

  // b = true, will return true
  std::atomic<bool> b(false);
  if (b = true) {
    std::cout << "Oops" << std::endl;
  }
}
