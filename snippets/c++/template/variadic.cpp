#include <iostream>
#include <bitset>
#include <future>

// no parameter
void print()
{
}

// only one parameter
template <typename T>
void print(T const &arg)
{
    std::cout << arg << std::endl;
}

// more parameters
template <typename T, typename... Types>
void print(T const &firstArg, Types const &... args)
{
    std::cout << firstArg << std::endl;
    print(args...);
}

template <typename T>
void foo()
{
    T t{}; // T t = T(); initialized with zero (since C++11)
    std::cout << t << std::endl;
}

int main()
{
    print(7.5, "hello", std::bitset<16>(377), 42);
    print(1);
    print();
    foo<std::string>();
    foo<int>();
    foo<float>();

    
}