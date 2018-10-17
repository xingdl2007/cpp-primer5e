#include <iostream>

class Base {
public:
  virtual void somefunction(int a, int b, int c = 0) {
    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
  }
};

class Derived : public Base {
public:
  virtual void somefunction(int a, int b, int c = 0) override {
    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
  }
};

int main() {
  Base b;
  b.somefunction(1, 2, 3);
  b.somefunction(4, 5);

  Derived d;
  d.somefunction(1, 2, 3);
  d.somefunction(4, 5);
  return 0;
}
