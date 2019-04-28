#include <atomic>
#include <iostream>
#include <mutex>
#include <condition_variable>

int main()
{
    {
        std::atomic<int> ai;
        std::cout << "atomic<int> lock free？ "
                  << std::boolalpha
                  << ai.is_lock_free()
                  << std::endl;
    }

    {
        std::atomic_flag flag = ATOMIC_FLAG_INIT; // 0

        flag.clear(std::memory_order_release);
        bool prev = flag.test_and_set();
        std::cout << "prev: " << std::boolalpha << prev << std::endl;
    }

    {
        std::cout << sizeof(std::atomic<uint32_t>) << std::endl; // 4 bytes
        std::cout << sizeof(std::atomic<uint64_t>) << std::endl; // 8 bytes
    }

    {
        std::cout << sizeof(std::mutex) << std::endl;              // 40 bytes
        std::cout << sizeof(std::condition_variable) << std::endl; // 48 bytes
    }
}
