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
    Blob() : data(std::make_shared<DataType>()) {}

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

    // interface to BlobPtr
    BlobPtr<T> begin();  // can't be defined until BlobPtr is
    BlobPtr<T> end();

    T &operator[](std::size_t n) { return (*data)[n]; }

    const T &operator[](std::size_t n) const { return (*data)[n]; }

private:
    std::shared_ptr<DataType> data;

    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

// constructor
template<typename T>
inline Blob<T>::Blob(std::initializer_list<T> il) :
        data(std::make_shared<DataType>(il)) {}

// copy ctor
template<typename T>
Blob<T>::Blob(const Blob &s)
        : data(std::shared_ptr<DataType>()) {
    auto *vec = new std::vector<T>(*s.data);
    data.reset(vec);
}

template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e):data(std::make_shared<DataType>(b, e)) {}

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


/*
 *  BlobPtr
 */
template<typename T>
bool operator==(const BlobPtr<T> &, const BlobPtr<T> &);

template<typename T>
bool operator<(const BlobPtr<T> &, const BlobPtr<T> &);

template<typename T>
BlobPtr<T> operator+(const BlobPtr<T> &, std::size_t);

template<typename T>
BlobPtr<T> operator-(const BlobPtr<T> &, std::size_t);

template<typename T>
std::ptrdiff_t operator-(const BlobPtr<T> &, const BlobPtr<T> &);

// BlobPtr throws an exception on attempts to access a nonexistent element
template<typename T>
class BlobPtr {
    friend bool operator==<T>(const BlobPtr<T> &, const BlobPtr<T> &);

    friend bool operator<
            <T>(const BlobPtr<T> &, const BlobPtr<T> &);

    friend BlobPtr<T> operator+<T>(const BlobPtr<T> &, std::size_t);

    friend BlobPtr<T> operator-<T>(const BlobPtr<T> &, std::size_t);

    friend std::ptrdiff_t operator-<T>(const BlobPtr<T> &, const BlobPtr<T> &);

public:
    BlobPtr() : curr(0) {}

    BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    T &operator*() const;

    T *operator->() const;

    BlobPtr &operator++();       // prefix version
    BlobPtr &operator--();       // prefix version
    BlobPtr operator++(int);     // postfix version
    BlobPtr operator--(int);     // postfix version

    T &operator[](std::size_t);

    const T &operator[](std::size_t) const;

private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<T>>
    check(std::size_t, const std::string &) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;      // current position within the array
};

template<typename T>
inline T &BlobPtr<T>::operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];  // (*p) is the vector to which this object points
}

template<typename T>
inline T *BlobPtr<T>::operator->() const {
    return &this->operator*();
}

template<typename T>
T &BlobPtr<T>::operator[](std::size_t n) {
    auto p = check(curr + n, "[] past end");
    return (*p)[curr + n];
}

template<typename T>
const T &BlobPtr<T>::operator[](std::size_t n) const {
    auto p = check(curr + n, "const [] past end");
    return (*p)[curr + n];
}

template<typename T>
inline std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();   // is the vector still around?
    if (!ret)
        throw std::runtime_error("unbound BlobPtr");

    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}

// prefix: return a reference to the incremented object
template<typename T>
inline BlobPtr<T> &BlobPtr<T>::operator++() {
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of BlobPtr");
    ++curr;       // advance the current state
    return *this;
}

template<typename T>
inline BlobPtr<T> BlobPtr<T>::operator++(int) {
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template<typename T>
inline BlobPtr<T> &BlobPtr<T>::operator--() {
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;       // move the current state back one element}
    check(curr, "decrement past begin of BlobPtr");
    return *this;
}

template<typename T>
inline BlobPtr<T> BlobPtr<T>::operator--(int) {
    BlobPtr ret = *this;
    --*this;
    return ret;
}

// begin and end members for StrBlob
template<typename T>
inline BlobPtr<T> Blob<T>::begin() {
    return BlobPtr<T>(*this);
}

template<typename T>
inline BlobPtr<T> Blob<T>::end() {
    auto ret = BlobPtr<T>(*this, data->size());
    return ret;
}

// named equality operators for BlobPtr
template<typename T>
inline bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    // if the underlying vector is the same
    if (l == r) {
        // then they're equal if they're both null or
        // if they point to the same element
        return (!r || lhs.curr == rhs.curr);
    } else {
        return false; // if they point to difference vectors, they're not equal
    }
}

template<typename T>
inline bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    if (l && r && l == r) {
        return lhs.curr < rhs.curr;
    } else {
        return false;
    }
}

template<typename T>
inline bool operator!=(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    return !(lhs == rhs);
}

// arithmetic
template<typename T>
inline BlobPtr<T> operator+(const BlobPtr<T> &lhs, std::size_t n) {
    BlobPtr<T> ret = lhs;
    ret.curr += n;
    return ret;
}

template<typename T>
inline BlobPtr<T> operator-(const BlobPtr<T> &lhs, std::size_t n) {
    BlobPtr<T> ret = lhs;
    ret.curr -= n;
    return ret;
}

template<typename T>
inline BlobPtr<T> operator+(std::size_t n, const BlobPtr<T> &rhs) {
    return operator+(rhs, n);
}

template<typename T>
inline std::ptrdiff_t operator-(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    return static_cast<std::ptrdiff_t >(lhs.curr) - static_cast<std::ptrdiff_t >(rhs.curr);
}

#endif
