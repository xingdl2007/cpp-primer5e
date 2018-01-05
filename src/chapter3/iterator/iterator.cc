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

void homework322() {
    std::vector<std::string> text = {"hello world", "what's wrong?", "", "hi!"};
    for (auto it = text.begin(); it != text.end() && !it->empty(); ++it) {
        if (it == text.begin()) {
            for (auto &c:*it) {
                c = std::toupper(c);
            }
        }
        std::cout << *it << std::endl;
    }
}

void homework323() {
    std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto it = ivec.begin(); it != ivec.end(); ++it) {
        *it += *it;
    }

    for (auto i:ivec) {
        std::cout << i << std::endl;
    }
}

void homework324() {
    int num;
    std::vector<int> vec;
    while (std::cin >> num) {
        vec.push_back(num);
    }

    for (auto it = vec.cbegin(); it != vec.cend() - 1; ++it) {
        std::cout << *it + *(it + 1) << std::endl;
    }

    std::cout << std::endl;
    for (auto it = vec.cbegin(); it != vec.cbegin() + vec.size() / 2; ++it) {
        std::cout << *it + *(vec.cbegin() + (vec.cend() - it - 1)) << std::endl;
    }
    if ((vec.cend() - vec.cbegin()) % 2 != 0) {
        std::cout << (*(vec.cbegin() + vec.size() / 2)) * 2 << std::endl;
    }
}

void homework325() {
    std::vector<int> grade{23, 43, 67, 89, 99, 100, 62, 92, 99, 44};
    std::vector<int> level(11, 0);

    for (auto it = grade.cbegin(); it != grade.cend(); ++it) {
        ++level[*it / 10];
    }

    for (const auto &l:level) {
        std::cout << l << " ";
    }
    std::cout << std::endl;
}

int main() {
    //homework322();
    //homework323();
    homework324();
    //homework325();
    return 0;
}