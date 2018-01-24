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
#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <cassert>
#include <memory>
#include <functional>
#include <type_traits>
#include <limits>

using namespace std;

template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
    return strcmp(p1, p2);
};

template<typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) { return -1; }
    if (v2 < v1) { return 1; }
    return 0;
}

template<>
int compare(const char *const &v1, const char *const &v2) {
    return strcmp(v1, v2);
}

// 16.4
namespace exercise {
    // self-defined version of find
    template<typename T, typename V>
    T find(const T &b, const T &e, V v) {
        T ret = b;
        while (ret != e) {
            if (*ret == v) {
                return ret;
            } else {
                ++ret;
            }
        }
        return e;
    };

    // 16.5
    template<typename T, unsigned N>
    void print(T (&arr)[N]) {
        for (auto e:arr) {
            cout << e << endl;
        }
    }

    // 16.6
    template<typename T, unsigned N>
    T *begin(T (&arr)[N]) {
        return arr;
    };

    template<typename T, unsigned N>
    T *end(T (&arr)[N]) {
        return arr + N;
    };

    // 16.7
    template<typename T, unsigned N>
    constexpr unsigned arraySize(T (&array)[N]) {
        return N;
    };

    // 16.11
    template<typename elemType>
    class ListItem;

    template<typename elemType>
    class List {
    public:
        List<elemType>();

        List<elemType>(const List<elemType> &);

        List<elemType> &operator=(const List<elemType> &);

        ~List();

        void insert(ListItem<elemType> *ptr, elemType value);

    private:
        ListItem<elemType> *front, *end;
    };

    // 16.14
    template<unsigned H, unsigned W>
    class Screen;

    template<unsigned H, unsigned W>
    ostream &operator<<(ostream &os, Screen<H, W> screen);

    template<unsigned H, unsigned W>
    istream &operator>>(istream &is, Screen<H, W> screen);

    template<unsigned H, unsigned W>
    class Screen {
        friend ostream &operator<<
                <H, W>(ostream &, Screen<H, W>);

        friend istream &operator>>
                <H, W>(istream &, Screen<H, W>);

    public:
        Screen(unsigned h = H, unsigned w = W) : height(h), width(w) {}

    private:
        unsigned height;
        unsigned width;
    };

    template<unsigned H, unsigned W>
    ostream &operator<<(ostream &os, Screen<H, W> screen) {
        os << "height: " << screen.height << " weight: " << screen.width;
        return os;
    };

    template<unsigned H, unsigned W>
    istream &operator>>(istream &is, Screen<H, W> screen) {
        is >> screen.height >> screen.width;
        return is;
    };

    // 16.27
    template<typename T>
    class Stack {
    public:
        Stack() { cout << "Stack()" << endl; }

        void operator()() const { cout << "Stack operator()" << endl; }
    };

    void f1(Stack<char> s) { s(); }

    class Exercise {
        //Stack<double> &rsd;
        Stack<int> si;
    };


    // move defination
    template<typename T>
    typename remove_reference<T>::type &&move(T &&t) {
        return static_cast<typename remove_reference<T>::type &&> (t);
    }

    //flip
    void f(int v1, int v2) {
        cout << "v1: " << v1 << " v2: " << ++v2 << endl;
    }

    template<typename F, typename T1, typename T2>
    void flip1(F f, T1 t1, T2 t2) {
        f(t2, t1);
    };

    void g(int v1, int &v2) {
        cout << "v1: " << v1 << " v2: " << ++v2 << endl;
    }

    template<typename F, typename T1, typename T2>
    void flip2(F f, T1 &&t1, T2 &&t2) {
        f(t2, t1);
    };

    void h(int &&v1, int &v2) {
        cout << "v1: " << v1 << " v2: " << v2 << endl;
    }

    template<typename F, typename T1, typename T2>
    void flip3(F f, T1 &&t1, T2 &&t2) {
        f(std::forward<T2>(t2), std::forward<T1>(t1));
    };
}

// 16.18
template<typename T, typename U, typename V>
void f1(T, U, V);

template<typename T>
T f2(int &);

template<typename T>
inline T foo(T, unsigned int *);

template<typename T>
void f4(T, T);

typedef char Ctype;

template<typename Ctype>
Ctype f5(Ctype a);

/*
 _  __    _  ___
/ |/ /_  / |( _ )
| | '_ \ | |/ _ \
| | (_) || | (_) |
|_|\___(_)_|\___/
*/

// 16.19
template<typename T>
void print(const T &t) {
    typename T::size_type s = 0, size = t.size();
    while (s != size) {
        cout << t[s] << endl;
        ++s;
    }
}

// 16.20
template<typename T>
void print2(T &t) {
    auto it = t.begin();
    while (it != t.end()) {
        cout << *it++ << endl;
    }
}


class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}

    template<typename T>
    void operator()(T *p) const {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};

// for 16.27
template<typename>
class Test;

// 16.36
template<typename T>
void ff1(T, T) {}

template<typename T1, typename T2>
void ff2(T1, T2) {}

int i = 0, j = 42, *p1 = &i, *p2 = &j;
const int *cp1 = &i, *cp2 = &j;

void test() {
    ff1(p1, p2);
    ff2(p1, p2);
    ff1(cp1, cp2);
    ff2(cp1, cp2);
    //ff1(p1, cp1); // error: no matching function for call to 'ff1(int*&, const int*&)'
    ff2(p1, cp1);
}

template<typename It>
auto first(It beg, It end) -> typename std::remove_reference<decltype(*beg)>::type {
    if (beg == end) {
        throw std::runtime_error("beg == end");
    }
    return *beg;
}

template<typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0) {
    if (beg == end) {
        throw std::runtime_error("beg == end");
    }
    return *beg;
}

// limited version
template<typename T>
auto sum(T lhs, T rhs) -> typename make_unsigned<decltype(lhs + rhs)>::type {
    return lhs + rhs;
}

// 16.45
template<typename T>
void g(T &&val) { vector<T> v; }

int main() {
    cout << compare(1, 2) << endl;                              // -1

    // ambiguous: two candidate, with T = char [6] and M = N = 6
    //cout << compare("lo", "world") << endl;
    cout << compare<const char *>("hi", "mom") << endl;                       // 1

    const char *p1 = "hi";
    const char *p2 = "mom";
    cout << compare(p1, p2) << endl;
    cout << compare(string("hello"), string("world")) << endl;  // -1

    //Sales_data s1, s2;
    //cout << compare(s1, s2) << endl;

    // 16.4
    vector<int> ivec = {1, 2, 3, 4};
    auto it = exercise::find(ivec.begin(), ivec.end(), 3);
    cout << it - ivec.begin() << endl;

    list<string> sls = {"ni", "hao", "hi", "mom"};
    auto it2 = exercise::find(sls.begin(), sls.end(), "hao");
    if (it2 != sls.end()) {
        cout << *it2 << endl;
    }

    // 16.5
    int array1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int array2[] = {11, 12, 13};
    string array3[] = {"ni", "hao"};
    exercise::print(array1);
    exercise::print(array2);
    exercise::print(array3);

    // 16.6
    assert(std::begin(array1) == exercise::begin(array1));
    assert(std::end(array1) == exercise::end(array1));

    assert(std::begin(array3) == exercise::begin(array3));
    assert(std::end(array3) == exercise::end(array3));

    // 16.7
    assert(exercise::arraySize(array1) == 10);
    assert(exercise::arraySize(array2) == 3);
    assert(exercise::arraySize(array3) == 2);

    // 16.14
    exercise::Screen<100, 20> screen;
    cout << screen << endl;

    exercise::Screen<10, 100> screen2;
    cout << screen2 << endl;

    // 16.19
    print(ivec);
    print2(sls);

    // interesting
    double *p = new double;
    DebugDelete d;
    d(p);

    int *ip = new int;
    DebugDelete()(ip);

    unique_ptr<int, DebugDelete> up(new int, DebugDelete());
    unique_ptr<string, DebugDelete> sup(new string, DebugDelete());

    // 16.27
    exercise::Stack<char> *sc;
    exercise::f1(*sc);
    int iObj = sizeof(exercise::Stack<string>);
    cout << "iObj: " << iObj << endl;

    // test
    test();

    // 16.37
    int i_int = 3;
    double d_double = 2.9;
    cout << std::max<double>(i_int, d_double) << endl;

    cout << "\nfirst() test:" << endl;
    cout << first(ivec.begin(), ivec.end()) << endl;
    cout << fcn3(ivec.begin(), ivec.end()) << endl;

    // 16.41
    cout << "\nnew sum:\n";
    // right result
    cout << std::numeric_limits<int>::max() << endl;
    cout << sum(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()) << endl;

    // wrong result
    cout << std::numeric_limits<int>::min() << endl;
    cout << sum(std::numeric_limits<int>::min(), std::numeric_limits<int>::min()) << endl;

    // wrong result
    cout << std::numeric_limits<unsigned int>::max() << endl;
    cout << sum(std::numeric_limits<unsigned int>::max(), std::numeric_limits<unsigned int>::max()) << endl;

    // 16.45
    g(42);

    // r-value reference
    int &&ref = static_cast<int &&>(i_int);
    cout << ref << endl;

    // 16.47
    exercise::flip1(exercise::f, 1, 2);
    int j = 2;
    exercise::flip2(exercise::g, j, 1);
    cout << j << endl;

    exercise::flip3(exercise::h, j, 1);
    return 0;
}
