#include <iostream>

// #1
void g(double) { std::cout << "void g(double);" << std::endl; }

template <typename T>
void f() {
  g(1);
}

// #2
void g(int) { std::cout << "void g(int);" << std::endl; }

// output: void g(double);
int main() { f<int>(); }
