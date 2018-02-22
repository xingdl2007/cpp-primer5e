#include <mutex>
#include <iostream>

struct Some {};
Some *s;
std::once_flag flag;

void init() {
  s = new Some();
}

void worker() {
  std::call_once(flag, init);
  // same address
  std::cout << s << std::endl;
}

// init() will only be called once
int main() {
  std::thread t1(worker);
  std::thread t2(worker);

  t1.join();
  t2.join();
}
