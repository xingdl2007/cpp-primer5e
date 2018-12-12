#include <ratio>
#include <limits>
#include <iostream>

using namespace std;

int main()
{
    typedef ratio<5, 3> FiveThirds;
    cout << FiveThirds::num << "/" << FiveThirds::den << endl;

    typedef ratio<25, 15> AlsoFiveThirds;
    cout << AlsoFiveThirds::num << "/" << AlsoFiveThirds::den << endl;

    ratio<42, 42> one;
    cout << one.num << "/" << one.den << endl;

    ratio<0> zero;
    cout << zero.num << "/" << zero.den << endl;

    typedef ratio<7, -3> Neg;
    cout << Neg::num << "/" << Neg::den << endl;

    typedef ratio_add<ratio<2, 7>, ratio<2, 6>>::type Compound;
    cout << Compound::num << "/" << Compound::den << endl;

    if (ratio_equal<ratio<5, 3>, ratio<15, 9>>::value)
    {
        cout << "ratio<5, 3> and ratio<15, 9> is equal" << endl;
    }
    else
    {
        cout << "ratio<5, 3> and ratio<15, 9> is not equal" << endl;
    }

    // The following two typedefs will trigger static_assert failture
    // typedef ratio_multiply<ratio<1, numeric_limits<long long>::max()>, ratio<1, 2>>::type Impossible;
    // typedef ratio_divide<FiveThirds, ratio<0>>::type Impossible;
    // ratio_divide<FiveThirds, ratio<0>>;
}