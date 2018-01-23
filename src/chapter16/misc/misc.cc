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
}

int main() {
    cout << compare(1, 2) << endl;                              // -1

    // ambiguous: two candidate, with T = char [6] and M = N = 6
    // cout << compare("hello", "world") << endl;
    cout << compare("hi", "mom") << endl;                       // 1

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
    return 0;
}
