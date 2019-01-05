#include <iostream>
#include <bitset>
#include <vector>
#include <future>
#include <functional>
#include "a.h"

// no parameter
void print()
{
}

// only one parameter
template <typename T>
void print(T const &arg)
{
    std::cout << arg << std::endl;
}

// more parameters
template <typename T, typename... Types>
void print(T const &firstArg, Types const &... args)
{
    std::cout << firstArg << std::endl;
    print(args...);
}

template <typename T>
void foo()
{
    T t{}; // T t = T(); initialized with zero (since C++11)
    std::cout << t << std::endl;
}

void func(int x, int y)
{
}

auto l = [](int x, int y) {};

class C
{
  public:
    void operator()(int x, int y) const {}
    void memfunc(int x, int y) const {}
};

// declaration
template <std::size_t... others>
struct static_max;

// partial specialization: only one nontype parameter
template <std::size_t arg>
struct static_max<arg>
{
    static const std::size_t value = arg;
};

// partial specialization: two and more nontype parameters
template <std::size_t arg1, std::size_t arg2, std::size_t... others>
struct static_max<arg1, arg2, others...>
{
    static const std::size_t value = arg1 >= arg2 ? static_max<arg1, others...>::value : static_max<arg2, others...>::value;
};

static B b;
A B::a;

int main()
{
    printf("main()\n");
    {
        variant<> v;
        variant<int> vv;
        variant<int, double> vvv;
    }

    {
        std::cout << static_max<sizeof(int)>::value << std::endl;
        std::cout << static_max<sizeof(int), sizeof(double)>::value << std::endl;
        std::cout << static_max<sizeof(int), sizeof(double), sizeof(std::string)>::value << std::endl;
        std::cout << static_max<sizeof(int), sizeof(double), sizeof(std::string), sizeof(std::vector<int>)>::value << std::endl;
        std::cout << '\n';
    }

    {
        print(7.5, "hello", std::bitset<16>(377), 42);
        print(1);
        print();
        foo<std::string>();
        foo<int>();
        foo<float>();

        C c;
        std::shared_ptr<C> sp(new C);

        std::bind(func, 77, 33)();
        std::bind(l, 77, 33)();
        std::bind(C(), 77, 33)();
        std::bind(&C::memfunc, c, 77, 33)();  // c.memfunc()
        std::bind(&C::memfunc, &c, 77, 33)(); // &c->memfunc()
        std::bind(&C::memfunc, sp, 77, 33)(); // sp->memfunc

        std::async(func, 52, 77);
        std::async(l, 42, 77);
        std::async(c, 42, 77);
        std::async(&C::memfunc, c, 42, 77);  // c.memfunc()
        std::async(&C::memfunc, &c, 42, 77); // &c->memfunc()
        std::async(&C::memfunc, sp, 42, 77); // sp->memfunc
    }
}