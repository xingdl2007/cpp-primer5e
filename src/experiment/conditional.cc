#include <unistd.h>
#include <thread>
#include <condition_variable>

bool flag = false;
std::mutex m1, m2;
std::condition_variable cv;

void fun1()
{
    while (flag == 0)
    {
        std::unique_lock<std::mutex> lock(m1);
        cv.wait(lock, []() { return flag; });
    }
}

void fun2()
{
    while (flag == 0)
    {
        std::unique_lock<std::mutex> lock(m2);
        cv.wait(lock, []() { return flag; });
    }
}

int main(int argc, char *argv[])
{
    std::thread t1(fun1);
    std::thread t2(fun2);
    {
        sleep(3);
        {
            std::lock_guard<std::mutex> lock1(m1);
            std::lock_guard<std::mutex> lock2(m2);
            flag = true;
        }
        cv.notify_all();
    }

    t1.join();
    t2.join();
}