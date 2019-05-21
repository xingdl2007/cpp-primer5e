#include <iostream>
#include <thread>
#include <mutex>

class Demo
{
  public:
    static thread_local int data;
};

int thread_local Demo::data = 1;

int main()
{
    std::mutex m;
    std::thread t1([&]() {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "Thread 1:" << Demo::data << std::endl;
    });

    std::thread t2([&]() {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "Thread 2:" << Demo::data << std::endl;
    });

    t1.join();
    t2.join();
}