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

#include <algorithm>
#include "strVec.h"

std::allocator<std::string> StrVec::alloc;

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
};

void StrVec::push_back(const std::string &s) {
    check_n_alloc();
    alloc.construct(first_free++, s);
}

void StrVec::push_back(std::string &&s) {
    check_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

void StrVec::free() {
    if (element) {
        for (auto p = first_free; p != element;) {
            alloc.destroy(--p);
        }
//        // 13.43
//        std::for_each(element, first_free,
//                      [&](const std::string) {
//                          alloc.destroy(--first_free);
//                      });
        alloc.deallocate(element, cap - element);
    }
}

StrVec::StrVec(std::initializer_list<std::string> li) {
    for (auto &s:li) {
        check_n_alloc();
        alloc.construct(first_free++, s);
    }
}

StrVec::StrVec(const StrVec &sv) {
    auto data = alloc_n_copy(sv.begin(), sv.end());
    element = data.first;
    first_free = cap = data.second;
}

StrVec::StrVec(StrVec &&s) noexcept
        : element(s.element), first_free(s.first_free), cap(s.cap) {
    s.element = s.first_free = s.cap = nullptr;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
    if (this != &rhs) {
        free();
        auto data = alloc_n_copy(rhs.begin(), rhs.end());
        element = data.first;
        first_free = cap = data.second;
    }
    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) {
    if (this != &rhs) {
        free();
        element = rhs.element;
        first_free = rhs.first_free;
        cap = rhs.cap;

        rhs.element = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

StrVec &StrVec::operator=(std::initializer_list<std::string> li) {
    auto data = alloc_n_copy(li.begin(), li.end());
    free();
    element = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec::~StrVec() {
    free();
}

void StrVec::reallocate() {
    auto newcap = size() ? 2 * size() : 1;
    reallocate(newcap);
}

void StrVec::reallocate(std::size_t sz) {
    auto newdata = alloc.allocate(sz);
    auto dest = newdata;
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                        std::make_move_iterator(end()),
                                        dest);
    free();
    element = newdata;
    first_free = last;
    cap = element + sz;
}


void StrVec::reserve(std::size_t n) {
    if (n > capacity()) {
        reallocate(n);
    }
}

void StrVec::resize(std::size_t n) {
    resize(n, "");
}

void StrVec::resize(std::size_t n, const std::string &s) {
    if (n > size()) {
        if (n > capacity()) {
            reallocate(n);
        }
        for (auto p = first_free; p != element + n;) {
            alloc.construct(p++, s);
        }
    } else if (n < size()) {
        for (auto p = first_free; p != element + n;) {
            alloc.destroy(--p);
        }
    }
    first_free = element + n;
}
