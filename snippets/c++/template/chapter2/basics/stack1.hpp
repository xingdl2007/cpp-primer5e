#pragma once

#include <vector>
#include <ostream>
#include <cassert>

// Option 2: part 1
template <typename T>
class Stack;

template <typename T>
std::ostream &operator<<(std::ostream &, Stack<T> const &);

template <typename T>
class Stack
{
  private:
    std::vector<T> elems;

  public:
    void push(T const &elem);
    void pop();
    T const &top() const;
    bool empty() const
    {
        return elems.empty();
    }
    void printOn(std::ostream &strm) const
    {
        for (T const &elem : elems)
        {
            strm << elem << ' ';
        }
    }

    // Best practice:
    // friend std::ostream &operator<<(std::ostream &strm, Stack<T> const &s)
    // {
    //     s.printOn(strm);
    //     return strm;
    // }

    // Option 1: part 1
    // template <typename U>
    // friend std::ostream &operator<<(std::ostream &, Stack<U> const &);

    // Option 2: part 2
    // <T> is important, we declare a specialization of the nonmember
    // function template as friend.
    friend std::ostream &operator<<<T>(std::ostream &, Stack<T> const &);
};

// Option 1: part 2
// Option 2: part 3
template <typename T>
std::ostream &operator<<(std::ostream &strm, Stack<T> const &s)
{
    s.printOn(strm);
    return strm;
}

template <typename T>
void Stack<T>::push(T const &elem)
{
    elems.push_back(elem);
}

template <typename T>
void Stack<T>::pop()
{
    assert(!elems.empty());
    elems.pop_back();
}

template <typename T>
T const &Stack<T>::top() const
{
    assert(!elems.empty());
    return elems.back();
}