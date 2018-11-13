#include <assert.h>
#include <chrono>
#include <iostream>
#include <thread>

// compiler option is interesting: use -pthread option
int main()
{
  std::thread::id id = std::this_thread::get_id();

  assert(id != std::thread::id());

  // thread::id of a non-executing thread
  std::cout << std::thread::id() << std::endl;
  std::cout << id << std::endl;
}
