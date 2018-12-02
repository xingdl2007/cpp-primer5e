#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>
#include <functional>
#include <streambuf>

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

class BindTest
{
public:
  BindTest() = default;

  template <typename T>
  void Output(T t)
  {
    std::cout << t << std::endl;
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

  std::map<std::string, int> test_map = {{"hello", 1}};
  auto *p = &test_map;
  std::cout << (*p)["hello"] << std::endl;

  std::string name("world");
  name.reserve(name.size() + 5);
  name.append("hello");

  char arry[] = {'a', 'b', 'c'};
  std::string name2(arry, sizeof(arry));

  std::cout << name2 << std::endl;

  BindTest bt;
  std::function<void(int)> f = std::bind(&BindTest::Output<int>, bt, std::placeholders::_1);
  f(2);

  std::function<void(std::string)> g = std::bind(&BindTest::Output<std::string>, bt, std::placeholders::_1);
  g("2");

  {
    // exchange underling streambuffer
    std::ostringstream oss;
    std::streambuf *former_buff = std::clog.rdbuf(oss.rdbuf());
    std::clog << "This will apperar in oss" << std::flush;
    std::cout << "in_avail: " << oss.rdbuf()->in_avail() << std::endl;
    std::cout << oss.str() << '\n';
    std::clog.rdbuf(former_buff);
  }

  {
    std::ostringstream oss;
    oss << "Hello, world!\n";
    oss << 123;
    std::string s = oss.str();
    std::cout << s << std::endl;
  }

  return 0;
}