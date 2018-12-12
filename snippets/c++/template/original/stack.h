#pragma once

#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
class Stack {
 public:
  Stack() = default;
  Stack(T elem) : elems({std::move(elem)}) {}

  ~Stack() = default;
  void push(T const& e) { elems.push_back(e); }
  void pop() {
    assert(!elems.empty());
    elems.pop_back();
  }
  T const& top() {
    assert(!elems.empty());
    return elems.back();
  }
  bool empty() { return elems.empty(); }

 private:
  std::vector<T> elems;
};

// Specialization of Class Templates,  not completed
template <>
class Stack<std::string> {
 public:
  void push(std::string const& s) {
    std::cout << "hhhhh" << std::endl;
    elems.push_back(s);
  }

 private:
  std::vector<std::string> elems;
};

// Partial specialized for pointer type
// We define a class template, still parameterized for T but specialized
// for a pointer (Stack<T*>)
template <typename T>
class Stack<T*> {
 private:
  std::vector<T*> elems;

 public:
  Stack() = default;
  ~Stack() = default;
  Stack(T* e) : elems({e}) {}
  void push(T*);
  T* pop();
  T* top() const;
  bool empty() const { return elems.empty(); }
};

template <typename T>
void Stack<T*>::push(T* elem) {
  elems.push_back(elem);
}

template <typename T>
T* Stack<T*>::pop() {
  T* p = elems.back();
  elems.pop_back();
  return p;
}

template <typename T>
T* Stack<T*>::top() const {
  return elems.back();
}
