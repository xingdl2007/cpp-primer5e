#include <chrono>
#include <ratio>
#include <iostream>
#include <iomanip>
#include <string_view>
#include <map>
#include <unordered_map>
#include <ctime>

// very useful
template <typename Rep, typename Period>
std::ostream &operator<<(std::ostream &out, const std::chrono::duration<Rep, Period> &d)
{
    out << "[ " << d.count() << " of " << Period::num << "/"
        << Period::den << "]";
    return out;
}

int main()
{
    auto system_start = std::chrono::system_clock::now();
    std::cout << std::clock() << std::endl;
    {
        // very interesting clock/time: duration is a multiply of tick and ratio<> (period)
        std::chrono::duration<int> twentySeconds(20);
        std::chrono::duration<double, std::ratio<60>> halfAMinute(0.5);
        std::chrono::duration<long, std::ratio<1, 1000>> oneMillisecond(1);
    }

    {
        std::chrono::seconds twentySeconds(20);
        std::chrono::hours aDay(24);
        std::chrono::milliseconds ms(0);
        std::cout << ms.count() << " ms" << std::endl;
        ms += aDay;
        std::cout << ms.count() << " ms" << std::endl;
        --ms;
        std::cout << ms.count() << " ms" << std::endl;
        ms *= 2;
        std::cout << ms.count() << " ms" << std::endl;
        {
            std::chrono::hours ret = aDay % 7;
            std::cout << ret.count() << " hour" << std::endl;
        }

        // seconds
        std::chrono::seconds s = twentySeconds + aDay;
        std::cout << s.count() << " s" << std::endl;

        // nanoseconds
        std::chrono::nanoseconds ns = aDay + twentySeconds + ms;
        std::cout << ns.count() << " ns" << std::endl;
    }

    {
        std::chrono::duration<int, std::ratio<1, 3>> d1(1);
        std::chrono::duration<int, std::ratio<1, 5>> d2(1);
        std::cout << d1 + d2 << std::endl;
    }

    {
        // useful function
        std::cout << std::chrono::seconds::min() << std::endl;
        std::cout << std::chrono::seconds::zero() << std::endl;
        std::cout << std::chrono::seconds::max() << std::endl;
    }

    {
        // conversion
        std::chrono::seconds sec(55);
        // std::chrono::minutes m1 = sec; // compile error
        std::chrono::minutes m2 = std::chrono::duration_cast<std::chrono::minutes>(sec);
        std::cout << m2 << std::endl;

        std::chrono::duration<double, std::ratio<60>> halfMin(0.5);
        // std::chrono::seconds s1 = halfMin; // compile error
        std::chrono::seconds s2 = std::chrono::duration_cast<std::chrono::seconds>(halfMin);
        std::cout << s2 << std::endl;
    }

    {
        using namespace std;
        using namespace std::chrono;

        // most precision of duration
        milliseconds ms(7255042);

        // split into hours, minutes, seconds, and milliseconds
        hours hh = duration_cast<hours>(ms);
        minutes mm = duration_cast<minutes>(ms % hours(1));
        seconds ss = duration_cast<seconds>(ms % minutes(1));
        milliseconds msec = duration_cast<milliseconds>(ms % seconds(1));

        cout << "raw: " << hh << "::" << mm << "::" << ss << "::" << msec << endl;
        cout << "hum: " << setfill('0') << setw(2) << hh.count() << "::"
             << setw(2) << mm.count() << "::"
             << setw(2) << ss.count() << "::"
             << setw(3) << msec.count() << endl;
    }

    {
        // string_view
        using namespace std;
        unordered_map<string_view, string_view> smap =
            {
                {"hello", "world"},
                {"country", "China"},
            };
        string_view key("hello");
        cout << smap[key] << std::endl;

        map<string_view, uint16_t> imap = {
            {"hello", 1},
            {"country", 12},
        };
        cout << imap["country"] << endl; /*interesting*/
    }

    {
        if (std::chrono::system_clock::now() > system_start + std::chrono::microseconds(1))
        {
            std::cout << "system start more than 1 us" << std::endl;
        }
        else
        {
            std::cout << "system start less than 1 us" << std::endl;
        }
    }

    {
        std::cout << CLOCKS_PER_SEC << std::endl;
        std::cout << std::clock() << std::endl;
    }
}