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

#include <map>

using std::map; using std::multimap;

#include <set>

using std::set; using std::multiset;

#include <vector>

using std::vector; using std::string;

#include <iostream>

using std::cin; using std::cout; using std::endl;

#include <algorithm>
#include <list>
#include <iterator>

using std::list;

#include "Sales_data.h"

int main() {
    vector<int> ivec{1, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8};
    vector<int> ilist{1, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8};
    set<int> iset(ivec.begin(), ivec.end());
    multiset<int> miset(ivec.begin(), ivec.end());

    cout << ivec.size() << endl;
    cout << iset.size() << endl;
    cout << miset.size() << endl;

    map<string, string> authors = {{"xing",  "dong"},
                                   {"hello", "world"}};
    multimap<string, string> authors2 = {{"xing",  "dong"},
                                         {"hello", "world"},
                                         {"hello", "kkkkm"}};
    cout << authors.size() << endl;
    cout << authors2.size() << endl;

    // for 11.9
    std::map<string, std::list<int>> words;

    // for 11.10
    map<vector<int>::iterator, int> vec_it_map;
    for (auto it = ivec.begin(); it != ivec.end(); ++it) {
        ++vec_it_map[it];
    }
    for (auto &p:vec_it_map) {
        cout << *p.first << " -> " << p.second << endl;
    }
    map<list<int>::iterator, int> list_it_map;

    // definition
    set<Sales_data, decltype(compareIsbn) *> bookstore(&compareIsbn);
    map<Sales_data, int, decltype(compareIsbn) *> bookstore1(compareIsbn);
    multiset<Sales_data, decltype(compareIsbn) *> bookstore2(compareIsbn);
    multimap<Sales_data, int, decltype(compareIsbn) *> bookstore3(&compareIsbn);

    // for 11.11
    multiset<Sales_data, bool (*)(const Sales_data &, const Sales_data &)> bookstore4(compareIsbn);


    // for 11.17
    multiset<string> msvec{"1", "2", "3"};
    vector<string> svec = {"hello", "world", "bookstore"};

    //std::copy(svec.begin(), svec.end(), std::inserter(msvec, msvec.end()));
    //std::copy(svec.begin(), svec.end(), std::back_inserter(msvec));
    //std::copy(msvec.begin(), msvec.end(), std::inserter(svec, svec.end()));
    std::copy(msvec.begin(), msvec.end(), std::back_inserter(svec));

    for (const auto &s:msvec) {
        cout << s << endl;
    }
    cout << endl;
    for (const auto &s:svec) {
        cout << s << endl;
    }

    return 0;
}
