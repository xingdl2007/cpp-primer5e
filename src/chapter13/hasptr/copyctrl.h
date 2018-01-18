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

#ifndef _COPYCTRL_H_
#define _COPYCTRL_H_

#include <string>

class HasPtr {
    friend void swap(HasPtr &, HasPtr &);

public:
    // default ctor
    HasPtr(const std::string &s = std::string(), int n = 0) :
            ps(new std::string(s)), i(n) {}

    // copy ctor
    HasPtr(const HasPtr &p) :
            ps(new std::string(*p.ps)), i(p.i) {}

    // copy-assignment operator
    HasPtr &operator=(HasPtr p);

    bool operator<(const HasPtr &p) { return i < p.i; }

    // dtor
    ~HasPtr() { delete ps; }

private:
    std::string *ps;
    int i;
};

// interesting
inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    std::cout << lhs.i << "<-swap->" << rhs.i << std::endl;

    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

// seems better version for value-semantic HasPtr
HasPtr &HasPtr::operator=(HasPtr p) {
    swap(*this, p);
    return *this;
}

#endif
