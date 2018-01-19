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

#include <iostream>
#include <algorithm>
#include <vector>

#include "string.h"

void print(const String &s) {
    std::for_each(s.begin(), s.end(),
                  [](const char c) { std::cout << c; });
    std::cout << '\n';
}

int main() {
    std::string str = "hello";
    std::cout << str.size() << " " << str.max_size() << std::endl;

    String s1 = "hello", s2 = "world", s3 = s1;

    s1 = s2;
    print(s1);
    print(s2);
    print(s3);

    s1 += s2;
    s1 += s3;
    print(s1);
    std::cout << s1.size() << " " << s1.capacity() << std::endl;

    std::cout << std::endl;
    std::vector<String> vec = {"1", "2", "3", "4"};
    std::cout << std::endl;
    vec.push_back("4");
    vec.push_back("6");
    vec.push_back("7");
    vec.push_back("8");
    std::for_each(vec.begin(), vec.end(),
                  [](const String &s) { print(s); });
    return 0;
}