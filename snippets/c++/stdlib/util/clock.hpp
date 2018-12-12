#include <chrono>
#include <iostream>
#include <iomanip>

template <typename Clock>
void printClockData()
{
    std::cout << "- precision: ";
    // if time unit is less or equal one millisecond
    typedef typename Clock::duration::period Period;
    if (std::ratio_less_equal<Period, std::nano>::value)
    {
        // the default resolution is second, so need mutiply std::giga when turn to nanoseconds
        typedef typename std::ratio_multiply<Period, std::giga>::type TT;
        std::cout << std::fixed << double(TT::num) / TT::den << " nanoseconds" << std::endl;
    }
    else
    {
        // print as seconds
        std::cout << std::fixed << double(Period::num) / Period::den << " seconds" << std::endl;
    }
    std::cout << "- is_steady: " << std::boolalpha << Clock::is_steady << std::endl;
}