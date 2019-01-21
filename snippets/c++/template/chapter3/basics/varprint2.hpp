#include <iostream>

// If two function templates only differ by a tailing parameter pack,
// the function template without the trailing parameter pack is preferred.
template <typename T>
void print(T arg)
{
    std::cout << arg << '\n';
}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << sizeof...(Types) << '\n';
    std::cout << sizeof...(args) << '\n';

    print(firstArg);
    print(args...);
}