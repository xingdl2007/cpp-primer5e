//
// C++ concurrency in Action.
//

#include <future>
#include <iostream>
#include <cassert>

void do_work(std::promise<int> barrier) {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  barrier.set_value(100);
}

int main() {
  std::promise<int> promise;
  std::future<int> future(promise.get_future());

  // simulate background calculation
  std::thread t(do_work, std::move(promise));

  future.wait();
  assert(future.valid());
  std::cout << future.get() << std::endl;
  assert(!future.valid());

  t.join();
  return 0;
}