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

#ifndef _STRBLOB_H_
#define _STRBLOB_H_

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <stdexcept>

// forward declaration needed for friend declaration in StrBlob
class StrBlobPtr;

class ConstStrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;

    friend class ConstStrBlobPtr;

public:
    typedef std::vector<std::string>::size_type size_type;

    // constructors
    StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

    StrBlob(std::initializer_list<std::string> il)
            : data(std::make_shared<std::vector<std::string>>(il)) {};

    // size operations
    size_type size() const { return data->size(); }

    bool empty() const { return data->empty(); }

    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }

    void pop_back();

    // element access, overloaded with const
    std::string &front();

    const std::string &front() const;

    std::string &back();

    const std::string &back() const;

    // interface to StrBlobPtr, can't be defined until StrBlobPtr is
    StrBlobPtr begin();

    StrBlobPtr end();

    ConstStrBlobPtr begin() const;

    ConstStrBlobPtr cbegin() const;

    ConstStrBlobPtr end() const;

    ConstStrBlobPtr cend() const;

private:
    std::shared_ptr<std::vector<std::string>> data;

    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};

inline void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

inline std::string &StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

inline const std::string &StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

inline std::string &StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

inline const std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

inline void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

// accompany class
// StrBlobPtr throws an exception on attempts to access a nonexistent element
class StrBlobPtr {
    friend bool eq(const StrBlobPtr &, const StrBlobPtr &);

public:
    StrBlobPtr() : curr(0) {}

    // const or not const?
    explicit StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    std::string &deref() const;

    StrBlobPtr &incr();       // prefix version
    StrBlobPtr &decr();       // prefix version
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string &) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;      // current position within the array
};

// key point
inline std::string &StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];  // (*p) is the vector to which this object points
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
inline StrBlobPtr &StrBlobPtr::incr() {
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;       // advance the current state
    return *this;
}

inline StrBlobPtr &StrBlobPtr::decr() {
    // if curr is zero, decrementing it will yield an invalid subscript
    --curr;       // move the current state back one element}
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

// begin and end members for StrBlob
inline StrBlobPtr StrBlob::begin() {
    return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end() {
    return StrBlobPtr(*this, data->size());
}

// accompany class
// ConstStrBlobPtr throws an exception on attempts to access a nonexistent element
class ConstStrBlobPtr {
    friend bool eq(const ConstStrBlobPtr &, const ConstStrBlobPtr &);

public:
    ConstStrBlobPtr() : curr(0) {}

    // const or not const?
    explicit ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    const std::string &deref() const;

    ConstStrBlobPtr &incr();       // prefix version
    ConstStrBlobPtr &decr();       // prefix version
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string &) const;

    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;      // current position within the array
};

inline const std::string &ConstStrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];  // (*p) is the vector to which this object points
}

inline ConstStrBlobPtr &ConstStrBlobPtr::incr() {
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

inline ConstStrBlobPtr &ConstStrBlobPtr::decr() {
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

inline std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();   // is the vector still around?
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");

    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}

inline ConstStrBlobPtr StrBlob::cbegin() const {
    return ConstStrBlobPtr(*this);
}

inline ConstStrBlobPtr StrBlob::cend() const {
    return ConstStrBlobPtr(*this, data->size());
}

inline ConstStrBlobPtr StrBlob::begin() const {
    return ConstStrBlobPtr(*this);
}

inline ConstStrBlobPtr StrBlob::end() const {
    return ConstStrBlobPtr(*this, data->size());
}

// named equality operators for StrBlobPtr
inline bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();

    // if the underlying vector is the same
    if (l == r)
        // then they're equal if they're both null or
        // if they point to the same element
        return (!r || lhs.curr == rhs.curr);
    else
        return false; // if they point to difference vectors, they're not equal
}

inline bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return !eq(lhs, rhs);
}

// named equality operators for ConstStrBlobPtr
inline bool eq(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();

    // if the underlying vector is the same
    if (l == r)
        // then they're equal if they're both null or
        // if they point to the same element
        return (!r || lhs.curr == rhs.curr);
    else
        return false; // if they point to difference vectors, they're not equal
}

inline bool neq(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return !eq(lhs, rhs);
}

#endif
