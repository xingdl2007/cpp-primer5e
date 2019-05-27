#include <time.h>

int main(int argc, char *argv[])
{
    struct timespec ts;
    for (int i = 0; i < 10000000; ++i)
    {
        clock_gettime(CLOCK_REALTIME, &ts);
    }
}