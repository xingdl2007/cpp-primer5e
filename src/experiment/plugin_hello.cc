#include <cstdio>

extern "C"
{
    void hello(int time)
    {
        std::printf("hello world: %d\n", time);
    }
}