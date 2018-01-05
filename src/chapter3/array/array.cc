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
#include <cstddef>
#include <iterator>

int txt_size() {
    return 0;
}

// impressive!
void homework327() {
    constexpr unsigned buf_size = 1024;
    int ia1[buf_size];
    int ia2[4 * 7 - 14];
    int ia3[txt_size()];

    // error: initializer-string is too long
    // char st[11] = "fundamental";
}

std::string sa[10];
int ia[10];

void homework328() {
    std::string sa2[10];
    int ia2[10];
}

void homework331() {
    int array[10];
    for (std::size_t i = 0; i < 10; ++i) {
        array[i] = i;
    }
    for (auto i:array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int copy[10];
    for (std::size_t i = 0; i < 10; ++i) {
        copy[i] = array[i];
    }
}

// big difference!!
void homework333() {
    int grade[10] = {23, 43, 67, 89, 99, 100, 62, 92, 99, 44};
    //int level[10];
    int level[10] = {};
    for (auto score:grade) {
        ++level[score / 10];
    }

    for (auto i:level) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void homework335() {
    int array[] = {1, 2, 3, 4};
    for (auto it = std::begin(array); it != std::end(array); ++it) {
        *it = 0;
    }
}

bool homework336() {
    int array1[] = {1, 2, 3, 4};
    int array2[] = {4, 3, 2, 1};
    std::size_t len1 = sizeof(array1) / sizeof(array1[0]);
    std::size_t len2 = sizeof(array2) / sizeof(array1[0]);
    if (len1 != len2) {
        return false;
    }
    for (std::size_t i = 0; i < len1; ++i) {
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

bool homework336_2() {
    std::vector<int> vec1{1, 2, 3, 4};
    std::vector<int> vec2{4, 3, 2, 1};
    return vec1 == vec2;
}

void homework337() {
    const char ca[] = {'h', 'e', 'l', 'l', 'o'};
    const char *cp = ca;
    while (*cp) {
        std::cout << *cp << std::endl;
        ++cp;
    }
}

void homework341() {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> ivec(std::begin(array), std::end(array));
    for (auto i:ivec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void homework342() {
    std::vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // really good, array length can be non-constexpr
    int array[ivec.size()];

    for (decltype(ivec.size()) i = 0; i < ivec.size(); i++) {
        array[i] = ivec[i];
    }
    for (auto i:array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void homework343() {
    const int row = 3, columen = 4;
    int multi[row][columen] = {{1, 2,  3,  4},
                               {5, 6,  7,  8},
                               {9, 10, 11, 12}
    };

    std::cout << "method 1: range for" << std::endl;
    for (int(&p)[columen] :multi) {
        for (int i:p) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nmethod 2: general for with index" << std::endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < columen; j++) {
            std::cout << multi[i][j] << " ";
        }
        std::cout << std::endl;
    }


    std::cout << "\nmethod 3: general for with pointer" << std::endl;
    for (int (*p)[columen] = multi; p != multi + 3; ++p) {
        for (int *q = *p; q != *p + 4; ++q) {
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }

    // define some useful type
    using ref = int (&)[columen];     //typedef int (&ref)[4];
    using pointer = int (*)[columen]; //typedef int(*pointer)[4];

    std::cout << "method 4: range for with type alias" << std::endl;
    for (ref p :multi) {
        for (int i:p) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nmethod 5: general for with pointer with type alias" << std::endl;
    for (pointer p = multi; p != multi + 3; ++p) {
        for (int *q = *p; q != *p + 4; ++q) {
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nmethod 6: auto with begin() and end()" << std::endl;
    for (auto p = std::begin(multi); p != std::end(multi); ++p) {
        for (auto q = std::begin(*p); q != std::end(*p); ++q) {
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }
}

void multiTest() {
    int multi[3][4] = {{1, 2,  3,  4},
                       {5, 6,  7,  8},
                       {9, 10, 11, 12}};
    for (auto &row:multi) {
        for (auto item:row) {
            std::cout << item << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    // impressive !
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto it = std::begin(ia); it != std::end(ia); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    int *p1 = ia, *p2 = &ia[10];
    p1 += p2 - p1;
    std::cout << *p1 << std::endl;

    // range for
    //multiTest();

    //homework327();
    //homework328();
    //homework331();
    //homework333();

    //std::cout << homework336() << std::endl;
    //std::cout << homework336_2() << std::endl;
    //homework337();
    //homework341();
    //homework342();
    homework343();
    return 0;
}