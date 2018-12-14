#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <map>
#include <iostream>

static uint64_t GenerateId()
{
    static thread_local std::mt19937_64 rand_source{std::random_device()()};
    return static_cast<uint64_t>(rand_source());
}

int main()
{
    std::mutex mutex_;
    std::map<uint64_t, uint64_t> result;
    auto lambda = [&]() {
        for (int i = 0; i < 1000000; ++i)
        {
            auto id = GenerateId();
            {
                std::lock_guard<std::mutex> lock(mutex_);
                result[id]++;
            }
        }
    };

    std::thread t1(lambda);
    std::thread t2(lambda);
    std::thread t3(lambda);
    std::thread t4(lambda);
    std::thread t5(lambda);
    std::thread t6(lambda);
    std::thread t7(lambda);
    std::thread t8(lambda);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    for (auto const &p : result)
    {
        if (p.second > 1)
        {
            std::cout << p.first << " " << p.second << std::endl;
        }
    }
    return 0;
}