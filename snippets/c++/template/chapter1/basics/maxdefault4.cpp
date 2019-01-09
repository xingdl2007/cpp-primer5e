#include <iostream>

template <typename T1, typename T2>
auto max(T1 a, T2 b)
{
    std::cout << "auto max(T1 a, T2 b)" << std::endl;
    return b < a ? a : b;
}

template <typename RT, typename T1, typename T2>
RT max(T1 a, T2 b)
{
    std::cout << "RT max(T1 a, T2 b)" << std::endl;
    return b < a ? a : b;
}

int main(int argc, char const *argv[])
{
    /* code */
    max(1, 2);
    max<long double>(3.4, 1);
    return 0;
}
