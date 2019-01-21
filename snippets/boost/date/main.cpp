#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>

using namespace boost::gregorian;
using namespace std;
int main(int argc, char const *argv[])
{
    date d1(2019, 1, 15);
    date d2(1970, 1, 1);

    std::cout << d1 - d2 << std::endl;
    return 0;
}
