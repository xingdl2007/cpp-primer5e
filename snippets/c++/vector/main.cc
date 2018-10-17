#include <chrono>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "usage: vector counter" << std::endl;
    return 1;
  }

  std::vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << ivec.size() << " " << ivec.capacity() << std::endl;

  // clear will not shrink space
  ivec.clear();
  std::cout << ivec.size() << " " << ivec.capacity() << std::endl;

  // shrink will free space
  ivec.shrink_to_fit();
  std::cout << ivec.size() << " " << ivec.capacity() << std::endl;

  int counter = atoi(argv[1]);

  std::chrono::steady_clock::time_point start =
      std::chrono::steady_clock::now();
  for (int i = 0; i < counter; ++i) {
    auto ptr = new std::vector<int>;
    delete ptr;
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  auto cnt = std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                 .count();
  std::cout << cnt << " us.\n";
}
