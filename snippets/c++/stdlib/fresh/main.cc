#include <initializer_list>
#include <iostream>

class P
{
  public:
    P(int, int)
    {
        std::cout << "P(int, int)" << std::endl;
    }

    explicit P(int, int, int)
    {
    }

    explicit P(std::initializer_list<int>)
    {
        std::cout << "P(std::initializer_list<int>)" << std::endl;
    }

    P(P const &)
    {
        std::cout << "P(P const &)" << std::endl;
    }

    P &operator=(P const &)
    {
        std::cout << "P &operator=(P const &)" << std::endl;
        return *this;
    }
};

template <typename T>
void printElements(const T &collection)
{
    for (auto const &elem : collection)
    {
        std::cout << elem << std::endl;
    }
}

class X
{
  public:
    X() = default;

    X(const X &) = delete;
    X &operator=(const X &) = delete;
    // X(const X &)
    // {
    //     std::cout << "X(const X &)" << std::endl;
    // }

    // X(X &&) = delete;
    X(X &&)
    {
        std::cout << "X(X &&)" << std::endl;
    }
};

X foo()
{
    X x;
    return x;
}

int main(int argc, char const *argv[])
{
    P p1 = P{1, 2}; // euqal with P p1 = {1,2}, no copy-constructor is invoked
    P p2{1, 2, 3};
    p1 = p2;

    printElements(std::initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    int sum{};
    int array[]{1, 2, 3, 4, 5};
    for (auto i : array)
    {
        sum += i;
    }
    for (auto i : {sum, 2 * sum, 4 * sum})
    {
        std::cout << i << std::endl;
    }

    std::cout << "Move semantic:\n";
    X x = foo();
    return 0;
}