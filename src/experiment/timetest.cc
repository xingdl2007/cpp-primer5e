#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <unistd.h>

void print_tm(std::tm const &t)
{
    std::cout << "year: " << t.tm_year + 1900 << std::endl;
    std::cout << "month: " << t.tm_mon + 1 << std::endl;
    std::cout << "day: " << t.tm_mday << std::endl;
    std::cout << "hour: " << t.tm_hour << std::endl;
    std::cout << "min: " << t.tm_min << std::endl;
    std::cout << "sec: " << t.tm_sec << std::endl;
}

int main()
{
    std::string timestamp("2019-04-03 09:30:60");
    std::istringstream ss(timestamp);

    std::tm t = {}, t2{};

    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    if (ss.fail())
    {
        std::cout << "Parse failed: std::get_time()\n";
        return EXIT_FAILURE;
    }
    print_tm(t);
    std::cout << std::mktime(&t) << std::endl;

    char *res = strptime(timestamp.c_str(), "%Y-%m-%d %H:%M:%S", &t2);
    if (res == nullptr)
    {
        std::cout << "Parse failed: strptime\n";
        return EXIT_FAILURE;
    }
    std::cout << '\n';
    print_tm(t2);
    std::cout << std::mktime(&t2) << std::endl;

    {
        time_t t = time(NULL);
        struct tm lt = {0};

        localtime_r(&t, &lt);

        printf("Offset to GMT is %lds.\n", lt.tm_gmtoff);
        printf("The time zone is '%s'.\n", lt.tm_zone);
    }

    {
        while (true)
        {
            /* code */
            sleep(1);
            time_t t = time(nullptr);
            std::cout << t << " " << ctime(&t);
        }
    }

    return EXIT_SUCCESS;
}