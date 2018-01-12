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
#include <memory>

using std::cin; using std::cout; using std::endl;
using std::vector; using std::shared_ptr;

vector<int> *factory() {
    return new vector<int>();
}

vector<int> *fill(vector<int> *ivec) {
    for (int i = 1; i <= 10; i++) {
        ivec->push_back(i);
    }
    return ivec;
}

void print(vector<int> *ivec) {
    auto b = ivec->cbegin(), e = ivec->cend();
    while (b != e) {
        cout << *b << endl;
        ++b;
    }
    delete ivec;
}

// shared_ptr version
shared_ptr<vector<int>> factory2() {
    return std::make_shared<vector<int>>();
}

shared_ptr<vector<int>> fill2(shared_ptr<vector<int>> ivec) {
    for (int i = 1; i <= 10; i++) {
        ivec->push_back(11 - i);
    }
    return ivec;
}

void print2(shared_ptr<vector<int>> ivec) {
    auto b = ivec->cbegin(), e = ivec->cend();
    while (b != e) {
        cout << *b << endl;
        ++b;
    }
}

void process(shared_ptr<int> ptr) {
    cout << *ptr << endl;
}

int main() {
    // new/read/print
    print(fill(factory()));

    // shared_ptr version
    print2(fill2(factory2()));

    //
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p));
    cout << *p << endl;
    return 0;
}
