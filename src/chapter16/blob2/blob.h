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

#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include "smart_pointer.h"

/*
 * Blob
 */
// forward declaration needed for friend declaration in Blob
template<typename>
class Blob;

template<typename>
class BlobPtr;

template<typename T>
bool operator==(const Blob<T> &, const Blob<T> &);

template<typename T>
bool operator<(const Blob<T> &, const Blob<T> &);

template<typename T>
class Blob {
    using DataType = std::vector<T>;

    friend class BlobPtr<T>;

    friend bool operator==<T>(const Blob<T> &, const Blob<T> &);

    friend bool operator<
            <T>(const Blob<T> &, const Blob<T> &);

public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;

    // constructors
    Blob() : data(exercise::make_shared<DataType>()) {}

    Blob(std::initializer_list<T> il);

    template<typename It>
    Blob(It b, It e);

    // copy ctor
    Blob(const Blob &s);

    // copy-assignment operator
    Blob &operator=(const Blob &s);

    // size operations
    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const T &t) { data->push_back(t); }

    void pop_back() { data->pop_back(); };

    // element access
    T &front() { return data->front(); };

    T &back() { return data->back(); };

    T &operator[](std::size_t n) {
        check(n, "out of range");
        return (*data)[n];
    }

    const T &operator[](std::size_t n) const { return (*data)[n]; }

private:
    exercise::shared_ptr<DataType> data;

    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const {
        if (i > size()) {
            throw std::out_of_range(msg);
        }
    }
};

// constructor
template<typename T>
inline Blob<T>::Blob(std::initializer_list<T> il) :
        data(exercise::make_shared<DataType>(il)) {}

// copy ctor
template<typename T>
Blob<T>::Blob(const Blob &s)
        : data(exercise::shared_ptr<DataType>()) {
    auto *vec = new std::vector<T>(*s.data);
    data.reset(vec);
}

template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e):data(exercise::make_shared<DataType>(b, e)) {}

// copy-assignment operator
template<typename T>
Blob<T> &Blob<T>::operator=(const Blob &s) {
    auto *vec = new std::vector<T>(*s.data);
    data.reset(vec);
    return *this;
}

template<typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
    if (lhs.data == rhs.data) { return true; }
    if (lhs.data && rhs.data && *lhs.data == *rhs.data) { return true; }
    return false;
}

template<typename T>
bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs) {
    return !(lhs == rhs);
}

template<typename T>
bool operator<(const Blob<T> &lhs, const Blob<T> &rhs) {
    if (lhs.size() < rhs.size()) { return true; }
    if (lhs.size() > rhs.size()) { return false; }
    if (lhs.data && rhs.data) {
        return *lhs.data < *rhs.data;
    }
    return true;
}

#endif
