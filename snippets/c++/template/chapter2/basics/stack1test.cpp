#include "stack1.hpp"
#include "stackpartspec.hpp"
#include "partial.hpp"

#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    // partial
    {
        MyClass<int, float> mif;
        MyClass<float, float> mff;
        MyClass<float, int> mfi;
        MyClass<int *, float *> mpp;
        MyClass<int *, int *> mii;
    }

    {
        Stack<int> intStack;
        Stack<std::string> stringStack;

        intStack.push(7);
        intStack.push(8);
        intStack.push(9);
        std::cout << intStack.top() << '\n';
        std::cout << intStack << std::endl;

        stringStack.push("Hello");
        std::cout << stringStack.top() << '\n';
        stringStack.pop();

        Stack<std::pair<int, int>> ps;
        ps.push({4, 5});
        ps.push({6, 7});
        std::cout << ps.top().first << '\n';
    }

    {
        Stack<int *> ptrStack;
        ptrStack.push(new int{42});
        std::cout << *ptrStack.top() << '\n';
        delete ptrStack.pop();
    }
    return 0;
}
