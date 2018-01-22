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

int add(int a, int b) { return a + b; }

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
    return 0;
}
