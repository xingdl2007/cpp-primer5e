#include <cstring>
#include <iostream>

template <typename T>
T const &max(T const &a, T const &b)
{
    std::cout << "T const &max(T const &a, T const &b)" << std::endl;
    return b < a ? a : b;
}

char const *max(char const *a, char const *b)
{
    std::cout << "char const *max(char const *a, char const *b)" << std::endl;
    return std::strcmp(b, a) < 0 ? a : b;
}

// [with T = const char*]
template <typename T>
T const &max(T const &a, T const &b, T const &c)
{
    std::cout << "T const &max(T const &a, T const &b, T const &c)" << std::endl;
    return max(max(a, b), c); // warning: returning reference to temporary [-Wreturn-local-addr]
}

int const &func()
{
    return 3; // warning: returning reference to temporary [-Wreturn-local-addr]
}

int main(int argc, char const *argv[])
{
    auto m1 = ::max(7, 42, 68);
    std::cout << std::endl;

    char const *s1 = "frederic";
    char const *s2 = "anica";
    char const *s3 = "lucas";

    // core dumped, access of expires temporary local value will
    // trigger segmentation fault
    auto m2 = ::max(s2, s2, s3); // will core dump
    ::max(s2, s2, s3);           // will not core dump

    // the following will core dump too, but if you does not access return value, it's ok
    auto m3 = func(); // will core dump
    func();           // will not core dump
    return 0;
}