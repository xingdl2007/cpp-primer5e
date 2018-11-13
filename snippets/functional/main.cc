#include <functional>
#include <iostream>

using namespace std;

int main()
{
    std::function<void()> func;
    std::cout << sizeof(func) << std::endl;
}