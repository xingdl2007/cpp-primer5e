#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <vector>
#include <map>
#include <iostream>

int main(int argc, char *argv[])
{
    std::mutex mutex_;
    auto lambda = [&]() {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << std::random_device{}() << std::endl;
    };

    int count = atoi(argv[1]);

    std::vector<std::thread> threads;
    std::cout << count << std::endl;
    for (int i = 0; i < count; ++i)
    {
        std::thread t(lambda);
        threads.emplace_back(std::move(t));
    }
    for (auto &t : threads)
    {
        t.join();
    }
}