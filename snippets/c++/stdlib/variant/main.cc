#include <variant>
#include <iostream>
#include <variant>
#include <string>
#include <cassert>

using namespace std;
using namespace std::literals;

int main()
{
    {
        variant<int, double> var = 3.14;
        cout << var.index() << endl;
        cout << var.valueless_by_exception() << endl;
    }

    // example from cpp-reference
    {
        std::variant<int, float> v, w;
        v = 12; // v contains int
        int i = std::get<int>(v);
        w = std::get<int>(v);
        w = std::get<0>(v); // same effect as the previous line
        w = v;              // same effect as the previous line

        // std::get<double>(v); // error: no double in [int, float]
        // std::get<3>(v);      // error: valid index values are 0 and 1

        try
        {
            std::get<float>(w); // w contains int, not float: will throw
        }
        catch (const std::bad_variant_access &)
        {
            cout << "std::get<float>(): throw exception" << endl;
        }

        std::variant<std::string> x("abc"); // converting constructors work when unambiguous
        x = "def";                          // converting assignment also works when unambiguous

        std::variant<std::string, bool> y("abc"); // casts to bool when passed a char const *
        assert(std::holds_alternative<bool>(y));  // succeeds
        y = "xyz"s;
        assert(std::holds_alternative<std::string>(y)); //succeeds
    }
}