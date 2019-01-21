#include <string>
#include <iostream>
#include <array>
#include <algorithm>

#include "addvalue.hpp"

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
void print(Cont const &c)
{
    std::cout << '[';
    for (auto &e : c)
    {
        std::cout << e << " ";
    }
    std::cout << ']';
}

int main(int argc, char const *argv[])
{
    {
        std::array<int, 10> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        print(arr);
        std::transform(arr.begin(), arr.end(), addValue<5, int>);
        print(arr);
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
