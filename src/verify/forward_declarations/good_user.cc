// from: google cpp sytle guide
// Notes:
// 1. use "b.h" header file, test(D *) will invoke func(B *)
#include "b.h"
#include <iostream>

// 2. use forward decls, test(D *) will invoke func(void *).
// so use header or forward decls can change the meaning of code

// class B;
// class D;

using namespace std;

void func(B *b) { cout << "func(B *b)" << '\n'; }

void func(void *t) { cout << "func(void *t)" << '\n'; }

void test(D *x) { func(x); }
