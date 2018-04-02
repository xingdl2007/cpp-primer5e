//
// C++ concurrency in Action.
//

// what is the difference between std::move and std::forward?
// highlight:
// std::forward is for perfect forwarding, std::move just allow you treat
// a object as a temporary(an rvalue).
//
// ref: https://stackoverflow.com/questions/9671749/whats-the-difference-between-stdmove-and-stdforward
//
// std::move takes an object and allows you to treat it as a temporary (an rvalue).
// Although it isn't a semantic requirement, typically a function accepting a reference
// to an rvalue will invalidate it.
// When you see std::move, it indicates that the value of the object should not be used
// afterwards, but you can still assign a new value and continue using it.
//
// std::forward has a single use case: to cast a templated function parameter (inside the
// function) to the value category (lvalue or rvalue) the caller used to pass it. This
// allows rvalue arguments to be passed on as rvalues, and lvalues to be passed on as
// lvalues, a scheme called "perfect forwarding."
//

#include <future>
#include <iostream>

void overloaded(int const &arg) { std::cout << "by lvalue\n"; }
void overloaded(int &&arg) { std::cout << "by rvalue\n"; }

template<typename t>
/* "t &&" with "t" being template param is special, and  adjusts "t" to be
   (for example) "int &" or non-ref "int" so std::forward knows what to do. */
void forwarding(t &&arg) {
  std::cout << "via std::forward: ";
  overloaded(std::forward<t>(arg));
  std::cout << "via std::move: ";
  overloaded(std::move(arg)); // conceptually this would invalidate arg
  std::cout << "by simple passing: ";
  overloaded(arg);
}

int main() {
  std::cout << "initial caller passes rvalue:\n";
  forwarding(5);
  std::cout << "\ninitial caller passes lvalue:\n";
  int x = 5;
  forwarding(x);
}