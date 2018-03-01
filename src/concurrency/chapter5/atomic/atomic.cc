//
// C++ concurrency in Action.
//

#include <thread>
#include <atomic>
#include <iostream>

std::atomic<unsigned> count;

void worker1() {
  while (true) {
    ++count;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

void worker2() {
  while (true) {
    std::cout << count.load() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int main() {
  std::thread t1(worker1);
  std::thread t2(worker2);

  t1.join();
  t2.join();
}
