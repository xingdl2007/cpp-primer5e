#include <chrono>
#include "clock.hpp"

int main()
{
    std::cout << "system_clock: " << std::endl;
    printClockData<std::chrono::system_clock>();

    std::cout << "steady_clock: " << std::endl;
    printClockData<std::chrono::steady_clock>();

    std::cout << "high_resolution_clock: " << std::endl;
    printClockData<std::chrono::high_resolution_clock>();
}