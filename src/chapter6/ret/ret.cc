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
#include <algorithm>

/* EXIT_FAILURE and EXIT_SUCCESS are preprocessor variables
 *       such variables are not in the std namespace,
 *       hence, no using declaration and no std:: when we use these names
*/

// void can't be omitted
int iabs(int p) {
    return std::abs(p);
}

int calls() {
    static int ctr = 0;
    return ctr++;
}

inline bool isShorter(const std::string &s1, const std::string &s2) {
    return s1.size() < s2.size();
}

int main() {
    std::cout << iabs(-1) << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << calls() << std::endl;
    }
    bool some_failure = true;
    if (some_failure)
        return EXIT_FAILURE;  // defined in cstdlib
    else
        return EXIT_SUCCESS;  // defined in cstdlib
}
