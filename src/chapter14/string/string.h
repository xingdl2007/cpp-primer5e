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

#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <memory>
#include <utility>
#include <iostream>

class String {
    friend std::ostream &operator<<(std::ostream &, const String &);

    friend bool operator==(const String &, const String &);

    friend bool operator<(const String &, const String &);

public:
    String() : element(nullptr), first_free(nullptr), cap(nullptr) {}

    String(const char *);

    String(const String &s);

    String(String &&) noexcept;

    String &operator=(const String &rhs);

    String &operator=(String &&);

    String &operator+=(const String &s);

    char &operator[](std::size_t n) { return element[n]; }

    const char &operator[](std::size_t n) const { return element[n]; }

    ~String() { free(); }

    std::size_t size() const { return first_free - element; }

    std::size_t capacity() const { return cap - element; }

    char *begin() const { return element; }

    char *end() const { return first_free; }

private:
    static std::allocator<char> alloc;
    char *element;
    char *first_free;
    char *cap;

    void reallocate();

    void free();

    void check() { if (size() == capacity()) reallocate(); }

    std::pair<char *, char *> copy(const char *, const char *);
};

std::ostream &operator<<(std::ostream &, const String &);

bool operator==(const String &, const String &);

bool operator!=(const String &, const String &);

bool operator<(const String &, const String &);

#endif
