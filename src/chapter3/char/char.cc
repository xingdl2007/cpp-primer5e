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
#include <memory>
#include <cxxabi.h>
#include <cctype>

template<class T>
std::string type_name() {
    using TR = typename std::remove_reference<T>::type;
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

void homework36() {
    // homework 3.6:
    std::string some("hello world.");
    for (char &c:some) {
        //mtd::cout << type_name<decltype(c)>() << std::endl; // output: char &
        c = 'X';
    }
    std::cout << some << std::endl;
}

// homework: 3.9
void homework39() {
    std::string s;
    std::cout << s[0] << std::endl;

}

// homework: 3.10
void homework310() {
    std::string original, output;
    std::cin >> original;
    if (std::cin) {
        for (const auto &c:original) {
            if (!std::ispunct(c)) {
                output += c;
            }
        }
    }
    std::cout << output << std::endl;
}

void homework311() {
    const std::string s = "Keep out!";
    for (auto &c:s) {
        /* ... */
        std::cout << type_name<decltype(c)>() << std::endl;
    }
}

int main() {
    //homework36();
    //homework39();
    //homework310();
    homework311();
    return 0;
}