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
#include <iostream>
#include <vector>
#include <set>

#include <algorithm>
#include <list>
#include <deque>
#include <iterator>
#include <unordered_map>
#include <memory>
#include <bitset>
#include <thread>
#include <future>

#include <string.h>
#include <assert.h>

#include "Sales_data.h"

using std::map; using std::multimap;
using std::set; using std::multiset;
using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;
using std::list;

struct TEST {
  int a = 1;
  int b = 2;
  int c = 3;
};

std::shared_ptr<int> helper(std::shared_ptr<int> &a) {
  a = std::make_shared<int>(4);
  return std::make_shared<int>(5);
}

// ignore 0
std::string binary(std::vector<std::pair<int, std::string>> &array, int key) {
  if (key < array[1].first)
    return array[0].second;
  else if (key >= array[array.size() - 1].first)
    return array[array.size() - 1].second;

  size_t low = 1, high = array.size() - 1, mid;
  while (low + 1 != high && low < high) {
    mid = low + (high - low)/2;
    if (array[mid].first < key) {
      low = mid;
    } else if (array[mid].first > key) {
      high = mid;
    } else {
      return array[mid].second;
    }
  }
  return array[low].second;
}

void binary_test() {
  std::vector<std::pair<int, std::string>> array = {
      {0, "[0,2)"}, {2, "[2,4)"}, {4, "[4,6)"}, {6, "[6,8)"}, {8, "[8,...)"}
  };
  cout << binary(array, 1) << " -> [0,2)" << endl;
  cout << binary(array, 2) << " -> [2,4)" << endl;
  cout << binary(array, 3) << " -> [2,4)" << endl;
  cout << binary(array, 4) << " -> [4,6)" << endl;
  cout << binary(array, 5) << " -> [4,6)" << endl;
  cout << binary(array, 6) << " -> [6,8)" << endl;
  cout << binary(array, 7) << " -> [6,8)" << endl;
  cout << binary(array, 8) << " -> [8,...)" << endl;
  cout << binary(array, 9) << " -> [8,...)" << endl;
}

class Checker {
public:
  ~Checker() {
    std::cout << "Checker: ~Checker()" << std::endl;
  }
};

struct Node {
  explicit Node() = default;
  Node(int i, int d) : id(i), data(d) {}
  int id = 0;
  int data = 1;
};

void range() {
  std::list<Node> ls;
  ls.emplace_back(1, 1);
  ls.emplace_back(2, 2);
  ls.emplace_back(3, 3);

  Node *cur = nullptr;
  for (auto &n: ls) {
    if (n.id == 1) {
      cur = &n;
    }
  }

  assert(cur != nullptr);
  cout << cur->data << endl;

  // test
  std::map<int, Node> m;
  m[1].id = 1;

  // test
  auto ptrs = std::make_shared<std::deque<int *>>();
  int a = 0, b = a;
  ptrs->push_back(&a);
  ptrs->clear();
  ptrs->push_back(&b);
}

int main() {
  vector<int> ivec{1, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8};
  vector<int> ilist{1, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8};
  set<int> iset(ivec.begin(), ivec.end());
  multiset<int> miset(ivec.begin(), ivec.end());

  cout << ivec.size() << endl;
  cout << iset.size() << endl;
  cout << miset.size() << endl;

  map<string, string> authors = {{"xing", "dong"},
                                 {"hello", "world"}};
  multimap<string, string> authors2 = {{"xing", "dong"},
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

  // unordered map: unlimited max bucket count, actually
  std::unordered_map<int, int> hstable;
  cout << hstable.bucket_count() << " " << hstable.max_bucket_count() << " " << sizeof(size_t) << endl;

  vector<bool> vec;
  cout << std::hash<std::vector<bool>>()(vec) << std::endl;

  // Test
  std::map<int, int> m;
  cout << TEST().a << TEST().b << TEST().c << endl;
  m.insert(std::make_pair(1, 2));

  std::shared_ptr<int> p1(new int(2));
  std::shared_ptr<int> p2(new int(3));
  p1.swap(p2);
  cout << *p1 << " " << *p2 << endl;
  p1 = p2;
  cout << (p1 == p2 ? "true" : "false") << " " << p1.use_count() << endl;

  p2 = helper(p1);
  cout << *p1 << "(" << p1.use_count() << ")" << " " << *p2 << "(" << p2.use_count() << ")" << endl;

  std::shared_ptr<int> p3;
  auto p4 = std::make_shared<int>(5);
  cout << (p3 == nullptr ? "true" : "false") << endl;

  // test
  cout << std::hash<string>()("1") << endl;
  cout << std::hash<string>()("2") << endl;
  cout << std::hash<int>()(3) << endl;
  cout << std::hash<int>()(4) << endl;
  cout << std::hash<int>()(5) << endl;
  cout << std::hash<int>()(6) << endl;
  cout << std::hash<int>()(7) << endl;
  cout << std::hash<int>()(8) << endl;
  cout << std::hash<int>()(123450) << endl;
  cout << std::hash<int>()(1) << endl;
  cout << std::hash<void *>()(&p1) << endl;

  // bitset
  int num = 6;
  std::bitset<3> s1(num);
  auto s = s1.to_string();
  std::reverse(s.begin(), s.end());
  cout << std::bitset<3>(s).to_ulong() << endl;

  // test bit reverse
  size_t bits = 2;
  int depth = 3;
  size_t sum = 0, factor = 1;
  int mask = 1 << depth;
  while (mask) {
    mask >>= 1;
    if (bits & mask) {
      sum += factor;
    }
    factor <<= 1;
  }
  cout << sum << endl;

  // test std::pair
  std::pair<int, int> a{1, 2};
  cout << sizeof(a) << endl;

  char ch[100] = {};
  cout << sizeof(ch) << endl;

  // test
  binary_test();

  std::pair<int, int> parray[0];
  cout << sizeof(parray) << endl;

  // memmove
  int array[5] = {1, 2, 3, 4, 5};
  memmove(array + 1, array, 4*sizeof(int));
  for (auto i:array) {
    std::cout << i << " ";
  }

  std::cout << "\nbefore Checker{}" << std::endl;
  __attribute__((unused)) auto checker = Checker{};
  std::cout << "after Checker{}" << std::endl;

  range();

  // background test
  std::cout << "Background....\n";
  std::promise<int> pro;
  std::atomic<bool> done{false};
  std::mutex latch;
  std::condition_variable cv;

  std::unique_lock<std::mutex> lock(latch);
  std::thread background([&]() {
    while (!done) {
      std::cout << "waiting....\n";
      if (cv.wait_for(lock, std::chrono::milliseconds(250)) == std::cv_status::timeout) {
        std::cout << "timeout....\n";
      }
    }
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  cv.notify_one();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  cv.notify_one();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  done = true;

  background.join();
  return 0;
}
