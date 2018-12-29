#include <regex>
#include <string>
#include <iostream>
#include <set>

using namespace std;

typedef int Car;
using Factory = std::set<int>;
using Store = std::set<Car>;

int main()
{
    string data = "business=B2C";
    regex re("business=(.*)");
    smatch m;
    if (regex_search(data, m, re))
    {
        cout << m.size() << endl;
        cout << m[1] << endl;
    }

    Factory f{1, 2, 3};
    Store s{3, 2, 1};

    f == s;
}