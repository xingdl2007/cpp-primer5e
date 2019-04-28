#include <locale>
#include <clocale>
#include <iostream>

int main()
{
    std::locale l1; // classic C localse
    std::locale l2("en_US.UTF-8");
    std::locale::global(l2);
    std::cout << std::locale("").name() << std::endl; // return a copy of global locale

    std::locale l3(l1, l2, std::locale::all);

    std::cout << "l1: " << l1.name() << std::endl;
    std::cout << "l2: " << l2.name() << std::endl;
    std::cout << "l3: " << l3.name() << std::endl;
}