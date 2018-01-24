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
 * reproduced. Any commercial use of this code requires the explicit written
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
#include <cstring>
#include "blob.h"

using namespace std;
using std::cin; using std::cout; using std::endl;

template<typename T>
void print(T &t) {
    while (t.size()) {
        cout << t.back() << endl;
        t.pop_back();
    }
}

template<typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) { return -1; }
    if (v2 < v1) { return 1; }
    return 0;
}

template<>
int compare(const char *const &v1, const char *const &v2) {
    return strcmp(v1, v2);
}

int main() {
    Blob<string> b1;
    {
        Blob<string> b2 = {"a", "an", "the"};
        b1 = b2;
        cout << (b1 == b2 ? "true" : "false") << endl;
        b2.push_back("about");
        cout << b2.size() << endl;
        print(b2);
    }
    cout << b1.size() << endl;
    Blob<string> b3 = b1;
    cout << b3.size() << endl;

    // == or !=
    cout << (b1 == b3 ? "true" : "false") << endl;
    b3.pop_back();
    cout << (b1 == b3 ? "true" : "false") << endl;
    b1.pop_back();
    cout << (b1 == b3 ? "true" : "false") << endl;

    b3.pop_back();
    cout << (b1 == b3 ? "true" : "false") << endl;
    b1.pop_back();
    cout << (b1 == b3 ? "true" : "false") << endl;

    Blob<string> b4;
    cout << (b1 == b4 ? "true" : "false") << endl;
    Blob<string> b5;
    cout << (b5 == b4 ? "true" : "false") << endl;

    // arithmetic
    int array[] = {1, 2, 3, 4};
    int *p = array;
    cout << *(2 + p) << endl;

    // member template
    cout << "shared_ptr: forward parameters to ctor" << endl;
    Blob<int> mt(begin(array), end(array));
    print(mt);

    // unique_ptr
    cout << "\nunique_ptr" << endl;
    exercise::unique_ptr<Blob<string>> up(new Blob<string>);
    up->push_back("hello");
    up->push_back("world");
    up->push_back("smart-pointer");
    cout << up->size() << endl;
    up->pop_back();
    up->pop_back();
    up->pop_back();
    cout << up->size() << endl;

    // 16.39
    cout << compare("hello", "world") << endl;              // must be same length for initialization
    cout << compare<const char *>("wold", "hello") << endl; // more elegant solution

    // cleanup
    cout << endl << "cleanup\n";
    return 0;
}
