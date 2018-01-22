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
#include "strblob.h"

using namespace std;
using std::cin; using std::cout; using std::endl;

int main() {
    // ref: vector
    const std::vector<int> a = {1, 2, 3};
    for (std::vector<int>::const_iterator it = a.begin(); it != a.end(); ++it) {
    }

    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        cout << (b1 == b2 ? "true" : "false") << endl;
        b2.push_back("about");
        cout << b2.size() << endl;
    }

    cout << b1.size() << endl;
    for (auto it = b1.begin(); it != b1.end(); it.incr()) {
        cout << it.deref() << endl;
        it.deref() += "-";
    }

    StrBlob b3 = b1;
    cout << b3.size() << endl;
    for (auto it = b3.begin(); it != b3.end(); it.incr()) {
        cout << it.deref() << endl;
    }

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

    StrBlob b4;
    cout << (b1 == b4 ? "true" : "false") << endl;
    StrBlob b5;
    cout << (b5 == b4 ? "true" : "false") << endl;


    // <
    cout << "\n <....\n";
    vector<int> ivec;
    vector<int> ivec2 = {1, 2, 3};
    cout << (ivec < ivec2 ? "true" : "false") << endl;
    cout << (ivec < ivec ? "true" : "false") << endl;
    ivec = {1, 2, 3};
    cout << (ivec < ivec2 ? "true" : "false") << endl;
    cout << (ivec < ivec ? "true" : "false") << endl;

    auto it = ivec2.begin();
    cout << it[0] << endl;
    ++it;
    cout << it[0] << endl;
    ++it;
    cout << it[0] << endl;
    return 0;
}
