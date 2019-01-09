#include <cstring>
#include <string>
#include <iostream>

// template function overloading
template <typename T>
T max(T a, T b)
{
    std::cout << "T max(T a, T b)" << std::endl;
    return b < a ? a : b;
}

template <typename T>
T *max(T *a, T *b)
{
    std::cout << "T *max(T *a, T *b)" << std::endl;
    return *b < *a ? a : b;
}

// for C-style string, ordinary function, not template
char const *max(char const *a, char const *b)
{
    std::cout << "char const *max(char const *a, char const *b)" << std::endl;
    return std::strcmp(b, a) < 0 ? a : b;
}

int main(int argc, char const *argv[])
{
    int a = 7, b = 42;
    auto m1 = ::max(a, b);

    std::string s1 = "hey";
    std::string s2 = "you";
    auto m2 = ::max(s1, s2);

    auto m3 = ::max(&a, &b);

    char const *x = "hello";
    char const *y = "world";
    auto m4 = ::max(x, y);
    return 0;
}
