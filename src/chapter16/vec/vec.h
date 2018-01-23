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

#ifndef _VEC_H_
#define _VEC_H_

#include <memory>
#include <utility>
#include <initializer_list>

template<typename T>
class Vec;

template<typename T>
bool operator==(const Vec<T> &, const Vec<T> &);

template<typename T>
bool operator<(const Vec<T> &, const Vec<T> &);

template<typename T>
class Vec {
    friend bool operator==<T>(const Vec<T> &, const Vec<T> &);

    friend bool operator<
            <T>(const Vec<T> &, const Vec<T> &);

public:
    Vec() : element(nullptr), first_free(nullptr), cap(nullptr) {}

    Vec(const Vec &);

    Vec(Vec &&) noexcept;

    Vec &operator=(const Vec &);

    Vec &operator=(Vec &&);

    Vec(std::initializer_list<T>);

    Vec &operator=(std::initializer_list<T>);

    ~Vec();

    void push_back(const T &);

    void push_back(T &&);

    void resize(std::size_t);

    void resize(std::size_t, const T &);

    void reserve(std::size_t);

    std::size_t size() const { return first_free - element; }

    std::size_t capacity() const { return cap - element; }

    T *begin() const { return element; }

    T *end() const { return first_free; }

    T &operator[](std::size_t n) { return element[n]; }

    const T &operator[](std::size_t n) const { return element[n]; }

private:
    static std::allocator<T> alloc;

    void check_n_alloc() {
        if (size() == capacity()) {
            reallocate();
        }
    }

    std::pair<T *, T *> alloc_n_copy(const T *, const T *);

    void free();

    void reallocate();

    void reallocate(std::size_t);

    T *element;
    T *first_free;
    T *cap;
};

template<typename T>
inline bool operator==(const Vec<T> &lhs, const Vec<T> &rhs) {
    if (&lhs == &rhs) { return true; }
    if (lhs.size() != rhs.size()) { return false; }
    auto it1 = lhs.begin(), it2 = rhs.begin();
    while (it1 != lhs.end()) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1;
        ++it2;
    }
    return true;
}

template<typename T>
inline bool operator!=(const Vec<T> &lhs, const Vec<T> &rhs) {
    return !(lhs == rhs);
}

template<typename T>
inline bool operator<(const Vec<T> &lhs, const Vec<T> &rhs) {
    if (lhs.size() < rhs.size()) { return true; }
    if (lhs.size() > rhs.size()) { return false; }
    auto it1 = lhs.begin(), it2 = rhs.begin();
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


template<typename T>
std::allocator<T> Vec<T>::alloc;

template<typename T>
std::pair<T *, T *> Vec<T>::alloc_n_copy(const T *b, const T *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
};

template<typename T>
void Vec<T>::push_back(const T &s) {
    check_n_alloc();
    alloc.construct(first_free++, s);
}

template<typename T>
void Vec<T>::push_back(T &&s) {
    check_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

template<typename T>
void Vec<T>::free() {
    if (element) {
        for (auto p = first_free; p != element;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(element, cap - element);
    }
}

template<typename T>
Vec<T>::Vec(std::initializer_list<T> li) {
    for (auto &s:li) {
        check_n_alloc();
        alloc.construct(first_free++, s);
    }
}

template<typename T>
Vec<T>::Vec(const Vec &sv) {
    auto data = alloc_n_copy(sv.begin(), sv.end());
    element = data.first;
    first_free = cap = data.second;
}

template<typename T>
Vec<T>::Vec(Vec &&s) noexcept
        : element(s.element), first_free(s.first_free), cap(s.cap) {
    s.element = s.first_free = s.cap = nullptr;
}

template<typename T>
Vec<T> &Vec<T>::operator=(const Vec &rhs) {
    if (this != &rhs) {
        free();
        auto data = alloc_n_copy(rhs.begin(), rhs.end());
        element = data.first;
        first_free = cap = data.second;
    }
    return *this;
}

template<typename T>
Vec<T> &Vec<T>::operator=(Vec &&rhs) {
    if (this != &rhs) {
        free();
        element = rhs.element;
        first_free = rhs.first_free;
        cap = rhs.cap;

        rhs.element = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

template<typename T>
Vec<T> &Vec<T>::operator=(std::initializer_list<T> li) {
    auto data = alloc_n_copy(li.begin(), li.end());
    free();
    element = data.first;
    first_free = cap = data.second;
    return *this;
}

template<typename T>
Vec<T>::~Vec() {
    free();
}

template<typename T>
void Vec<T>::reallocate() {
    auto newcap = size() ? 2 * size() : 1;
    reallocate(newcap);
}

template<typename T>
void Vec<T>::reallocate(std::size_t sz) {
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


template<typename T>
void Vec<T>::reserve(std::size_t n) {
    if (n > capacity()) {
        reallocate(n);
    }
}

template<typename T>
void Vec<T>::resize(std::size_t n) {
    resize(n, "");
}

template<typename T>
void Vec<T>::resize(std::size_t n, const T &s) {
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

#endif
