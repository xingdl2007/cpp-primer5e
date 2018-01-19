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
#include "copyctor.h"

int numberd::src = 0;
int Employee::src = 0;

X test(X x) {
    return x;
}

X test2(X &x) {
    return x;
}

void xx() {
    // 13.13
    {
        X x;
        X x2 = test(x);
    }

    std::cout << std::endl;

    {
        X x;
        X x2 = test2(x);
    }

    std::cout << std::endl;

    {
        X *x3 = new X();
        delete x3;
    }

    std::cout << std::endl;
    std::vector<X> xvec(3);

}

void num() {
    numberd a, b = a, c = b;
    f(a);
    f(b);
    f(c);
}

void num2() {
    numberd a, b = a, c = b;
    f2(a);
    f2(b);
    f2(c);
}

int f() { return 0; }

int main() {
    FOO f1;
    FOO f2 = f1;
    std::cout << f2.value << std::endl;

    // copy-assignment operator
    int a, b, c = 10;
    std::cout << (a = b = c) << std::endl;

    // 13.13
    xx();

    // 13.17
    std::cout << std::endl;
    //num();
    num2();

    // 13.46
    std::vector<int> vi(100);
    int &&r1 = f();
    int &r2 = vi[0];
    int &r3 = r1;
    int &&r4 = vi[0] * f();

    std::cout << r1 << " " << r2 << " " << r3 << " " << r4 << std::endl;

    return 0;
}