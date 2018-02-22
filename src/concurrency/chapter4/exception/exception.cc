#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
#include <exception>
#include <cmath>

double sqrt_root(int x) {
  if (x < 0) {
    throw std::out_of_range("x < 0");
  }
  return std::sqrt(x);
}

int main() {
  std::future<double> res = std::async(sqrt_root, -1);
  std::cout << res.get() << std::endl;
}
