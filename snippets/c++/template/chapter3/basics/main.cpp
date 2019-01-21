#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include <memory>
#include <array>
#include <algorithm>
#include <tuple>

#include "addvalue.hpp"
#include "varprint1.hpp"

// Aggregate classes: classes/structs with no user-provided, explicit,
// or inherited constructors, no private or protected nonstatic data
// members, no virtual functions, and no virtual, private, or protected
// base classes
template <typename T>
struct ValueWithComment
{
    T value;
    std::string comment;
};

// deduction guide, constructor deduction guide
ValueWithComment(char const *, char const *)->ValueWithComment<std::string>;

template <typename Cont>
void printColl(Cont const &c)
{
    std::cout << '[';
    for (auto &e : c)
    {
        std::cout << e << " ";
    }
    std::cout << ']' << '\n';
}

enum class Category
{
    INFO,
    DEBUG,
    WARNNING,
    ERROR
};

template <char const *name>
class MyClass
{
};

char const s11[] = "hello"; // internal linkage

int main(int argc, char const *argv[])
{
    {
        std::array<std::string, 5> arr = {"Hello", "my", "new", "!", "World"};
        // printByIdx<std::array<std::string, 5>, 0, 4, 3>(arr);
        printByIdx(arr, Indices<0, 4, 3>());

        auto t = std::make_tuple(12, "monkeys", 2.0);
        printByIdx(t, Indices<0, 1, 2>());
    }
    {
        std::vector<std::string> coll = {"good", "times", "say", "bye"};
        printElems(coll, 2, 0, 3);
        printIdx<2, 0, 3>(coll);
    }

    {
        std::cout << std::boolalpha;
        std::cout << isHomogeneous(1, 2, 3) << '\n';
        std::cout << isHomogeneous(43, -1, "hello") << '\n';
        std::cout << isHomogeneous("hello", "", "world", "!") << '\n';
    }

    {
        std::string s("world");
        print(7.5, "hello", s);
        printDouble(7.5, std::string("hello"), s);
        addOne(0, 2, 4, 6, 8);
    }

    {
        MyClass<s11> x;                 // OK since C++11
        static char const s17[] = "hi"; // no linkage
        MyClass<s17> m17;               // OK since C++17
    }

    {
        // only int can be nontype template parameter
        foo<5>();
        foo<Category::INFO>();
        bar<nullptr_t>();
    }
    {
        std::array<int, 10> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        printColl(arr);
        std::transform(arr.begin(), arr.end(), arr.begin(), addValue<5, int>);
        printColl(arr);
    }

    {
        std::cout << "Hello World" << std::endl;
        ValueWithComment<int> vc;
        vc.value = 42;
        vc.comment = "initial value";

        ValueWithComment vc2 = {"hello", "initial value"};
    }
    return 0;
}

namespace Demo
{
template <typename T, typename... Args>
std::shared_ptr<T> make_shared(Args &&... args);

class Thread
{
  public:
    template <typename F, typename... Args>
    explicit Thread(F &&f, Args &&... args);
};

template <typename T>
class vector
{
  public:
    template <typename... Args>
    void emplace_back(Args &&... args);
};

// args are copies with decayed types, arguments are copied and decay
template <typename... Args>
void foo(Args... args);

// args are nondecayed reference to passed objects
template <typename... Args>
void bar(Args const &... args);
} // namespace Demo
