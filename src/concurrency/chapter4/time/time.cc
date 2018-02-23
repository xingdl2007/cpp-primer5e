//
// C++ concurrency in Action.
//

#include <chrono>
#include <iostream>
#include <thread>

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  std::chrono::duration<double, std::milli> d = std::chrono::high_resolution_clock::now() - start;
  std::cout << d.count() << " ms" << std::endl;
}
