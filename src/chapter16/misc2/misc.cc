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

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace exercise {
    // l-value or const r-value
    template<typename T>
    string debug_rep(const T &t) {
        ostringstream ret;
        ret << t;
        return ret.str();
    }

    // overloaded version
    template<typename T>
    string debug_rep(T *p) {
        ostringstream ret;
        ret << "pointer: " << p;
        if (p) {
            ret << " value: " << debug_rep(*p);
        } else {
            ret << " null pointer";
        }
        return ret.str();
    }

    string debug_rep(const string &s) {
        return '"' + s + '"';
    }

    // plain overloaded function for char *
    string debug_rep(char *p) {
        return debug_rep(string(p));
    }

    // plain overloaded function for const char *
    string debug_rep(const char *p) {
        return debug_rep(string(p));
    }

    // another method
    template<>
    string debug_rep(char *p) {
        return debug_rep(string(p));
    }

    template<>
    string debug_rep(const char *p) {
        return debug_rep(string(p));
    }


    template<typename T>
    void f(T) {
        cout << "f(T)" << endl;
    }

    template<typename T>
    void f(const T *) {
        cout << "f(const T *)" << endl;
    }

    template<typename T>
    void g(T) {
        cout << "g(T)" << endl;
    }

    template<typename T>
    void g(T *) {
        cout << "g(T*)" << endl;
    }

    // variadic template
    template<typename T, typename... Args>
    void foo(const T &t, const Args &... rest) {
        cout << sizeof...(Args) << " " << sizeof...(rest) << endl;
    };

    template<typename... Args>
    void gg(Args ... args) {
        cout << sizeof...(Args) << " " << sizeof...(args) << endl;
    };

    // seems no way to iteration, have to recursion
    template<typename T>
    ostream &print(ostream &os, const T &t) {
        os << t;
        return os;
    }

    template<typename T, typename... Args>
    ostream &print(ostream &os, const T &t, const Args &... rest) {
        os << t << ", ";
        return print(os, rest...);
    };

    template<typename... Args>
    ostream &errorMsg(ostream &os, const Args &... args) {
        return print(os, debug_rep(args)...);
    }

    template<typename T>
    struct remove_reference {
        typedef T type;
    };

    template<typename T>
    struct remove_reference<T &> {
        typedef T type;
    };
    template<typename T>
    struct remove_reference<T &&> {
        typedef T type;
    };

    // partial specialization
    template<typename A, typename B>
    struct Foo {
        Foo() { cout << "struct Foo" << endl; }

        A a;
        B b;
    };

    template<typename A>
    struct Foo<A, string> {
        Foo() { cout << "struct Foo<A, string>" << endl; }

        A a;
        string b;
    };

    // 16.63
    template<typename T>
    std::size_t count(const std::vector<T> &c, T v) {
        std::size_t cnt = 0;
        for (auto it = c.begin(); it != c.end(); ++it) {
            if (*it == v) {
                ++cnt;
            }
        }
        return cnt;
    }

    template<>
    std::size_t count(const std::vector<const char *> &c, const char *v) {
        std::size_t cnt = 0;
        for (auto it = c.begin(); it != c.end(); ++it) {
            if (strcmp(*it, v) == 0) {
                ++cnt;
            }
        }
        return cnt;
    }
}

int main() {
    cout << exercise::debug_rep("hello") << endl;
    cout << exercise::debug_rep(100) << endl;
    int a = 150;
    cout << exercise::debug_rep(a) << endl;
    cout << exercise::debug_rep(&a) << endl;

    // report a's address in stack
    int *b = &a;
    int *&c = b;
    cout << c << endl;

    // 16.49
    int i = 42, *p = &i;
    const int ci = 0, *p2 = &ci;

    exercise::g(42);
    exercise::g(p);
    exercise::g(ci);
    exercise::g(p2);
    exercise::f(42);
    exercise::f(p);
    exercise::f(ci);
    exercise::f(p2);

    // variadic template
    {
        int i = 0;
        double d = 3.14;
        string s = "how now brown cow";

        exercise::foo(i, s, 42, d);
        exercise::foo(s, 42, "hi");
        exercise::foo(d, s);
        exercise::foo("hi");

        exercise::gg(i, s, 42, d);
        exercise::gg(s, 42, "hi");
        exercise::gg(d, s);
        exercise::gg("hi");
        exercise::print(cout, i, d, s);
        cout << endl;
        exercise::errorMsg(cout, i, d, s);
        cout << endl;
    }

    // partial specialization
    {
        int i = 100;
        exercise::remove_reference<decltype(42)>::type a = 200;
        exercise::remove_reference<decltype(i)>::type b = 300;
        exercise::remove_reference<decltype(std::move(i))>::type c = 400;
        cout << i << " " << a << " " << b << " " << c << endl;
        exercise::Foo<int, string> f; // struct Foo<A, string>
    }

    // 16.63
    {
        vector<double> dvec = {1.1, 2.2, 3.3, 1.1};
        cout << exercise::count(dvec, 1.1) << endl;

        vector<int> ivec = {1, 2, 3, 1};
        cout << exercise::count(ivec, 1) << endl;

        vector<string> svec = {"1", "2", "3", "1"};
        cout << exercise::count(svec, string("1")) << endl;

        vector<const char *> cvec = {"1", "2", "3", "1"};
        cout << exercise::count(cvec, "1") << endl;

        cout << endl;
        cout << exercise::count(cvec, "2") << endl;
        cout << exercise::count(cvec, "3") << endl;
    }
    return 0;
}
