#include <random>
#include <iostream>
#include <sstream>

void printNumber(std::default_random_engine &dre)
{
    for (int i = 0; i < 6; ++i)
    {
        std::cout << dre() << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::default_random_engine dre;
    printNumber(dre);

    std::default_random_engine dre2;
    printNumber(dre2);

    std::default_random_engine dre3(42);
    printNumber(dre3);

    // save state of entire dre
    std::stringstream engingeState;
    engingeState << dre;
    std::cout << "engingeState: " << engingeState.str() << std::endl;

    printNumber(dre);

    // restore
    engingeState >> dre;
    printNumber(dre);

    // interesting
    engingeState.clear();  // clear EOF bit
    engingeState.seekg(0); // and move read position to the beginning
    engingeState >> dre;
    dre.discard(2);
    printNumber(dre);

    {
        std::default_random_engine dre;
        // [1, 2**31-2]
        std::cout << dre.min() << " " << dre.max() << std::endl;
    }

    {
        std::uniform_int_distribution<> d(0, 20);
        std::cout << d.a() << " " << d.b() << std::endl;
        std::cout << d.param().a() << " " << d.param().b() << std::endl;
    }
}