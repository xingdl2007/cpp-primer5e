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
        b2.push_back("about");
        cout << b2.size() << endl;
    }

    cout << b1.size() << endl;
    for (auto it = b1.begin(); neq(it, b1.end()); it.incr()) {
        cout << it.deref() << endl;
        it.deref() += "-";
    }

    const StrBlob b3 = b1;
    cout << b3.size() << endl;
    for (auto it = b3.begin(); neq(it, b3.end()); it.incr()) {
        cout << it.deref() << endl;
    }
    return 0;
}