#include <mutex>
#include <iostream>
#include <thread>

struct Some {};
Some &init() {
  static Some s;
  return s;
}

void worker() {
  Some &s = init();
  // address
  std::cout << &s << std::endl;
}

// static Some's initialization in init() is thread-safe
int main() {
  std::thread t1(worker);
  std::thread t2(worker);

  t1.join();
  t2.join();

  // another method

}
