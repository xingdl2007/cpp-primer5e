/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 *
 * "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
 *
 *
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 *
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address:
 *
 * 	Pearson Education, Inc.
 * 	Rights and Permissions Department
 * 	One Lake Street
 * 	Upper Saddle River, NJ  07458
 * 	Fax: (201) 236-3290
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

using namespace std;
using namespace std::placeholders;

string operator+(const char *c, string s) {
    return string(c) + s;
}

// 14.34
class Demo {
public:
    int operator()(int a, int b, int c) {
        return a ? b : c;
    }
};

struct Integral {
    operator const int() { return 100; }

    operator int() const { return 150; }
};

int add(int a, int b) { return a + b; }

struct SmallInt {
    friend SmallInt operator+(const SmallInt &, const SmallInt &);

public:
    SmallInt(int = 0) {}

    operator int() const {
        cout << "SmallInt: operator int()" << endl;
        return val;
    }

private:
    std::size_t val;
};

struct LongDouble {
    LongDouble(double = 0.0) {}

    LongDouble operator+(const SmallInt &) {
        cout << " LongDouble operator+(const SmallInt &) " << endl;
        return *this;
    }

    operator double() {
        cout << "LongDouble: operator double()" << endl;
        return 1.1;
    }

    operator float() {
        cout << "LongDouble: operator float()" << endl;
        return 2.2;
    }
};

LongDouble operator+(LongDouble &l, double d) {
    LongDouble ret = l;
    cout << "LongDouble operator+(LongDouble &l, double d)" << endl;
    return ret;
}

SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs) {
    SmallInt ret = lhs;
    ret.val += rhs.val;
    cout << "SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs)" << endl;
    return ret;
}

void calc(int) { cout << "calc(int)" << endl; }

void calc(LongDouble) { cout << "calc(LongDouble)" << endl; }

int main() {
    string world = "world";
    cout << "hello" + world << endl;

    Demo demo;
    cout << demo(1, 2, 3) << endl;
    cout << demo(0, 2, 3) << endl;

    string hello = "hello", hi = "hi";
    vector<string *> nameTable = {&hello, &world, &hi};
    sort(nameTable.begin(), nameTable.end(), less<string *>());

    for_each(nameTable.begin(), nameTable.end(),
             [](const string *ptr) {
                 cout << ptr << endl;
             });

    vector<int> ivec = {1024, 1025, 9, 1100, 3, 12};
    cout << count_if(ivec.begin(), ivec.end(), bind(greater<int>(), _1, 1024)) << endl;

    vector<string> svec = {"pooh", "pooh", "skip", "pooh"};
    auto ret = find_if(svec.begin(), svec.end(), bind(not_equal_to<string>(), _1, "pooh"));
    cout << *ret << " " << ret - svec.begin() << endl;

    transform(ivec.begin(), ivec.end(), ivec.begin(), bind(multiplies<int>(), _1, 2));
    for_each(ivec.begin(), ivec.end(),
             [](int &i) {
                 cout << i << endl;
             });

    cout << (all_of(ivec.begin(), ivec.end(), bind(equal_to<int>(),
                                                   bind(modulus<int>(), _1, 2),
                                                   0)) ? "true" : "false") << endl;

    // 14.44
    map<string, function<int(int, int)>> binops = {
            {"+", add},
            {"-", std::minus<int>()},
            {"*", [](int a, int b) { return a * b; }},
            {"/", std::divides<int>()},
    };
    cout << binops["+"](10, 5) << endl;
    cout << binops["-"](10, 5) << endl;
    cout << binops["*"](10, 5) << endl;
    cout << binops["/"](10, 5) << endl;

    //
    cout << endl;
    Integral integral;
    const int i = static_cast<int>(integral);
    int ii = static_cast<int>(integral);
    cout << i << " " << ii << endl;

    cout << endl;
    LongDouble ldObj;
    //int ex1 = ldObj; // ambiguous
    float ex2 = ldObj;
    cout << ex2 << endl;

    double dval = .1;
    calc(dval);// which calc?


    cout << endl;
    SmallInt si;
    LongDouble ld;
    //ld = si + ld;
    ld = ld + si;
    //double d = si + 3.14;
    return 0;
}
