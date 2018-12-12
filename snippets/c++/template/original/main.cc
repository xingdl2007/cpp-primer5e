#include <cstring>
#include <iostream>
#include <type_traits>
#include "class.h"
#include "stack.h"

using namespace std;

template <typename T>
T val{};
void print_val() { std::cout << val<long> << std::endl; }

int ii = 2;
template <decltype(auto) N>
class C {};

template <typename T1, typename T2, typename T3>
void foo(int a1[7], int a2[], int (&a3)[42], int (&x0)[], T1 x1, T2& x2,
         T3&& x3) {
  MyClass<decltype(a1)>::print();
  MyClass<decltype(a2)>::print();
  MyClass<decltype(a3)>::print();
  MyClass<decltype(x0)>::print();
  MyClass<decltype(x1)>::print();
  MyClass<decltype(x2)>::print();
  MyClass<decltype(x3)>::print();
}

class TestData {
 public:
  TestData(std::string const&) {}
};

template <typename T>
struct ValueWithComment {
  T value;
  std::string comment;
};

ValueWithComment(double)->ValueWithComment<double>;
ValueWithComment(char const*, char const*)->ValueWithComment<std::string>;

// necessary
void print() {}

template <typename T, typename... Types>
void print(T firstArg, Types... args) {
  std::cout << firstArg << '\n';
  if (sizeof...(args) > 0) {
    print(args...);
  }
}

// #1
template <typename T>
void g(T t) {
  std::cout << "void g(T t);" << std::endl;
}
void g(double) { std::cout << "void g(double);" << std::endl; }

template <typename T>
void f() {
  g(1);
}

// #2
void g(int) { std::cout << "void g(int);" << std::endl; }

class Temp {
 public:
  Temp() = default;
  Temp(int d) : data(d) {}
  ~Temp() { std::cout << "~Temp: " << data << std::endl; }
  Temp& operator=(Temp const& rhs) {
    data = rhs.data;
    return *this;
  }

 private:
  friend bool operator<(Temp const&, Temp const&);
  friend ostream& operator<<(ostream& os, Temp const&);
  int data;
};
bool operator<(Temp const& lhs, Temp const& rhs) { return lhs.data < rhs.data; }

ostream& operator<<(ostream& os, Temp const& t) {
  os << "Temp<<: " << t.data;
  return os;
}
Temp factory(int d) { return Temp(d); }

class N {
 public:
  N() = default;
  N(int d) : data(d) {}
  N(N const&) = delete;
  N(N&&) = delete;
  void test() {}

 private:
  friend bool operator<(N const&, N const&);
  int data = 1;
};

bool operator<(N const& lhs, N const& rhs) { return lhs.data < rhs.data; }

N make_n() { return N{}; }

int& lvalue();
int&& xvalue();
int prvalue();

// you can pass N to max, but return error occurs
// so as parameter, T is not to be copyable, but as return type
// T must be copyable
template <typename T>
auto SimpleMax(T a, T b) {
  return b < a ? a : b;
}

template <typename T>
auto ComplexMax(T&& a, T&& b) {
  return b < a ? a : b;
}

template <typename T1, typename T2,
          typename RT = std::decay_t<decltype(true ? T1() : T2())>>
RT ComplexMax2(T1&& a, T2&& b) {
  return b < a ? a : b;
}

// call-by-reference
template <typename T>
T const& max(T const& a, T const& b) {
  std::cout << "template 1" << std::endl;
  return b < a ? a : b;
}

// can't understand why the warnning
// call-by-value
char const* max(char const* a, char const* b) {
  std::cout << "template 2" << std::endl;
  printf("a: %p\n", a);
  printf("b: %p\n", b);
  return std::strcmp(b, a) < 0 ? a : b;
}

// call-by-reference: return a reference
template <typename T>
T const& max(T const& a, T const& b, T const& c) {
  std::cout << "template 3" << std::endl;
  return ::max(::max(a, b), c);
}

// output: void g(double);
int main() {
  f<int>();
  auto t = factory(1);

  factory(100);

  // class rvalue can occur on the left-hand-side of assignments
  // such assignments are actually function calls to the appropriate
  // assignment operator of the class rather than 'simple' assignment
  // for scalar types, so they follow the (separate) rules of member
  // function calls.
  factory(100) = t;

  // c++17/c++2a is ok, even N is neither copyable nor movable
  auto n = make_n();
  make_n().test();

  std::cout << "is_same():" << std::is_same<decltype(lvalue()), int&>()
            << std::endl;
  std::cout << "is_same():" << std::is_same<decltype(xvalue()), int&&>()
            << std::endl;
  std::cout << "is_same():" << std::is_same<decltype(prvalue()), int>()
            << std::endl;

  static_assert(sizeof(int) < 10, "int too small");

  // m1 is int type, is a local variable, the the temporaries
  // (7, 42, 68) are created for the arguments, but those temporaries
  // are created in main() where they persist until the statement
  // is done.
  auto m1 = ::max(7, 42, 68);
  printf("m1: %p\n", &m1);
  std::cout << m1 << std::endl;

  char const* s1 = "frederic";
  char const* s2 = "anica";
  char const* s3 = "lucas";

  // there is a problem, m2 is a reference to a local variable
  // created by max(const char*, const char*), should use -O3 to
  // see the effect
  // m2 is a referece to a 'const char *'
  // this problem is very subtle
  // auto m2 = ::max(s1, s2, s3);
  // printf("m2: %p\n", m2);
  // std::cout << m2 << std::endl;  // garbage

  printf("s1: %p\n", s1);
  printf("s2: %p\n", s2);
  printf("s3: %p\n", s3);

  std::cout << SimpleMax(4, 34) << std::endl;
  std::cout << SimpleMax(4.03, 3.4) << std::endl;

  // the following template argument deduction
  // results in no match function
  // std::cout << SimpleMax(4.03, 3) << std::endl;

  // you must use explicit type parameter
  std::cout << SimpleMax<double>(4.04, 3) << std::endl;

  std::cout << SimpleMax(factory(1000), factory(2000)) << std::endl;

  std::cout << "Complex Max: \n";
  std::cout << ComplexMax(factory(1001), factory(2001)) << std::endl;

  std::cout << ComplexMax2(300, 400) << std::endl;

  using IntStack = Stack<int>;
  using StringStack = Stack<std::string>;
  IntStack a;
  a.push(1);

  StringStack ss;
  ss.push("hello");

  Stack<int*> test;
  test.push(new int{42});
  assert(!test.empty());
  delete test.pop();

  g(1);
  g(1.0);
  g<>(1);
  g<>(1.0);
  g(1.0f);

  ValueWithComment<int> vc;
  vc.value = 42;
  vc.comment = "initial value";

  ValueWithComment vc2{1.3};
  ValueWithComment vc3{"hello", "initial value"};

  Stack<int> intStack1;
  Stack<int> intStack2 = intStack1;
  Stack intStack3 = intStack2;

  Stack intStack{0};
  Stack literalStack = "bottom";

  // only one conversion is allowed
  TestData td{"hello"};
  // TestData td2 = "hello";

  // 4 bytes
  std::cout << sizeof(int) << std::endl;

  // reference type
  C<(ii)> xii;
  C<123> x123;

  print(7.5, "hello", "world");
  {
    int a[42];
    MyClass<decltype(a)>::print();

    extern int x[];
    MyClass<decltype(x)>::print();

    foo(a, a, a, x, x, x, x);
  }

  {
    val<long> = 42;
    val<double> = 44.34;
    print_val();
  }
}

int x[] = {0, 8, 15};
