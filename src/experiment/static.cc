#include <iostream>

struct Trace_Null
{
    void dumpStats()
    {
        std::cout << "dumpStats()" << std::endl;
    }

    static Trace_Null Instance;
};

// interesting
Trace_Null Trace_Null::Instance;

int main(int argc, char *argv[])
{
    Trace_Null::Instance.dumpStats();
}