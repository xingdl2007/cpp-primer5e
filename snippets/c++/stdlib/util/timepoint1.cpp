#include <chrono>
#include <iostream>
#include "timepoint.hpp"

int main()
{
    auto tp1 = makeTimePoint(2010, 01, 01, 00, 00);
    std::cout << asString(tp1) << std::endl;

    auto tp2 = makeTimePoint(2011, 05, 23, 13, 44);
    std::cout << asString(tp2l) << std::endl;
    return 0;
}