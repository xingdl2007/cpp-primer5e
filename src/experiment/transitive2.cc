#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<int> data[5];
std::atomic<int> sync(0);

void thread_1()
{
    data[0].store(42, std::memory_order_relaxed);
    data[1].store(97, std::memory_order_relaxed);
    data[2].store(17, std::memory_order_relaxed);
    data[3].store(-141, std::memory_order_relaxed);
    data[4].store(2003, std::memory_order_relaxed);
    sync.store(1, std::memory_order_release);
}

void thread_2()
{
    int expected = 1;
    while (!sync.compare_exchange_strong(expected, 2, std::memory_order_acq_rel))
    {
        /* reset expected */
        expected = 1;
    }
}

void thread_3()
{
    while (sync.load(std::memory_order_acquire) < 2)
        ;
    assert(data[0].load(std::memory_order_relaxed) == 42);
    assert(data[1].load(std::memory_order_relaxed) == 97);
    assert(data[2].load(std::memory_order_relaxed) == 17);
    assert(data[3].load(std::memory_order_relaxed) == -141);
    assert(data[4].load(std::memory_order_relaxed) == 2003);
}

int main()
{
    std::thread a(thread_1);
    std::thread b(thread_2);
    std::thread c(thread_3);

    a.join();
    b.join();
    c.join();
}