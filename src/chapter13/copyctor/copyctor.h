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

#ifndef _COPYCTOR_H_
#define _COPYCTOR_H_

class FOO {
public:
    FOO() = default;

    // if define with FOO(const FOO lhs), compiler will not accept
    // error: invalid constructor; you probably meant 'FOO (const FOO&)'
    FOO(const FOO &lhs) = default;

    int value = 0;
};

// 13.5
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) :
            ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr &rhs) :
            ps(new std::string(*rhs.ps)), i(rhs.i) {}

    HasPtr &operator=(const HasPtr &rhs) {
        if (this != &rhs) {
            delete ps;
            ps = new std::string(*rhs.ps);
            i = rhs.i;
        }
        return *this;
    }

    ~HasPtr() { delete ps; }

private:
    std::string *ps;
    int i;
};

// 13.13
struct X {
    X() { std::cout << "X()" << std::endl; }

    X(const X &) { std::cout << "X(const X&)" << std::endl; }

    X &operator=(const X &) {
        std::cout << "X &operator=(const X&)" << std::endl;
        return *this;
    }

    ~X() { std::cout << "~X()" << std::endl; }
};

// 13.17
class numberd {
public:
    numberd() : mysn(src++) {}

    numberd(const numberd &rhs) : mysn(src++) {}

    int mysn;
private:
    static int src;
};

void f(numberd s) {
    std::cout << s.mysn << std::endl;
}

void f2(const numberd &s) {
    std::cout << s.mysn << std::endl;
}

// 13.18
class Employee {
public:
    Employee() = default;

    Employee(std::string name_) :
            name(name_), id(src++) {}

private:
    std::string name;
    int id;
    static int src;
};

class TreeNode {
    TreeNode() : count(0), left(nullptr), right(nullptr) {}

private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;
};

class BinStrTree {
    BinStrTree() : root(nullptr) {}

private:
    TreeNode *root;
};

#endif