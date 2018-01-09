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
#include <vector>

#include "person.h"

class NoDefault {
public:
    explicit NoDefault(int v) { val = v; }

private:
    int val;
};

class C {
public:
    C() : no(100) {}

private:
    NoDefault no;
};

int main() {
    // 1
    std::cout << "Person person1;" << std::endl;
    Person person1;

    // 2
    std::cout << "Person person2(std::cin);" << std::endl;
    Person person2(std::cin);

    // 3
    C c;

    // 4: it's right, static_case from int to std::vector<int>
    //std::vector<int> ivec(static_cast<std::vector<int>>(5));
    std::vector<NoDefault> ivec(5, NoDefault(100));
}