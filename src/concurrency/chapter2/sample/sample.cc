//
// C++ concurrency in Action.
//

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// RAII idiom, make sure exception safety
class thread_guard {
public:
  explicit thread_guard(std::thread &t_) : t(t_) {}
  ~thread_guard() {
    if (t.joinable()) {
      t.join();
    }
  }
  thread_guard(const thread_guard &) = delete;
  thread_guard &operator=(const thread_guard &) = delete;
private:
  std::thread &t;
};

// because std::thread is movable
class scoped_guard {
  std::thread t;
public:
  explicit scoped_guard(std::thread t_) : t(std::move(t_)) {
    if (!t.joinable()) {
      throw std::logic_error("No thread");
    }
  }
  ~scoped_guard() {
    t.join();
  }
  scoped_guard(const scoped_guard &) = delete;
  scoped_guard &operator=(const scoped_guard &)= delete;
};

void hello(const std::string &s) {
  std::cout << "Hello " << s << " World" << std::endl;
}

void smart(std::unique_ptr<int> ptr) {
  (*ptr) += 100;
  cout << *ptr << endl;
}

void work(int id) {
  cout << "work " << id << ends;
}

int main() {
  // a hint: how many thread can truly run concurrently;
  cout << std::thread::hardware_concurrency() << endl;

  // but not perfect, need named std::thread object
  std::thread t(hello, "concurrency");
  thread_guard g(t);

  // smart pointer and scoped_guard, better solution
  scoped_guard s(std::thread(smart, std::make_unique<int>(42)));

  // vector of thread
  vector<std::thread> pool;
  for (int i = 0; i < 10; ++i) {
    pool.emplace_back(std::thread(work, i));
  }
  for_each(pool.begin(), pool.end(), std::mem_fn(&std::thread::join));
}
