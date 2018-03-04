//
// C++ concurrency in Action.
//

#include <atomic>
#include <algorithm>
#include <vector>
#include <thread>
#include <functional>
#include <iostream>

std::atomic<unsigned long> counter(0);
void loop() {
  while (counter.fetch_add(1, std::memory_order_relaxed) < 10000000) {
    // do nothing
  }
}

void loop2() {
  unsigned long counter = 0;
  for (int i = 0; i < 10000000; ++i) {
    ++counter;
  }
}

int main() {
  std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < std::thread::hardware_concurrency(); ++i) {
    threads.push_back(std::thread(loop));
  }
  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "multi-thread: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms.\n";

  // compare with single-thread version
  start = std::chrono::high_resolution_clock::now();
  loop2();
  end = std::chrono::high_resolution_clock::now();
  std::cout << "single-thread: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
            << " ms.\n";
}
