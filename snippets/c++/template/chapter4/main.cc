#include <array>
#include "varprint.hpp"

int main(int argc, char const *argv[])
{
    std::array a{42, 45, 77};
    printByIdx(a, Indices<0, 1, 2>());
    return 0;
}
