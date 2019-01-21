#include <iostream>
template <auto T>
class Message
{
  public:
    void print()
    {
        std::cout << T << '\n';
    }
};

// why even decltype(auto) is possible ?
template <decltype(auto) N>
class C
{
};

int main(int argc, char const *argv[])
{
    {
        int i;
        C<(i)> x; // N is int&
    }

    {
        Message<42> msg1;
        msg1.print();

        static char const s[] = "hello";
        Message<s> msg2;
        msg2.print();
    }
    return 0;
}
