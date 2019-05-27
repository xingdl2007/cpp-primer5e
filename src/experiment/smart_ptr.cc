#include <thread>
#include <memory>
#include <iostream>
#include <functional>
#include <vector>

void func(std::unique_ptr<int> &ptr)
{
    std::cout << *ptr << std::endl;
}

void test(const std::function<void()> &f)
{
    f();
}

template <typename Callable>
void test2(Callable &&f)
{
    f();
}

void do_sth(int data)
{
    std::cout << "data: " << data << std::endl;
}

// Note: f is Fn type
template <typename Fn, typename... Args>
static void Worker(Fn f, Args &&... args)
{
    f(std::forward<Args>(args)...);
    return;
}

template <typename Fn, typename... Args>
void Wrapper(Fn &&f, Args &&... args)
{
    std::thread t(Worker<Fn, Args...>, std::forward<Fn>(f), std::forward<Args>(args)...);
    t.join();
}

int main(int argc, char *argv[])
{
    {
        Wrapper<decltype(do_sth), int>(do_sth, 2);
    }
    {
        std::unique_ptr<int> ptr = std::make_unique<int>(1);
        std::unique_ptr<int> ptr2 = std::make_unique<int>(1);

        // Not OK
        // copy occur when, when std::bind to std::function, there will be copying
        // std::function<void()> f = std::bind(func, std::move(ptr));
        // test(std::bind(func, std::move(ptr)));

        // OK, callable no need to cast to Callable
        test2(std::bind(func, std::move(ptr2)));
    }

    {
        std::vector<std::function<int(int)>> functions;
        std::function<int(int, int)> foo = [](int a, int b) { return a + b; };
        std::function<int(int)> bar = std::bind(foo, 2, std::placeholders::_1);
        functions.push_back(bar);
    }
}