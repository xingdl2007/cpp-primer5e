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

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using std::cin;
using std::cout;   using std::endl;
using std::vector; using std::string;

void homework312() {
    std::vector<std::vector<int>> ivec;
    std::vector<std::string> svec(10, "null");
    for (const auto &s:svec) {
        std::cout << s << std::endl;
    }
}

void homework313() {
    vector<int> v1;
    vector<int> v2(10);
    vector<int> v3(10, 42);
    vector<int> v4{10};
    vector<int> v5{10, 42};
    vector<string> v6{10};
    vector<string> v7{10, "hi"};
    vector<string> v8(10, "hi");

    cout << "v1: " << v1.size() << ", " << endl;
    cout << "v2: " << v2.size() << ", " << endl;
    cout << "v3: " << v3.size() << ", " << endl;
    cout << "v4: " << v4.size() << ", " << endl;
    cout << "v5: " << v5.size() << ", " << endl;
    cout << "v6: " << v6.size() << ", " << endl;
    cout << "v7: " << v7.size() << ", " << endl;
    cout << "v8: " << v8.size() << ", " << endl;

    for (auto it = v7.cbegin(); it != v7.cend(); ++it) {
        cout << *it << endl;
    }
}

void homework314() {
    vector<int> vec;
    int num;
    while (cin >> num) {
        vec.push_back(num);
    }
}

void homework315() {
    vector<string> vec;
    string str;
    while (cin >> str) {
        vec.push_back(str);
    }
}

void toupper(string &str) {
    for (auto &c:str) {
        c = std::toupper(c);
    }
}

void homework317() {
    vector<string> vec;
    string str;
    while (cin >> str) {
        toupper(str);
        vec.push_back(str);
    }
    for (const string &s:vec) {
        cout << s << endl;
    }
}

void homework320() {
    vector<int> vec;
    int num;
    while (cin >> num) {
        vec.push_back(num);
    }
    for (decltype(vec.size()) i = 0; i != vec.size() - 1; i++) {
        cout << vec[i] + vec[i + 1] << endl;
    }

    cout << endl;
    for (decltype(vec.size()) i = 0; i != vec.size() / 2; i++) {
        cout << vec[i] + vec[vec.size() - i - 1] << endl;
    }
    if (vec.size() % 2 != 0) {
        cout << vec[vec.size() / 2] * 2 << endl;
    }
}

int main() {
    //homework312();
    //homework313();
    //homework314();
    //homework315();
    //homework317();
    //homework320();

    return 0;
}
