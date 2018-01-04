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

#include <iostream>
#include <cxxabi.h>
#include <memory>

// ref: https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
template<class T>
std::string type_name() {
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void (*)(void *)> own(
            abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
            std::free
    );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

void homework() {
    const int i = 42;
    auto j = i;
    const auto &k = i;
    auto *p = &i;
    const auto j2 = i, &k2 = i;

    std::cout << "j: " << type_name<decltype(j)>() << std::endl;
    std::cout << "k: " << type_name<decltype(k)>() << std::endl;
    std::cout << "p: " << type_name<decltype(p)>() << std::endl;
    std::cout << "j2 " << type_name<decltype(j2)>() << std::endl;
    std::cout << "k2: " << type_name<decltype(k2)>() << std::endl;
}

int main() {
    int i = 0, &r = i;
    auto a = r;   // int

    const int ci = i, &cr = ci;
    auto b = ci;  // int
    auto c = cr;  // int
    auto d = &i;  // int *
    auto e = &ci; // const int *

    const auto f = ci; // const int
    auto &g = ci;      // const int &

    a = 42;
    b = 42;
    c = 42;

    std::cout << "a: " << type_name<decltype(a)>() << std::endl;
    std::cout << "b: " << type_name<decltype(b)>() << std::endl;
    std::cout << "c: " << type_name<decltype(c)>() << std::endl;
    std::cout << "d: " << type_name<decltype(d)>() << std::endl;
    std::cout << "e: " << type_name<decltype(e)>() << std::endl;
    std::cout << "f: " << type_name<decltype(f)>() << std::endl;
    std::cout << "g: " << type_name<decltype(g)>() << std::endl;

    // d = 42;
    // e = 42;
    // g = 42;
    homework();
    return 0;
}
