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
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <iostream>
#include <cstddef>

using std::string;
using std::size_t;
using std::sort;

using std::list; using std::vector;
using std::istream_iterator; using std::ostream_iterator;
using std::pair; using std::make_pair;
using std::cin; using std::cout; using std::endl;

pair<string, string> anon;       // holds two strings
pair<string, size_t> word_count; // holds a string and an size_t
pair<string, vector<int>> line;  // holds string and vector<int>

// list initialize the members in a pair
pair<string, string> author{"James", "Joyce"};

// ways to initialize a pair
typedef pair<string, string> Author;
Author proust("Marcel", "Proust");  // construct a pair
Author joyce{"James", "Joyce"};     // list initialize a pair
Author austen = make_pair("Jane", "Austen"); // use make_pair

void preliminaries(vector<string> &v) {
    // read from cin
    istream_iterator<string> input(cin), eof;
    copy(input, eof, back_inserter(v));
    sort(v.begin(), v.end(), [](const string &a, const string &b) {
        return a.size() < b.size();
    });
}

// three different ways to return a pair
// 1. list initialize the return value
pair<string, size_t> process(vector<string> &v) {
    if (!v.empty())
        return {v.back(), v.back().size()}; // list initialize
    else
        return {};
}

// 2. use make_pair to generate the return value
pair<string, size_t> process2(vector<string> &v) {
    // process v
    if (!v.empty())
        return make_pair(v.back(), v.back().size());
    else
        return make_pair("", static_cast<size_t>(0));
}

// 3. explicitly construct the return value
pair<string, size_t> process3(vector<string> &v) {
    // process v
    if (!v.empty())
        return pair<string, size_t>(v.back(), v.back().size());
    else
        return pair<string, size_t>();
}

int main() {
    vector<string> v;
    preliminaries(v);  // sort v into size order

    // all three output statements should be the same
    auto biggest = process(v);
    cout << biggest.first << " " << biggest.second << endl;

    auto biggest2 = process2(v);
    cout << biggest.first << " " << biggest.second << endl;

    auto biggest3 = process3(v);
    cout << biggest.first << " " << biggest.second << endl;
}
