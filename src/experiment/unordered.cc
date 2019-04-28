#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

void foo(int a, int b)
{
    std::cout << a << ", " << b << std::endl;
}
int get_num()
{
    static int i = 0;
    return ++i;
}

std::atomic<bool> x, y;
std::atomic<int> z;

void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed);
    y.store(true, std::memory_order_relaxed);
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_relaxed))
    {
        /* code */
    }
    if (x.load(std::memory_order_relaxed))
        ++z;
}

int main()
{
    foo(get_num(), get_num());
    {
        x = false;
        y = false;
        z = 0;

        std::thread a(write_x_then_y);
        std::thread b(read_y_then_x);

        a.join();
        b.join();
        assert(z.load() != 0);
        std::cout << z << std::endl;
    }
}