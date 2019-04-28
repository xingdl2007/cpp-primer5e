#include <iostream>
#include <type_traits>

int main()
{
    std::cout << std::extent<int[3]>::value << '\n'; //< default dimension is 0
    std::cout << std::extent<int[3][4], 0>::value << '\n';
    std::cout << std::extent<int[3][4], 1>::value << '\n';
    std::cout << std::extent<int[3][4], 2>::value << '\n';
    std::cout << std::extent<int[]>::value << '\n';

    const auto ext = std::extent<int[9]>{};
    std::cout << ext << '\n'; //< implicit conversion to std::size_t

    const int ints[] = {1, 2, 3, 4};
    std::cout << std::extent<decltype(ints)>::value << '\n'; //< array size
}