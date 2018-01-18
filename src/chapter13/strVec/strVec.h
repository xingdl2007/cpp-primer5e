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

#ifndef _STR_VEC_H_
#define _STR_VEC_H_

#include <memory>
#include <utility>
#include <initializer_list>

class StrVec {
public:
    StrVec() : element(nullptr), first_free(nullptr), cap(nullptr) {}

    StrVec(const StrVec &);

    StrVec &operator=(const StrVec &);

    StrVec(const std::initializer_list<std::string> &li);

    ~StrVec();

    void push_back(const std::string &);

    void resize(std::size_t);

    void resize(std::size_t, const std::string &);

    void reserve(std::size_t);

    std::size_t size() const { return first_free - element; }

    std::size_t capacity() const { return cap - element; }

    std::string *begin() const { return element; }

    std::string *end() const { return first_free; }

private:
    static std::allocator<std::string> alloc;

    void check_n_alloc() {
        if (size() == capacity()) {
            reallocate();
        }
    }

    std::pair<std::string *, std::string *>
    alloc_n_copy(const std::string *, const std::string *);


    void free();

    void reallocate();

    void reallocate(std::size_t);

    std::string *element;
    std::string *first_free;
    std::string *cap;
};

#endif
