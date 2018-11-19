#include <fstream>
#include <iostream>

// std::cout's original buffer is not restored
int main()
{
    std::ofstream log("oops.log");
    std::cout.rdbuf(log.rdbuf());
    std::cout << "ooops!\n";
    return 0;
}