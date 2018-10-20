#include <cstring>
#include <iostream>
#include <type_traits>

// #1
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
  ~Temp() { std::cout << data << std::endl; }
  Temp& operator=(Temp const& rhs) {
    data = rhs.data;
    return *this;
  }

 private:
  int data;
};

Temp factory(int d) { return Temp(d); }

class N {
 public:
  N() = default;
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
// template <typename T>
// auto max(T a, T b) {
//  return b < a ? a : b;
//}

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
  return max(max(a, b), c);
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
  auto m2 = ::max(s1, s2, s3);
  printf("m2: %p\n", m2);
  std::cout << m2 << std::endl;  // garbage

  printf("s1: %p\n", s1);
  printf("s2: %p\n", s2);
  printf("s3: %p\n", s3);
}
