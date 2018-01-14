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

#include <algorithm>
#include <string>
#include <list>
#include <forward_list>
#include <vector>
#include <iostream>

using std::find;
using std::vector;
using std::forward_list;
using std::list;
using std::string;
using std::cout; using std::endl;

void insert_after(forward_list<string> &flist, const string &s1, const string &s2) {
    auto pre = flist.before_begin(), curr = flist.begin();
    while (curr != flist.end()) {
        if (*curr == s1) {
            flist.insert_after(curr, s2);
            return;
        } else {
            pre = curr;
            ++curr;
        }
    }
    flist.insert_after(pre, s2);
}

int main() {
    // lst has ten elements 0 ... 9 in value
    list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // print the initial values in lst
    cout << "initial list: ";
    for (auto it : lst)
        cout << it << " ";
    cout << endl;

    // erase the odd elements in lst
    auto it = lst.begin();
    while (it != lst.end()) {
        if (*it % 2) {            // if the element is odd
            it = lst.erase(it);  // erase this element
        } else {
            ++it;
        }
    }
    // print the current contents of lst
    cout << "after erasing odd elements from lst: ";
    for (auto it : lst) {
        cout << it << " ";
    }
    cout << endl;

    // repeat the same actions but on a forward_list
    forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // print the initial values in flst
    cout << "initial list: ";
    for (auto it : flst) {
        cout << it << " ";
    }
    cout << endl;

    // erase the odd elements in flst
    auto prev = flst.before_begin(); // element "off the start" of flst
    auto curr = flst.begin();        // denotes the first element in flst
    while (curr != flst.end()) {     // while there are still elements
        if (*curr % 2) {                   // if the element is odd
            curr = flst.erase_after(prev); // erase it and move curr
        } else {
            prev = curr; // move the iterators to denote the next
            ++curr;      // element and one before the next element
        }
    }

    // print the current contents of lst
    cout << "after erasing elements from flst: ";
    for (auto it : flst) {
        cout << it << " ";
    }
    cout << endl;

    // 9.28
    forward_list<string> flist = {"1", "2", "3", "5", "6", "7"};
    insert_after(flist, "3", "4");
    insert_after(flist, "10", "8");
    for (auto s:flist) {
        cout << s << "\n";
    }
    return 0;
}
