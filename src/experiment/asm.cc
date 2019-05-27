#include <iostream>
#include <unistd.h>

template <class T>
void doNotOptimizeAway(T &&datum)
{
    asm volatile(""
                 : "+r"(datum));
}

unsigned long long rdtsc(void)
{
    unsigned int tickl, tickh;
    __asm__ __volatile__("rdtsc"
                         : "=a"(tickl), "=d"(tickh));
    return ((unsigned long long)tickh << 32) | tickl;
}

int main(int argc, char *argv)
{
    int sum = 0;
    for (int i = 0; i < 100; ++i)
    {
        doNotOptimizeAway(sum += i);
    }
    doNotOptimizeAway(sum);

    // delta
    for (int i = 0; i < 100; ++i)
    {
        auto start = rdtsc();
        auto end = rdtsc();
        std::cout << start << " -> " << end << "[" << end - start << "]" << std::endl;
    }

    std::cout << sysconf(_SC_CLK_TCK) << std::endl;
}