#include <unistd.h>
#include <cstdio>
#include <iostream>

struct Status
{
    uint32_t nr;
    uint32_t data[]; // no difference with data[0]
};

int main(int argc, char *argv[])
{
    char buffer[64 * 1024];
    std::FILE *fp = fopen("file.log", "w");
    ::setbuffer(fp, buffer, sizeof buffer);

    ::fprintf(fp, "%s\n", "press enter to exit...");
    ::fflush(fp);

    std::cout << sizeof(Status) << std::endl;
    std::cout << "pid: " << ::getpid() << ", press enter to exit...";
    std::cin.get();

    // coredump
    // *((uint32_t *)0) = 1;
    ::fclose(fp);
}   