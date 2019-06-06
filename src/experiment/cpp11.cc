#include <utility>
#include <iostream>
#include <stdint.h>
#include <stdio.h>

#include <iostream>
#include <utility>
#include <tuple>
#include <type_traits>

namespace test
{
struct true_type
{
    static bool value;
};
bool true_type::value = true;

} // namespace test

class Test : public test::true_type
{
};

struct Foo
{
    explicit Foo(std::tuple<int, float>)
    {
        std::cout << "Constructed a Foo from a tuple\n";
    }
    Foo(int, float)
    {
        std::cout << "Constructed a Foo from an int and a float\n";
    }
};

int main()
{
    std::cout << sizeof(std::piecewise_construct) << std::endl;

    std::tuple<int, float> t(1, 3.14);
    std::pair<Foo, Foo> p1(t, t);
    std::pair<Foo, Foo> p2(std::piecewise_construct, t, t);

    {
        uint64_t array[4];
        printf("%p\n", array);
        printf("%p\n", &array[0]);
        printf("%p\n", &array);
    }

    {
        test::true_type::value = false;
        std::cout << Test::value << std::endl;
        std::cout << test::true_type::value << std::endl;
    }
}
