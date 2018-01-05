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
#include <string>

// skip empty line
void readLine() {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty()) {
            std::cout << line << std::endl;
        }
    }
}

// default is by word
void readWord() {
    std::string word;
    while (std::cin >> word) {
        std::cout << word << std::endl;
    }
}

void compare1() {
    std::string item1, item2;
    std::cin >> item1 >> item2;
    if (std::cin) {
        if (item1 < item2) {
            std::cout << item2 << std::endl;
        } else {
            std::cout << item1 << std::endl;
        }
    }
}

void compare2() {
    std::string item1, item2;
    std::cin >> item1 >> item2;
    if (std::cin) {
        if (item1.size() < item2.size()) {
            std::cout << item2 << std::endl;
        } else {
            std::cout << item1 << std::endl;
        }
    }
}

void concatenate() {
    std::string word, line;
    while (std::cin >> word) {
        line += word;
    }
    std::cout << line << std::endl;
}

void concatenate2() {
    std::string word, line;
    while (std::cin >> word) {
        line += word + " ";
    }
    std::cout << line << std::endl;
}

int main() {
    int a = 1, b = 2, c = 3;
    a = b = c;
    std::cout << a << std::endl;

    // homework: 3.2
    readLine();
    //readWord();

    // homework: 3.4
    //compare1();
    //compare2();

    // homework: 3.5
    //concatenate2();
    return 0;
}