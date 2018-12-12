#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

std::string asString(const std::chrono::system_clock::time_point &tp)
{
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::asctime(gmtime(&t));
    ts.resize(ts.size() - 1);
    return ts;
}

int main()
{
    // epoch: take care of local timezone
    std::chrono::system_clock::time_point tp;
    std::cout << asString(tp) << std::endl;

    // now
    tp = std::chrono::system_clock::now();
    std::cout << asString(tp) << std::endl;

    // min
    tp = std::chrono::system_clock::time_point::min();
    std::cout << asString(tp) << std::endl;

    // max
    tp = std::chrono::system_clock::time_point::max();
    std::cout << asString(tp) << std::endl;

    // Output is interesting:
    // Thu Jan  1 08:00:00 1970
    // Wed Dec 12 17:56:17 2018
    // Tue Sep 21 07:49:26 1677
    // Sat Apr 12 07:47:16 2262
}