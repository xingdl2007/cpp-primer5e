// https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern#Static_polymorphism

#include <iostream>

//------------------------------------------------------------------------
// basic CRTP: curiously recurring template pattern
template <typename T> class Base {
public:
  void A() {
    std::cout << "Base::A(), &A: " << &Base::A << "\n";
    B();
  }
  void B() { std::cout << "Base::B(), &B: " << &Base::B << "\n"; }

  // data member is seems like an address, but member funciton's address is
  // always 1?
  int m;

  void C() { static_cast<T *>(this)->C(); }
  void D() { static_cast<T *>(this)->D(); }
};

class Derived : public Base<Derived> {
public:
  void A() {
    std::cout << "Derived::A(), &A: " << &Derived::A << "\n";
    B();
  }
  void B() { std::cout << "Derived ::B(), &B: " << &Derived::B << "\n"; }
  void C() { std::cout << "Derived ::C(), &C: " << &Derived::C << "\n"; }
  void D() { std::cout << "Derived ::D(), &D: " << &Derived::D << "\n"; }
};

//------------------------------------------------------------------------
// object counter
template <typename T> class Counter {
public:
  static int objects_created;
  static int objects_alive;

  Counter() {
    ++objects_created;
    ++objects_alive;
  }

  Counter(Counter const &) {
    ++objects_created;
    ++objects_alive;
  }

  // operator= is deleted
  Counter &operator=(Counter const &) = delete;
  Counter &operator=(Counter &&) = delete;

protected:
  ~Counter() { --objects_alive; }
};

template <typename T> int Counter<T>::objects_created{0};
template <typename T> int Counter<T>::objects_alive{0};

class X : Counter<X> {};

class Y : Counter<Y> {};

//------------------------------------------------------------------------
// polymorphic chaining
template <typename ConcretePrinter> class Printer {
public:
  template <typename T> ConcretePrinter &print(T &&t) {
    m_stream << t;
    return *static_cast<ConcretePrinter *>(this);
  }

  template <typename T> ConcretePrinter &println(T &&t) {
    m_stream << t << std::endl;
    return *static_cast<ConcretePrinter *>(this);
  }

protected:
  // user code can not create a general printer
  Printer(std::ostream &pstream) : m_stream(pstream) {}

private:
  std::ostream &m_stream;
};

class CoutPrinter : public Printer<CoutPrinter> {
public:
  CoutPrinter() : Printer(std::cout) {}
  CoutPrinter &SetConsoleColor() { return *this; }
};

//------------------------------------------------------------------------
// CRTP clone problem
class Shape {
public:
  Shape() = delete;
  Shape &operator=(Shape const &) = delete;

  virtual ~Shape(){};
  virtual Shape *clone() const = 0;
};

template <typename Derived> class ShapeCRTP : public Shape {
public:
  virtual Shape *clone() const override {
    // copy
    return new Derived(static_cast<Derived const &>(*this));
  }

protected:
  ShapeCRTP() = default;
};

class Square : public ShapeCRTP<Square> {};
class Circle : public ShapeCRTP<Circle> {};

int main(int argc, char *argv[]) {
  {
    Derived d;
    Base<Derived> &b = d;

    b.A();
    d.A();

    b.C();
    b.D();
  }

  {
    X x1;
    { X x2; }
    std::cout << Counter<X>::objects_created << " " << Counter<X>::objects_alive
              << std::endl;
  }

  { CoutPrinter{}.println("hello").SetConsoleColor().println(500); }

  return 0;
}