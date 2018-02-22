#include <mutex>
#include <iostream>

struct Box {
  explicit Box(int num) : num_things{num} {}

  int num_things;
  std::mutex m;
};

// a good example of unique_lock
void transfer(Box &from, Box &to, int num) {
  // don't actually take the locks yet
  std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
  std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

  // lock both unique_locks without deadlock
  std::lock(lock1, lock2);

  from.num_things -= num;
  to.num_things += num;

  // 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' dtors
}

void transfer2(Box &from, Box &to, int num) {
  // lock both mutexes without deadlock
  std::lock(from.m, to.m);

  // already locks
  std::lock_guard<std::mutex> lock1(from.m, std::adopt_lock);
  std::lock_guard<std::mutex> lock2(to.m, std::adopt_lock);

  from.num_things -= num;
  to.num_things += num;

  // 'from.m' and 'to.m' mutexes unlocked in 'lock_guard' dtors
}

int main() {
  Box acc1(100);
  Box acc2(50);
  std::cout << acc1.num_things << ", " << acc2.num_things << std::endl;

  std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
  std::thread t2(transfer2, std::ref(acc2), std::ref(acc1), 5);

  t1.join();
  t2.join();

  std::cout << acc1.num_things << ", " << acc2.num_things << std::endl;
}
