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
#include <list>
#include <deque>
#include <iomanip>

using std::string;
using std::to_string; using std::stod;
using std::cout; using std::endl;
using std::vector; using std::list; using std::deque;

typedef vector<int>::iterator iter;

iter find(iter b, iter e, int v) {
    while (b != e) {
        if (*b == v) {
            return b;
        }
        b++;
    }
    return e;
}

void printVec(const vector<int> &vi) {
    // print the vector's elements
    auto iter = vi.begin();
    while (iter != vi.end()) {
        cout << *iter++ << endl;
    }
}

void replace(string &s, const string &o, const string &n) {
    for (string::size_type pos = 0; (pos = s.find(o, pos)) != string::npos;) {
        s.replace(pos, o.size(), n);
        pos += n.size();
    }
}


int main() {
    vector<int> ivec = {1, 2, 3, 5, 8};
    auto res = find(ivec.begin(), ivec.end(), 18);
    if (res == ivec.end()) {
        cout << "no" << endl;
    }

    // 9.1
    list<int> ilist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vector<double> dvec(ilist.begin(), ilist.end());
    vector<double> dvec2(ivec.begin(), ivec.end());


    // 9.14
    list<const char *> clist = {"hello", "world"};
    vector<string> svec(clist.begin(), clist.end());

    // 9.20
    deque<int> idq1, idq2;
    for (auto i:ilist) {
        if (i % 2) {
            idq1.push_back(i);
        } else {
            idq2.push_back(i);
        }
    }
    cout << ilist.size() << " " << idq1.size() << " " << idq2.size() << endl;

    // 9.22
    int some_val = 2;
    vector<int>::iterator iter = ivec.begin();
    while (iter != ivec.begin() + ivec.size() / 2) {
        if (*iter == some_val) {
            iter = ivec.insert(iter, 2 * some_val);
            iter += 2;
        } else {
            ++iter;
        }
    }
    for (auto i:ivec) {
        cout << i << endl;
    }

    vector<int> evec;
    // out-of-range exception
    //cout << evec.at(0);

    // segmentation fault
    //cout << evec[0];

    // segmentation fault
    //cout << evec.front();

    // segmentation faule
    //cout << evec.back();

    // 9.29
    cout << ivec.size() << " " << ivec.capacity() << endl;
    while (ivec.size() < 25) {
        ivec.push_back(0);
    }
    cout << ivec.size() << " " << ivec.capacity() << endl;
    ivec.resize(106);
    cout << ivec.size() << " " << ivec.capacity() << endl;
    ivec.resize(5);
    cout << ivec.size() << " " << ivec.capacity() << endl;

    // 9.33
    cout << endl;
    printVec(ivec);
    cout << endl;

    auto begin = ivec.begin();
    while (begin != ivec.end()) {
        ++begin;
        begin = ivec.insert(begin, 42);
        ++begin;
    }
    printVec(ivec);

    // 9.41
    vector<char> cvec = {'h', 'e', 'l', 'l', 'o'};
    string str(cvec.begin(), cvec.end());
    cout << str << endl;

    // 9.43
    string test = "he thru llo tho you! tho hello";
    replace(test, "tho", "though");
    replace(test, "thru", "through");
    cout << test << endl;

    // 9.48
    string data = "ab2c3d7R4E6";
    for (string::size_type pos = 0;
         (pos = data.find_first_of("0123456789", pos)) != string::npos;) {
        cout << pos++ << endl;
    }
    cout << data << endl;
    for (string::size_type pos = 0;
         (pos = data.find_first_not_of("0123456789", pos)) != string::npos;) {
        cout << pos++ << endl;
    }

    // 9.50
    vector<string> nvec = {"1", "2", "3", "4"};
    int sum = 0;
    for (const auto &n :nvec) {
        sum += std::stoi(n);
    }
    cout << sum << endl;
}
