//
// Created by xing on 7/4/18.
//

#include <thread>
#include <future>
#include <iostream>
#include <chrono>

using namespace std;

// think: global_flag is volatile or not ? what is the difference

// if global_flag is not volatile-qualified
// you can see the difference with -O2 and -O0:
// -O2 optimized out reading of global_flag, counter thread will
// not loop forever.
// -O0 does not optimize out reading of global_falg

// what if global_flag is volatile-qualified ?

bool global_flag = true;

int main() {
  auto result = std::async(std::launch::async, []() {
    int counter = 0;
    while (global_flag) {
      counter++;
    }
    return counter;
  });

  // do some work
  auto start = std::chrono::high_resolution_clock::now();
  std::this_thread::sleep_for(1ms);
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "Waited " << elapsed.count() << " ms\n";

  global_flag = false;
  cout << result.get() << endl;
}