#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

std::string asString(const std::chrono::system_clock::time_point &tp)
{
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::asctime(gmtime(&t));
    ts.resize(ts.size() - 1);
    return ts;
}

int main()
{
    typedef std::chrono::duration<int, std::ratio<3600 * 24>> Days;

    std::chrono::time_point<std::chrono::system_clock> tp;
    std::cout << "epoch: " << asString(tp) << std::endl;

    tp += Days(1) + std::chrono::hours(23) + std::chrono::minutes(55);
    std::cout << "later: " << asString(tp) << std::endl;

    auto diff = tp - std::chrono::system_clock::time_point();
    std::cout << "diff : "
              << std::chrono::duration_cast<std::chrono::minutes>(diff).count()
              << " minute(s)" << std::endl;

    Days days = std::chrono::duration_cast<Days>(diff);
    std::cout << "diff : "
              << days.count()
              << " day(s)" << std::endl;

    tp -= std::chrono::hours(24 * 356);
    std::cout << "-1 year    " << asString(tp) << std::endl;

    tp -= std::chrono::duration<int, std::ratio<365 * 24 * 3600, 1>>(200);
    std::cout << "-200 year    " << asString(tp) << std::endl;

    tp -= std::chrono::duration<int, std::ratio<365 * 24 * 3600, 1>>(200);
    std::cout << "-200 year    " << asString(tp) << std::endl;
}