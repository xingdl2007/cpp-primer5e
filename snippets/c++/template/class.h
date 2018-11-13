#include <iostream>

template <typename T>
struct MyClass;

template <typename T, std::size_t SZ>
struct MyClass<T[SZ]> {
  static void print() { std::cout << "print() for T[" << SZ << "]\n"; }
};

template <typename T, std::size_t SZ>
struct MyClass<T (&)[SZ]> {
  static void print() { std::cout << "print() for T(&)[" << SZ << "]\n"; }
};

template <typename T>
struct MyClass<T[]> {
  static void print() { std::cout << "print() for T[]\n"; }
};

template <typename T>
struct MyClass<T (&)[]> {
  static void print() { std::cout << "print() for T(&)[]\n"; }
};

template <typename T>
struct MyClass<T*> {
  static void print() { std::cout << "print() for T*\n"; }
};

template <typename T>
struct MyClass {
  static void print() { std::cout << "Primary\n"; }
};
