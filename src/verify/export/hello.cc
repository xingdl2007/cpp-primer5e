#include <iostream>

using namespace std;

// can be called in c code, export C API
extern "C" void sayHello() { cout << "Hello World from sayHello!\n"; }

// can be called only in c++ code
void Hello() { cout << "Hello World from Hello!\n"; }
