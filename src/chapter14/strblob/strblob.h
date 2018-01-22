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

// forward declaration needed for friend declaration in StrBlob
class StrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;

    friend bool operator==(const StrBlob &, const StrBlob &);

    friend bool operator<(const StrBlob &, const StrBlob &);

    using DataType = std::vector<std::string>;

public:
    typedef std::vector<std::string>::size_type size_type;

    // constructors
    StrBlob() : data(std::make_shared<DataType>()) {}

    StrBlob(std::initializer_list<std::string>
            il);

    // copy ctor
    StrBlob(
            const StrBlob &s);

    // copy-assignment operator
    StrBlob &operator=(const StrBlob &s);

    // size operations
    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }

    void pop_back() { data->pop_back(); };

    // element access
    std::string &front() { return data->front(); };

    std::string &back() { return data->back(); };

    // interface to StrBlobPtr
    StrBlobPtr begin();  // can't be defined until StrBlobPtr is
    StrBlobPtr end();

    std::string &operator[](std::size_t n) { return (*data)[n]; }

    const std::string &operator[](std::size_t n) const { return (*data)[n]; }

private:
    std::shared_ptr<DataType> data;

    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

// constructor
inline StrBlob::StrBlob(std::initializer_list<std::string> il) :
        data(std::make_shared<DataType>(il)) {}

// copy ctor
StrBlob::StrBlob(const StrBlob &s)
        : data(std::make_shared<DataType>()) {
    auto *vec = new std::vector<std::string>(*s.data);
    data.reset(vec);
}

// copy-assignment operator
StrBlob &StrBlob::operator=(const StrBlob &s) {
    auto *vec = new std::vector<std::string>(*s.data);
    data.reset(vec);
    return *this;
}

bool operator==(const StrBlob &lhs, const StrBlob &rhs) {
    if (lhs.data == rhs.data) { return true; }
    if (lhs.data && rhs.data && *lhs.data == *rhs.data) { return true; }
    return false;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs) {
    return !(lhs == rhs);
}

bool operator<(const StrBlob &lhs, const StrBlob &rhs) {
    if (lhs.size() < rhs.size()) { return true; }
    if (lhs.size() > rhs.size()) { return false; }
    if (lhs.data && rhs.data) {
        return *lhs.data < *rhs.data;
    }
    return true;
}

// StrBlobPtr throws an exception on attempts to access a nonexistent element
class StrBlobPtr {
    friend bool operator==(const StrBlobPtr &, const StrBlobPtr &);

    friend bool operator<(const StrBlobPtr &, const StrBlobPtr &);

    friend StrBlobPtr operator+(const StrBlobPtr &, std::size_t);

    friend StrBlobPtr operator-(const StrBlobPtr &, std::size_t);

    friend std::ptrdiff_t operator-(const StrBlobPtr &, const StrBlobPtr &);

public:
    StrBlobPtr() : curr(0) {}

    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    std::string &operator*() const;

    std::string *operator->() const;

    StrBlobPtr &operator++();       // prefix version
    StrBlobPtr &operator--();       // prefix version
    StrBlobPtr operator++(int);     // postfix version
    StrBlobPtr operator--(int);     // postfix version

    std::string &operator[](std::size_t);

    const std::string &operator[](std::size_t) const;

private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string &) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;      // current position within the array
};

inline std::string &StrBlobPtr::operator*() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];  // (*p) is the vector to which this object points
}

inline std::string *StrBlobPtr::operator->() const {
    return &this->operator*();
}

std::string &StrBlobPtr::operator[](std::size_t n) {
    auto p = check(curr + n, "[] past end");
    return (*p)[curr + n];
}

const std::string &StrBlobPtr::operator[](std::size_t n) const {
    auto p = check(curr + n, "const [] past end");
    return (*p)[curr + n];
}

inline std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();   // is the vector still around?
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");

    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}

// prefix: return a reference to the incremented object
inline StrBlobPtr &StrBlobPtr::operator++() {
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;       // advance the current state
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator++(int) {
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

inline StrBlobPtr &StrBlobPtr::operator--() {
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;       // move the current state back one element}
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator--(int) {
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

// begin and end members for StrBlob
inline StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end() {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

// named equality operators for StrBlobPtr
inline bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
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

inline bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    if (l && r && l == r) {
        return lhs.curr < rhs.curr;
    } else {
        return false;
    }
}

inline bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return !(lhs == rhs);
}

// arithmetic
inline StrBlobPtr operator+(const StrBlobPtr &lhs, std::size_t n) {
    StrBlobPtr ret = lhs;
    ret.curr += n;
    return ret;
}

inline StrBlobPtr operator-(const StrBlobPtr &lhs, std::size_t n) {
    StrBlobPtr ret = lhs;
    ret.curr -= n;
    return ret;
}

inline StrBlobPtr operator+(std::size_t n, const StrBlobPtr &rhs) {
    return operator+(rhs, n);
}

inline std::ptrdiff_t operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return static_cast<std::ptrdiff_t >(lhs.curr) - static_cast<std::ptrdiff_t >(rhs.curr);
}


// 14.32
class StrBlobPtrPtr {
public:
    StrBlobPtrPtr(StrBlobPtr *p) : ptr(p) {}

    StrBlobPtr &operator*() { return *ptr; }

    StrBlobPtr operator->() { return *ptr; }

private:
    StrBlobPtr *ptr;
};

#endif
