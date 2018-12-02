#include <iostream>

void *operator new(size_t n)
{
    std::cout << "[allocating " << n << " bytes]\n";
    return malloc(n);
}

bool compare(std::string const &s1, std::string const &s2)
{
    if (s1 == s2)
        return true;
    std::cout << '\"' << s1 << "\" does not match \"" << s2 << "\"\n";
    return false;
}

int main()
{
    std::string str = "this is my input string";

    compare(str, "this is the first test string");
    compare(str, "this is the second test string");
    compare(str, "this is the third test string");
}