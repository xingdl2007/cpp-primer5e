#include "stack3.hpp"

#include <iostream>
#include <deque>
#include <string>

class Test
{
  public:
    void func(std::string)
    {
        std::cout << "func(std::stirng){}" << '\n';
    }
};

int main(int argc, char const *argv[])
{
    {
        Stack stringStack{"bottom"};
        std::cout << stringStack.top() << '\n';
    }

    // By language rules, you can't copy initialize (initialize using =) an object
    // by passing a string literal to constructor expecting a std::string.
    //
    // {
    //     Stack stringStack = "bottom";
    //     std::cout << stringStack.top() << '\n';
    // }
    // But function parameter can!!
    {
        Test t;
        t.func("hello");
    }

    {
        Stack intStack = 0;
        std::cout << intStack.top() << '\n';
    }

    {
        Stack<int> intStack1;
        Stack<int> intStack2 = intStack1;
        Stack intStack3 = intStack1; // need -std=c++17
    }

    {
        Stack<int> intStack;
        Stack<double, std::deque<double>> dblStack;

        intStack.push(7);
        std::cout << intStack.top() << '\n';

        dblStack.push(42.42);
        std::cout << dblStack.top() << '\n';
        dblStack.pop();
    }
    return 0;
}
