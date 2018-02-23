//
// C++ concurrency in Action.
//

#include <future>
#include <iostream>

int calculate() {
  return 100;
}

int main() {
  // simulate background calculation
  std::future<int> res = std::async(calculate);
  std::cout << "std::async: " << res.get() << std::endl;
  return 0;
}