#include <stdint.h>
#include <iostream>

template <typename T>
struct BestFit;

// specialization
template <>
struct BestFit<int>
{
    BestFit()
    {
        std::cout << "BestFIt<int>()\n";
    }
};

// overloading
template <typename T>
struct BestFit<T *>
{
    BestFit()
    {
        std::cout << "BestFIt<T*>()\n";
    }
};

template <typename T>
struct Foo
{
};

// partial specialization
template <typename T, typename U>
struct Foo<std::tuple<T, U>>
{
};

int func(int64_t a)
{
    std::cout << a << std::endl;
}

int main()
{
    BestFit<int> a;
    BestFit<int *> b;    
}