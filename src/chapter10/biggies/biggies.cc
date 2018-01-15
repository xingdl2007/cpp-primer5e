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
#include <vector>
#include <iostream>
#include <iomanip>
#include <functional>

using std::string;
using std::vector;
using std::cin; using std::cout; using std::endl;
using namespace std::placeholders;

// comparison function to be used to sort by word length
bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

void print(const vector<string> &words) {
    for_each(words.begin(), words.end(),
             [](const string &s) { cout << std::quoted(s) << " "; });
    cout << endl;
}

void elimDups(vector<string> &words) {
    sort(words.begin(), words.end());
    auto ret = std::unique(words.begin(), words.end());
    words.erase(ret, words.end());
}

bool target(const string &s, vector<string>::size_type sz) {
    return s.size() >= sz;
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto ret = std::stable_partition(words.begin(), words.end(),
                                     [sz](const string &s) {
                                         return s.size() < sz;
                                     });
    auto count = std::count_if(words.begin(), words.end(),
                               std::bind(target, _1, sz));
    cout << count << " words is >= " << sz << endl;
    for_each(ret, words.end(),
             [sz](const string &s) {
                 cout << std::quoted(s) << " ";
             });
    cout << endl;
}

void biggies2(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto ret = std::find_if(words.begin(), words.end(),
                            [=](const string &s) {
                                return s.size() >= sz;
                            });

    auto count = std::count_if(words.begin(), words.end(),
                               [=](const string &s) {
                                   return s.size() >= sz;
                               });
    cout << count << " words is >= " << sz << endl;
    for_each(ret, words.end(),
             [sz](const string &s) {
                 cout << std::quoted(s) << " ";
             });
    cout << endl;
}

int main() {
    vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    biggies(words, 3);
    biggies(words, 4);
    biggies2(words, 5);
    biggies2(words, 6);
    return 0;
}
