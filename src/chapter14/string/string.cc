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
#include <cstring>

#include "string.h"

std::allocator<char> String::alloc;

// double strategy
void String::reallocate() {
    auto old_size = size();
    auto new_size = old_size ? 2 * old_size : 1;
    auto new_data = alloc.allocate(new_size);
    std::uninitialized_copy(element, first_free, new_data);
    free();
    element = new_data;
    first_free = element + old_size;
    cap = element + new_size;
}

std::pair<char *, char *> String::copy(const char *b, const char *e) {
    auto start = alloc.allocate(e - b);
    return {start, std::uninitialized_copy(b, e, start)};
}

void String::free() {
    if (element) {
        for (auto p = first_free; p != element;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(element, capacity());
    }
}

String::String(const char *literal) {
    auto pair = copy(literal, literal + std::strlen(literal));
    element = pair.first;
    first_free = cap = pair.second;
    std::cout << "String::String(const char *literal)" << std::endl;
}

String::String(String &&s) noexcept
        : element(s.element), first_free(s.first_free), cap(s.cap) {
    s.element = s.first_free = s.cap = nullptr;
    std::cout << "String::String(String &&s)" << std::endl;
}

String::String(const String &s) {
    auto pair = copy(s.begin(), s.end());
    element = pair.first;
    first_free = cap = pair.second;

    std::cout << "String(const String &s)" << std::endl;
}

String &String::operator=(const String &rhs) {
    if (this != &rhs) {
        free();
        auto pair = copy(rhs.begin(), rhs.end());
        element = pair.first;
        first_free = cap = pair.second;
    }
    std::cout << "String &String::operator=(const String &rhs)" << std::endl;
    return *this;
}

String &String::operator=(String &&rhs) {
    if (this != &rhs) {
        free();
        element = rhs.element;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.element = rhs.first_free = rhs.cap = nullptr;
    }
    std::cout << "String &String::operator=(String &&rhs)" << std::endl;
    return *this;
}

String &String::operator+=(const String &s) {
    while (size() + s.size() > capacity()) {
        reallocate();
    }
    std::uninitialized_copy(s.begin(), s.end(), first_free);
    first_free += s.size();
    std::cout << "String &String::operator+=(const String &s)" << std::endl;

    return *this;
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    if (s.element) {
        auto it = s.element;
        while (it != s.first_free) {
            out << *it++;
        }
    }
    return out;
}

bool operator==(const String &lhs, const String &rhs) {
    if (&lhs == &rhs) { return true; }
    if (lhs.size() != rhs.size()) { return false; }
    auto it1 = lhs.begin(), it2 = lhs.begin();
    while (it1 != lhs.end()) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return true;
}

bool operator!=(const String &lhs, const String &rhs) {
    return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs) {
    if (lhs.size() < rhs.size()) { return true; }
    if (lhs.size() > rhs.size()) { return false; }
    auto it1 = lhs.begin(), it2 = lhs.begin();
    while (it1 != lhs.end()) {
        if (*it1 == *it2) {
            ++it1;
            ++it2;
            continue;
        }
        return *it1 < *it2;
    }
    return false;
}