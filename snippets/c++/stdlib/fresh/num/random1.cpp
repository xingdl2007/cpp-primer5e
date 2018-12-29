#include <random>
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::default_random_engine dre; // source of randomness
    std::uniform_int_distribution<int> di(10, 20);
    for (int i = 0; i < 20; ++i)
    {
        std::cout << di(dre) << " ";
    }
    std::cout << std::endl;

    std::uniform_real_distribution<double> dr(10, 20);
    for (int i = 0; i < 8; ++i)
    {
        std::cout << dr(dre) << " ";
    }
    std::cout << std::endl;

    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(v.begin(), v.end(), dre);
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    {
        std::uniform_int_distribution<int> d;
        std::default_random_engine dre1(0);
        std::cout << d(dre1) << " ";

        std::default_random_engine dre2(11);
        std::cout << d(dre2) << std::endl;
    }
}