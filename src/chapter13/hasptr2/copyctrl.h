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
public:
    // default ctor
    HasPtr(const std::string &s = std::string()) :
            ps(new std::string(s)), cnt(new std::size_t(1)), i(0) {}

    // copy ctor
    HasPtr(const HasPtr &p) : ps(p.ps), cnt(p.cnt), i(p.i) { ++*cnt; }

    // copy-assignment operator
    HasPtr &operator=(const HasPtr &p);

    // dtor
    ~HasPtr();

private:
    std::string *ps;
    std::size_t *cnt;
    int i;
};

HasPtr::~HasPtr() {
    if (--*cnt == 0) {
        delete ps;
        delete cnt;
    }
}

HasPtr &HasPtr::operator=(const HasPtr &p) {
    ++*p.cnt;
    if (--*cnt == 0) {
        delete ps;
        delete cnt;
    }
    ps = p.ps;
    cnt = p.cnt;
    i = p.i;
    return *this;
}

#endif
