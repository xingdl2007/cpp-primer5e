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
#include <numeric>
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <iomanip>

using std::count;
using std::vector; using std::list;
using std::string;
using std::cout; using std::endl;
using std::accumulate;
using std::begin; using std::end;
using std::equal; using std::copy;


int main() {
    // 10.1
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << count(ivec.begin(), ivec.end(), 0) << endl;
    cout << count(ivec.begin(), ivec.end(), 1) << endl;
    cout << count(ivec.begin(), ivec.end(), 2) << endl;
    cout << count(ivec.begin(), ivec.end(), 3) << endl;
    cout << count(ivec.begin(), ivec.end(), 4) << endl;
    cout << count(ivec.begin(), ivec.end(), 5) << endl;
    cout << count(ivec.begin(), ivec.end(), 6) << endl;
    cout << count(ivec.begin(), ivec.end(), 7) << endl;
    cout << count(ivec.begin(), ivec.end(), 8) << endl;
    cout << count(ivec.begin(), ivec.end(), 9) << endl;
    cout << endl;

    // 10.2
    list<string> ilist{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    cout << count(ilist.begin(), ilist.end(), "0") << endl;
    cout << count(ilist.begin(), ilist.end(), "1") << endl;
    cout << count(ilist.begin(), ilist.end(), "2") << endl;
    cout << count(ilist.begin(), ilist.end(), "3") << endl;
    cout << count(ilist.begin(), ilist.end(), "4") << endl;
    cout << count(ilist.begin(), ilist.end(), "5") << endl;
    cout << count(ilist.begin(), ilist.end(), "6") << endl;
    cout << count(ilist.begin(), ilist.end(), "7") << endl;
    cout << count(ilist.begin(), ilist.end(), "8") << endl;
    cout << count(ilist.begin(), ilist.end(), "9") << endl;

    // 10.4
    vector<double> dvec{0.0, 1.1, 2.2, 3.3};
    cout << accumulate(dvec.begin(), dvec.end(), .0) << endl;

    // 10.5
    char data1[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char data2[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char data3[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char data4[] = {'h', 'e', 'l', 'l', 'o', '\0'};

    vector<const char *> roster1{data1, data2};
    vector<const char *> roster2{data3, data4};
    vector<string> roster3{"hello", "hello"};

    cout << ((equal(roster1.cbegin(), roster1.cend(), roster2.cbegin())) ? "true" : "false") << endl;
    cout << ((equal(roster3.cbegin(), roster3.cend(), roster1.cbegin())) ? "true" : "false") << endl;


    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int a2[sizeof(a1) / sizeof(a1[0])];
    copy(begin(a1), end(a1), begin(a2));

    std::replace(begin(a1), end(a1), 9, 99);
    std::replace_copy(begin(a1), end(a1), begin(a2), 9, 99);


    vector<int> vec;
    vec.resize(2); // reserve is covered in § 9.4 (p. 356)
    fill_n(vec.begin(), 2, 100);
    std::for_each(vec.begin(), vec.end(), [](const int i) { cout << i << endl; });
    cout << vec.size() << " " << vec.capacity() << endl;

    // 10.13
    vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    auto ret = std::partition(words.begin(), words.end(),
                              [](const string &s) {
                                  return s.size() < 5;
                              });
    // print out
    std::for_each(words.begin(), ret,
                  [](const string &s) {
                      cout << std::quoted(s) << endl;
                  });

    // 10.14
    auto func = [](int a, int b) { return a + b; };
    cout << func(1, 2) << endl;

    // 10.15
    int cap = 100;
    auto func2 = [cap](int i) { return i + cap; };
    cout << func2(8) << endl;

    // 10.20
    int i = 3;
    auto fun3 = [=]()mutable -> bool {
        if (i == 0) {
            return true;
        }
        --i;
        return false;
    };
    cout << (fun3() ? "true" : "false") << endl;
    cout << (fun3() ? "true" : "false") << endl;
    cout << (fun3() ? "true" : "false") << endl;
    cout << (fun3() ? "true" : "false") << endl;
    cout << i << endl;

    // 10.27 and 10.28
    vector<int> ivec2{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
    list<int> ilist2;
    vector<int> ivec3;
    list<int> ilist3;
    std::unique_copy(ivec2.begin(), ivec2.end(), std::inserter(ilist2, ilist2.begin()));
    std::unique_copy(ivec2.begin(), ivec2.end(), std::front_inserter(ilist3));
    std::unique_copy(ivec2.begin(), ivec2.end(), std::back_inserter(ivec3));

    std::for_each(ilist2.begin(), ilist2.end(),
                  [](int i) {
                      cout << i << endl;
                  });
    cout << endl;
    std::for_each(ilist3.begin(), ilist3.end(),
                  [](int i) {
                      cout << i << endl;
                  });
    cout << endl;
    std::for_each(ivec3.begin(), ivec3.end(),
                  [](int i) {
                      cout << i << endl;
                  });

    // 10.29
//    std::istream_iterator<string> in(std::cin), eof;
//    vector<string> words2(in, eof);
//    std::for_each(words2.begin(), words2.end(), [](const string &s) { cout << s << " "; });
//    cout << endl;

    // 10.30
//    std::istream_iterator<int> in2(std::cin), eof2;
//    vector<int> nums;
//    //copy(in2, eof2, std::back_inserter(nums));
//    unique_copy(in2, eof2, std::back_inserter(nums));
//    std::sort(nums.begin(), nums.end());
//    std::for_each(nums.begin(), nums.end(), [](int i) { cout << i << " "; });
//    cout << endl;

    //

    // 10.36
    list<int> ilist4{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 0, 9, 9};
    auto rr = std::find(ilist4.crbegin(), ilist4.crend(), 0);
    cout << *rr << endl;

    // 10.37
    vector<int> ivec4{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> ilist5;
    copy(ivec4.crbegin() + 2, ivec4.crend() - 3, std::inserter(ilist5, ilist5.begin()));
    std::for_each(ilist5.begin(), ilist5.end(), [](int i) { cout << i << " "; });
    cout << endl;

    // 10.42
    list<string> word_list = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    word_list.sort();
    word_list.unique();
    std::for_each(word_list.begin(), word_list.end(), [](const string &i) { cout << i << " "; });
    cout << endl;
    return 0;
}
