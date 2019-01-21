#pragma once

#include "stack1.hpp"
#include <deque>
#include <string>
#include <cassert>

template <>
class Stack<std::string>
{
  private:
    // use deque instead of a vector
    std::deque<std::string> elems;

  public:
    // use reference semantics to pass the string argument to push(), wihch
    // makes more sense for this specific type
    void push(std::string const &);
    void pop();
    std::string const &top() const;
    bool empty() const
    {
        return elems.empty();
    }
};

void Stack<std::string>::push(std::string const &elem)
{
    elems.push_back(elem);
}

void Stack<std::string>::pop()
{
    assert(!elems.empty());
    elems.pop_back();
}

std::string const &Stack<std::string>::top() const
{
    assert(!elems.empty());
    return elems.back();
}