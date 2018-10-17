#include <assert.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include "pool.h"

// think: is this usage pattern good?
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "usage: pool counter size" << std::endl;
    return 1;
  }

  SmartObjectPool<int> pool;
  pool.add(std::unique_ptr<int>(new int(42)));
  assert(pool.size() == 1);
  {
    auto obj = pool.acquire();
    assert(pool.size() == 0);
    assert(*obj == 42);
    *obj = 1337;
  }
  assert(pool.size() == 1);

  auto obj = pool.acquire();
  assert(*obj == 1337);

  int counter = atoi(argv[1]);
  int size = atoi(argv[2]);
  {
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i < counter; ++i) {
      auto ptr = new std::vector<int>;
      ptr->reserve(2000000);
      for (int i = 0; i < size; ++i) {
        ptr->push_back(i);
      }
      delete ptr;
    }
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    auto cnt =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    std::cout << "newd: " << cnt << " us.\n";
  }

  {
    SmartObjectPool<std::vector<int>> vec_pool;
    for (int i = 0; i < 10; ++i) {
      auto ptr = new std::vector<int>();
      ptr->reserve(2000000);
      vec_pool.add(std::unique_ptr<std::vector<int>>(ptr));
    }

    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    for (int i = 0; i < counter; ++i) {
      auto vec = vec_pool.acquire();
      for (int i = 0; i < size; ++i) {
        vec->push_back(i);
      }
      vec->clear();
    }
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    auto cnt =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count();
    std::cout << "pool: " << cnt << " us.\n";
  }
}
