#include <time.h>
#include <tuple>
#include <iostream>
#include <exception>

void clock_res(clockid_t clock_id, struct timespec &res)
{
    clock_getres(clock_id, &res);
}

std::tuple<clockid_t, const char *> clock_types[] = {
    {CLOCK_REALTIME, "realtime"},
    {CLOCK_REALTIME_COARSE, "realtime coarse"}, // 4us
    {CLOCK_MONOTONIC, "monotonic"},
    {CLOCK_MONOTONIC_COARSE, "monotonic coarse"}, // 4us
    {CLOCK_MONOTONIC_RAW, "monotonic raw"},
    {CLOCK_BOOTTIME, "boottime"},
    {CLOCK_PROCESS_CPUTIME_ID, "process cputime id"},
    {CLOCK_THREAD_CPUTIME_ID, "thread cputime id"}};

void print_clock_res()
{
    for (auto &t : clock_types)
    {
        struct timespec res;
        clock_res(std::get<0>(t), res);
        std::cout << std::get<1>(t) << ": " << res.tv_sec << "s."
                  << res.tv_nsec << "ns" << std::endl;
    }
}

int main()
{
    print_clock_res();
}