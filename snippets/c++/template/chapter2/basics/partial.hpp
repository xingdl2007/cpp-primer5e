#pragma once

#include <iostream>

template <typename T1, typename T2>
class MyClass
{
  public:
    MyClass()
    {
        std::cout << "MyClass<T1, T2>" << std::endl;
    }
};

template <typename T>
class MyClass<T, T>
{
  public:
    MyClass()
    {
        std::cout << "MyClass<T, T>" << std::endl;
    }
};

template <typename T>
class MyClass<T *, T *>
{
  public:
    MyClass()
    {
        std::cout << "MyClass<T*, T*>" << std::endl;
    }
};

template <typename T>
class MyClass<T, int>
{
  public:
    MyClass()
    {
        std::cout << "MyClass<T,int>" << std::endl;
    }
};

template <typename T1, typename T2>
class MyClass<T1 *, T2 *>
{
  public:
    MyClass()
    {
        std::cout << "MyClass<T1*, T2*>" << std::endl;
    }
};
