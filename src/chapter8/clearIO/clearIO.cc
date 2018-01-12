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

using std::cin; using std::cout; using std::endl;

#include <sstream>

using std::istringstream;

#include <string>

using std::string;

#include <assert.h>

void read() {
    // turns on both fail and bad bits
    cin.setstate(cin.badbit | cin.eofbit | cin.failbit);
}

void off() {
    // turns off failbit and badbit but all other bits unchanged
    //cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);
    cin.clear(~(cin.failbit | cin.badbit));
}

std::istream &exercise81(std::istream &is) {
    int data;
    while (is >> data) {
        cout << data;
    }
    is.clear();
    assert(is.good());
    return is;
}

int main() {
    cout << "before read" << endl;
    if (cin.good()) cout << "\tcin's good" << endl;
    if (cin.bad()) cout << "\tcin's bad" << endl;
    if (cin.fail()) cout << "\tcin's fail" << endl;
    if (cin.eof()) cout << "\tcin's eof" << endl;

    read();
    cout << "after read" << endl;
    if (cin.good()) cout << "\tcin's good" << endl;
    if (cin.bad()) cout << "\tcin's bad" << endl;
    if (cin.fail()) cout << "\tcin's fail" << endl;
    if (cin.eof()) cout << "\tcin's eof" << endl;

    off();
    cout << "after off" << endl;
    if (cin.good()) cout << "\tcin's good" << endl;
    if (cin.bad()) cout << "\tcin's bad" << endl;
    if (cin.fail()) cout << "\tcin's fail" << endl;
    if (cin.eof()) cout << "\tcin's eof" << endl;

    // reset
    cin.clear();
    exercise81(cin);
    return 0;
}
