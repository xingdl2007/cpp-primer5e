#include <chrono>
#include <ctime>
#include <string>

inline std::string asString(const std::chrono::system_clock::time_point &tp)
{
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ret(ctime(&t));
    ret.resize(ret.size() - 1);
    return ret;
}

inline std::chrono::system_clock::time_point makeTimePoint(int year, int month, int day,
                                                           int hour, int min, int sec = 0)
{
    std::tm t;
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = sec;
    t.tm_isdst = -1; // daylight saving time information is not available
    std::time_t tp = std::mktime(&t);
    if (tp == -1)
    {
        throw "no valid system time";
    }
    return std::chrono::system_clock::from_time_t(tp);
}