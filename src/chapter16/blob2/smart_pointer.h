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

#ifndef _SMART_POINTER_
#define _SMART_POINTER_

#include <functional>
#include <iostream>

namespace exercise {
    // deleter
    class deleter {
    public:
        template<typename T>
        void operator()(T *p) const {
            std::cout << "info from deleter" << std::endl;
            delete p;
        }
    };

    /****************************************************************
     *
             _                        _            _
         ___| |__   __ _ _ __ ___  __| |     _ __ | |_ _ __
        / __| '_ \ / _` | '__/ _ \/ _` |    | '_ \| __| '__|
        \__ \ | | | (_| | | |  __/ (_| |    | |_) | |_| |
        |___/_| |_|\__,_|_|  \___|\__,_|____| .__/ \__|_|
                                      |_____|_|

     *
     ****************************************************************/

    template<typename T>
    class shared_ptr;

    template<typename T>
    bool operator==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs);

    template<typename T>
    class shared_ptr {
        friend bool operator==<T>(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs);

    public:
        shared_ptr() : ptr(nullptr), cnt(nullptr) {}

        shared_ptr(T *p, std::function<void(T *)> d = deleter())
                : ptr(p), del(d), cnt(new std::size_t(1)) {}

        // copy-control
        shared_ptr(const shared_ptr &p)
                : ptr(p.ptr), del(p.del), cnt(p.cnt) {
            ++*cnt;
            debug();
        }

        // copy assignment
        shared_ptr &operator=(const shared_ptr &p);

        // member
        T operator*() const { return *ptr; }

        // arrow
        T *operator->() const { return ptr; }

        operator bool() const { return ptr != nullptr; }

        // reset
        void reset(T *p);

        void reset(T *p, std::function<void(T *)> deleter);

        ~shared_ptr();

        void debug() const {
            if (cnt) {
                std::cout << "ref cnt: " << *cnt << std::endl;
            } else {
                throw std::runtime_error("should not happen");
            }
        }

    private:
        T *ptr;
        std::function<void(T *)> del;
        std::size_t *cnt;
    };

    template<typename T>
    shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr &p) {
        ++*p.cnt;
        if (--*cnt == 0) {
            del ? del(ptr) : delete ptr;
            delete cnt;
        }
        ptr = p.ptr;
        del = p.del;
        cnt = p.cnt;
        debug();
        return *this;
    }

    template<typename T>
    void shared_ptr<T>::reset(T *p) {
        if (cnt && --*cnt == 0) {
            del ? del(ptr) : delete ptr;
            delete cnt;
        }
        ptr = p;
        cnt = new std::size_t(1);
    }

    template<typename T>
    void shared_ptr<T>::reset(T *p, std::function<void(T *)> deleter) {
        reset(p);
        del = deleter;
    }

    template<typename T>
    shared_ptr<T>::~shared_ptr() {
        if (--*cnt == 0) {
            del ? del(ptr) : delete ptr;
            delete cnt;
        }
    }

    // == and != operator
    template<typename T>
    bool operator==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
        return lhs.ptr == rhs.ptr;
    }

    template<typename T>
    bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
        return !(lhs == rhs);
    }

    // helper function, simulate std::make_shared()
    template<typename T, typename ... Args>
    shared_ptr<T> make_shared(Args &&... args) {
        shared_ptr<T> s(new T(std::forward<Args>(args)...));
        return s;
    }

    /****************************************************************
     *
                     _                             _
         _   _ _ __ (_) __ _ _   _  ___      _ __ | |_ _ __
        | | | | '_ \| |/ _` | | | |/ _ \    | '_ \| __| '__|
        | |_| | | | | | (_| | |_| |  __/    | |_) | |_| |
         \__,_|_| |_|_|\__, |\__,_|\___|____| .__/ \__|_|
                          |_|         |_____|_|

     *
     ****************************************************************/
    template<typename T, typename D = deleter>
    class unique_ptr {
    public:
        unique_ptr(T *p = nullptr, D d = deleter()) : ptr(p), del(d) {}

        ~unique_ptr() { del(ptr); }

        // move ctor
        unique_ptr(unique_ptr &&u) : ptr(u.ptr), del(u.del) { u.ptr = nullptr; }

        unique_ptr(unique_ptr &u) = delete;

        // move assignment
        unique_ptr &operator=(unique_ptr &&u);

        unique_ptr &operator=(unique_ptr &) = delete;

        T operator*() const { return *ptr; }

        T *operator->() const { return ptr; }

        void reset(T *p) {
            del(ptr);
            ptr = p;
        }

        void reset(T *p, D d) {
            reset(p);
            del = d;
        }

    private:
        T *ptr;
        D del;
    };

    template<typename T, typename D>
    unique_ptr<T, D> &unique_ptr<T, D>::operator=(unique_ptr &&u) {
        if (this != &u) {
            del(ptr);
            ptr = u.ptr;
            del = u.del;

            u.ptr = nullptr;
        }
        return *this;
    }
}

#endif
