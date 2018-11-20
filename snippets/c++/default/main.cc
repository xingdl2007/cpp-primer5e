#include <iostream>
#include <memory>

// virtual function default value is tricky and may not be what you want
// so be careful
class Base
{
public:
  virtual void somefunction(int a, int b, int c = -10)
  {
    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
  }
};

class Derived : public Base
{
public:
  virtual void somefunction(int a, int b, int c = 10) override
  {
    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
  }
};

// output
// a: 1 b: 2 c: 3
// a: 4 b: 5 c: -10
// a: 1 b: 2 c: 3
// a: 4 b: 5 c: 10
int main()
{
  Base b;
  b.somefunction(1, 2, 3);
  b.somefunction(4, 5);

  Derived d;
  d.somefunction(1, 2, 3);
  d.somefunction(4, 5);

  std::shared_ptr<int> a(new int(100));
  std::cout << *a << std::endl;
  std::cout << sizeof(a) << std::endl;
  return 0;
}
