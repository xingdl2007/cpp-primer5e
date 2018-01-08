# Chapter 6 Functions

**Exercise 6.1:** What is the difference between a parameter and an argument?

```c++
// 实参是形参的初始值。函数调用时，用实参初始化形参。因此函数调用的时候，传递的参数必须满足初始化规则。
// parameter: 形参; argument: 实参
```

**Exercise 6.2:** Indicate which of the following functions are in error and why. Suggest how you might correct the problems.

```c++
(a) int f() { 
  		string s;
		// . . .
		return s; 
    }
(b) f2(int i){/* ... */}
(c) int calc(int v1,int v1)/* ... */} 
(d) double square(double x) return x * x;

---
(a) 返回值类型和函数声明不匹配；修改函数的返回类型为string
(b) 没有返回值时，要声明返回void类型，不能省略；加上void即可
(c) 修改为返回void，少了{
(d) 函数体需要在语句块中，缺少{}
```

**Exercise 6.3:** Write and test your own version of fact.

**Exercise 6.4:** Write a function that interacts with the user, asking for a number and generating the factorial of that number. Call this function from main.

**Exercise 6.5:** Write a function to return the absolute value of its argument.

```c++
int iabs(int p) {
    return std::abs(p);
}
```

**Exercise 6.6:** Explain the differences between a parameter, a local variable, and a local static variable. Give an example of a function in which each might be useful.

```c++
// 形参(parameter)：函数调用时会用实参进行初始化

// 局部变量(local variable)：函数体中定义的变量，作用域仅限函数内部，在其定义之后可见；形参也是局部变量。局部变量在作用域结束后即销毁，这样的变量也叫做自动对象。

// 局部静态变量(local static variable)：函数初次调用时初始化，函数返回之后仍然存在，同程序生命期一样长。如果局部静态变量没有显式的初始值，它将执行值初始化，内置类型的局部静态变量初始值为0。
```

**Exercise 6.7:** Write a function that returns 0 when it is first called and then generates numbers in sequence each time it is called again.

```c++
int calls() {
    static int ctr = 0;
    return ctr++;
}
```

**Exercise 6.8:** Write a header file named Chapter6.h that contains declarations for the functions you wrote for the exercises in § 6.1 (p. 205).

**Exercise 6.9:** Write your own versions of the fact.cc and factMain.cc files. These files should include your Chapter6.h from the exercises in the previous section. Use these files to understand how your compiler supports separate compilation.

**Exercise 6.10:** Using pointers, write a function to swap the values of two ints. Test the function by calling it and printing the swapped values.

**Exercise 6.11:** Write and test your own version of reset that takes a reference.

**Exercise 6.12:** Rewrite the program from exercise 6.10 in § 6.2.1 (p. 210) to use refer-ences instead of pointers to swap the value of two ints. Which version do you think would be easier to use and why?

**Exercise 6.13:** Assuming T is the name of a type, explain the difference between a function declared as void f(T) and void f(T&).

```c++
// void f(T): 参数是T类型，函数调用时，实参的值拷贝到形参，即形参执行拷贝初始化。
// void f(T&): 参数是T&类型（引用），函数调用时，形参bind到实参。
```

**Exercise 6.14:** Give an example of when a parameter should be a reference type. Give an example of when a parameter should not be a reference.

```c++
// 什么时候形参应该是引用类型？
// 参数是IO类型的函数，比如重载<<和>>运算符时，istream和ostream的参数必须是引用类型。因为IO类型不支持拷贝操作，函数只能通过引用参数访问该类型的对象。这个限制应用于所有不支持拷贝的类型。
// 还有一种情况就是当函数需要返回多个值时，可以用引用参数workaround。

// 什么时候又不应该是引用类型呢？
// 内置类型的形参一般都不是引用类型。可以使用字面值作为实参的情况，不应该是引用类型，传值会更加灵活。
```

**Exercise 6.15:** Explain the rationale for the type of each of find_char’s parameters In particular, why is s a reference to const but occurs is a plain reference? Why are these parameters references, but the char parameter c is not? What would happen if we made s a plain reference? What if we made occurs a reference to const?

```c++
// s是常量引用是因为函数执行期间不会修改s，限定为常量引用可以增加函数的使用范围，例如可以使用字符串字面量调用find_char函数。occurs是普通引用，是因为函数执行期间会修改occurs的值。

// char不是引用的原因是没有必要使用引用，如果是普通引用，则限制了函数的使用，此时字符字面值无法作为c的参数。而且内置类型拷贝开销小。

// 如果s改为普通引用，则减小了find_char的使用范围，字符串字面量就不能作为参数使用。

// 如果occurs修改为const引用，则无法再函数中修改occurs了。
```

**Exercise 6.16:** The following function, although legal, is less useful than it might be. Identify and correct the limitation on this function:

```c++
bool is_empty(string& s) { return s.empty(); }

---
// 局限性就是非const形参导致字符串字面量，e.g."hello"，无法作为实参调用函数。还有就是const string也无法使用该函数；字面值本质需要类型转换，会生成临时对象，编译器会禁止修改临时对象，因为这肯定不是程序的正常意图。
bool is_empty(const string& s) { return s.empty(); }
```

**Exercise 6.17:** Write a function to determine whether a string contains any capitalletters. Write a function to change a string to all lower case. Do the parameters you used in these functions have the same type? If so, why? If not, why not?

```c++
// 显然应该不同；
// 1. bool hasCapital(const string&);
// 2. void toLower(string &);
```

**Exercise 6.18:** Write declarations for each of the following functions. When you writethese declarations, use the name of the function to indicate what the function does.

(a) A function named `compare` that returns a bool and has two parameters that are references to a class named `matrix`.

(b) A function named `change_val` that returns a `vector<int>` iterator and takes two parameters: One is an int and the other is an iterator for a `vector<int>`.

```c++
bool compare(const matrix&, const matrix&);
std::vector<int>::iterator change_val(int, std::vector<int>::iterator);
```

**Exercise 6.19:** Given the following declarations, determine which calls are legal and which are illegal. For those that are illegal, explain why.

```c++
double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int); 
vector<int> vec(10);

(a) calc(23.4, 55.1); 	(b) count("abcda", ’a’);
(c) calc(66); 			(d) sum(vec.begin(), vec.end(), 3.8);

---
(a) illegal，参数个数不匹配
(b) legal
(c) legal
(d) legal
```

**Exercise 6.20:** When should reference parameters be references to const? What happens if we make a parameter a plain reference when it could be a reference to const?

```c++
// 不修改参数的情况下
// 限制使用范围，const对象、字面值或者需要类型转换的对象无法传递给普通引用。
```

**Exercise 6.21:** Write a function that takes an int and a pointer to an int and returns the larger of the int value or the value to which the pointer points. What type should you use for the pointer?

```c++
// 应该是const int *
```

**Exercise 6.22:** Write a function to swap two int pointers.

```c++
std::swap(pa,pb);
```

**Exercise 6.23:** Write your own versions of each of the print functions presented in this section. Call each of these functions to print i and j defined as follows:

```c++
int i = 0, j[2] = {0, 1};

---
// from book: print ints in the given range
void print(const int *beg, const int *end) {
    // print every element starting at beg up to but not including end
    while (beg != end)
        cout << *beg++ << " "; // print the current element
    // and advance the pointer
}
```

**Exercise 6.24:** Explain the behavior of the following function. If there are problems in the code, explain what they are and how you might fix them.

```c++
void print(const int ia[10])
{
	for (size_t i = 0; i != 10; ++i) cout << ia[i] << endl;
}

---
// 这个函数的问题在与，数组的长度不是固定为10，形参中的10会被编译器忽略，可以传递长度小于的10的组数
// 如何要强制只能接受长度为10的数组，可以修改形参为:
// const int (*ia)[10] 或者 const int (&int)[10]
```

**Exercise 6.25:** Write a main function that takes two arguments. Concatenate the supplied arguments and print the resulting string.

**Exercise 6.26:** Write a program that accepts the options presented in this section. Print the values of the arguments passed to main.

**Exercise 6.27:** Write a function that takes an `initializer_list<int>` and produces the sum of the elements in the list.

```c++
int sum(std::initializer_list<int> array) {
    int sum = 0;
    for (auto item:array) {
        sum += item;
    }
    return sum;
}
```

**Exercise 6.28:** In the second version of error_msg that has an ErrCode parameter,what is the type of elem in the for loop?

```c++
const string &
```

**Exercise 6.29:** When you use an initializer_list in a range for would you everuse a reference as the loop control variable? If so, why? If not, why not?

```c++
// 是否声明为引用类型要看initializer_list中存放的对象类型，如果是内置类型，不需要声明为引用类型；如果对象可能会很大，则应该声明为引用类型。如果声明为引用类型，则实际类型为常量引用，因为initializer_list中存放的是const的。
```

**Exercise 6.30:** Compile the version of str_subrange as presented on page 223 to see what your compiler does with the indicated errors.

**Exercise 6.31:** When is it valid to return a reference? A reference to const?

```c++
// C++中，函数完成后，它所占用的存储空间也随之被释放掉了。因此函数终止意味着局部变量的引用将指向不再有效的内存区域。
// 试图返回局部自动变量的引用是在C++中是严重的错误。同样的，返回局部对象的指针也是错误的。
// 如果函数形参是引用，则可以返回引用。一般如果形参是const的，则返回值也最好是const的。
```

**Exercise 6.32:** Indicate whether the following function is legal. If so, explain what it does; if not, correct any errors and then explain it.

```c++
int &get(int *arry, int index) { return arry[index]; }
int main() {
    int ia[10];
    for (int i = 0; i != 10; ++i)
        get(ia, i) = i;
}

---
// legal: 功能是数组赋值
```

**Exercise 6.33:** Write a recursive function to print the contents of a vector.

**Exercise 6.34:** What would happen if the stopping condition in `factorial` were if `(val != 0)`

```c++
// 无法处理参数为负数的情况
```

**Exercise 6.35:** In the call to factorial, why did we pass `val - 1` rather than `val--`?

```c++
// 显然；后面还要乘以val，两个表达式都需要使用val，首先求值顺序不确定，即使确定也是错误的。
```

**Exercise 6.36:** Write the declaration for a function that returns a reference to an array of ten strings, without using either a trailing return, decltype, or a type alias.

```c++
std::string (&func())[10] {
    std::cout << __func__ << std::endl;
    // ....
}
```

**Exercise 6.37:** Write three additional declarations for the function in the previous ex-ercise. One should use a type alias, one should use a trailing return, and the thirdshould use decltype. Which form do you prefer and why?

```c++
// type alias
typedef std::string strT[10] // using strT = string[10] /*better*/
strT &func(){
	std::cout << __func__ << std::endl;
  	// ...
}
// tailing return type
auto func() -> string(&)[10] {
  	std::cout << __func__ << std::endl;
  	// ...
}

// decltype
std::string some[10];
decltype(some) func() {
	std::cout << __func__ << std::endl;
  	// ...
}

// 个人觉得最好的是tailing return type; 因为更加清晰，函数名更加重要，返回类型有明确指示；类似的C++11引入的别名声明using语句也使得描述更清晰。
```

**Exercise 6.38:** Revise the arrPtr function on to return a reference to the array.

```c++
// returns a pointer to an array of five int elements
decltype(odd) &arrRef(int i) {
    return (i % 2) ? odd : even; // returns a pointer to the array
}
```

**Exercise 6.39:** Explain the effect of the second declaration in each one of the following sets of declarations. Indicate which, if any, are illegal.

```c++
(a) int calc(int, int);
	int calc(const int, const int);
(b) int get(); 
	double get();
(c) int *reset(int *); 
	double *reset(double *);

---
(a) illegal
(b) illegal
(c) legal
```

**Exercise 6.40:** Which, if either, of the following declarations are errors? Why?

```c++
(a) int ff(int a,int b=0,int c=0);
(b) char *init(int ht = 24, int wd, char bckgrnd);

---
(a) legal
(b) illegal

// 一点某个形参被赋予了默认值，则它后面的所有形参都必须要有默认值。用作默认实参的名字在函数声明所在的作用域解析，而这些名字的求值过程发生在函数调用时(这就给修改这些默认值留下了时间) 
```

**Exercise 6.41:** Which, if any, of the following calls are illegal? Why? Which, if any, are legal but unlikely to match the programmer’s intent? Why?

```c++
char *init(int ht, int wd = 80, char bckgrnd = ’ ’);
(a) init(); (b) init(24,10); (c) init(14, ’*’);

---
(a) illegal，缺少参数
(b) legal
(c) legal，但是和程序员的初衷不符
```

**Exercise 6.42:** Give the second parameter of make_plural (§ 6.3.2, p. 224) a default argument of ’s’. Test your program by printing singular and plural versions of the words success and failure.

```c++
inline
string make_plural(size_t ctr, const string &word,
                   const string &ending = "s") {
    return (ctr > 1) ? word + ending : word;
}
```

**Exercise 6.43:** Which one of the following declarations and definitions would you put in a header? In a source file? Explain why.

```c++
(a) inline bool eq(const BigInt&, const BigInt&) {...} 
(b) void putValues(int *arr, int size);

---
(a) inline函数定义，放在头文件中，因为可能在编译时展开，需要保证定义一致。
(b) 函数声明，同样应该放在头文件中。
```

**Exercise 6.44:** Rewrite the isShorter function from § 6.2.2 (p. 211) to be inline.

```c++
inline bool isShorter(const std::string &s1, const std::string &s2) {
    return s1.size() < s2.size();
}
```

**Exercise 6.45:** Review the programs you’ve written for the earlier exercises and decide whether they should be defined as inline. If so, do so. If not, explain why they should not be inline.

**Exercise 6.46:** Would it be possible to define isShorter as a constexpr? If so, doso. If not, explain why not.

```c++
// 不可以，isShorter函数调用了std::string的size()成员函数。
// 编译器提示：call to non-constexpr function
```

**Exercise 6.47:** Revise the program you wrote in the exercises in § 6.3.2 (p. 228) that used recursion to print the contents of a vector to conditionally print information about its execution. For example, you might print the size of the vector on each call. Compile and run the program with debugging turned on and again with it turned off.

**Exercise 6.48:** Explain what this loop does and whether it is a good use of assert:

```c++
string s;
while (cin >> s && s != sought) { } // empty body 
assert(cin);

---
// 过滤输入string，直到遇到sought；合理
```

**Exercise 6.49:** What is a candidate function? What is a viable function?

```c++
// candidate function: 重载函数集中的函数 候选函数
// viable function: 根据本次调用提供的实参，从候选函数中选择出来的函数为 可行函数
```

**Exercise 6.50:** Given the declarations for f from page 242, list the viable functions, ifany for each of the following calls. Indicate which function is the best match, or if thecall is illegal whether there is no match or why the call is ambiguous.

```c++
(a) f(2.56, 42) (b) f(42) (c) f(42, 0) (d) f(2.56, 3.14)
 
---
(a) 二义性调用
(b,c,d)精确匹配
```

**Exercise 6.51:** Write all four versions of f. Each function should print a distinguishing message. Check your answers for the previous exercise. If your answers were incorrect, study this section until you understand why your answers were wrong.

```c++
#include <iostream>

using std::cout; using std::endl;

void f() {
    cout << "f()" << endl;
}

void f(int a) {
    cout << "f(int a)" << endl;
}

void f(int a, int b) {
    cout << "f(int a, int b)" << endl;
}

void f(double a, double b = 3.14) {
    cout << "f(double a, double b = 3.14)" << endl;
}

int main() {
    f(5.6);
    f(42);
    f(42, 0);
    f(2.56, 3.14);
    return 0;
}
```

**Exercise 6.52:** Given the following declarations,

```c++
void manip(int, int); 
double dobj;
```

what is the rank (§ 6.6.1, p. 245) of each conversion in the following calls?

```c++
(a) manip(’a’, ’z’); (b) manip(55.4, dobj);

---
(a) 整型提升，rank 3
(b) 算数类型转换， rank 4
```

**Exercise 6.53:** Explain the effect of the second declaration in each one of the following sets of declarations. Indicate which, if any, are illegal.

```c++
(a) int calc(int&, int&);
	int calc(const int&, const int&);
(b) int calc(char*, char*);
	int calc(const char*, const char*);
(c) int calc(char*, char*);
	int calc(char* const, char* const);

---
(a) const版本，合法
(b) const版本，合法
(c) 忽略形参const，非法
```

**Exercise 6.54:** Write a declaration for a function that takes two int parameters and returns an int, and declare a vector whose elements have this function pointer type.

```c++
int func(int,int);
std::vector<int(*)(int,int)>;
```

**Exercise 6.55:** Write four functions that add, subtract, multiply, and divide two intvalues. Store pointers to these functions in your vector from the previous exercise.

```c++
#include <iostream>
#include <vector>
using std::cout; using std::endl;
using std::vector;

int add(int a, int b) {
    return a + b;
}
int subtract(int a, int b) {
    return a - b;
}
int multiply(int a, int b) {
    return a * b;
}
int divide(int a, int b) {
    return a / b;
}
int main() {
    std::vector<int (*)(int, int)> methods = {add, subtract, multiply, divide};
    return 0;
}
```

**Exercise 6.56:** Call each element in the vector and print their result.

```c++
int main() {
    std::vector<int (*)(int, int)> methods = {add, subtract, multiply, divide};
    int a = 12, b = 6;
    for (auto m:methods) {
        cout << m(a, b) << endl;
    }
    return 0;
}
```

### Notes

- C++中函数的返回类型不能是数组类型或函数类型，但可以是指向数组或函数的指针。

- 一种特殊的返回类型是void，它表示函数不返回任何值。但是不能省略。

- C++语言中，<u>名字有作用域，对象有生命期</u>。

- > 名字的作用域是程序文本的一部分，名字在其中可见。
  >
  > 对象的声明周期是程序执行过程中该对象存在的一段时间。


- 含有函数声明的头文件应该包含到定义该函数的头文件中。
- 函数每次被调用的时候都会重新创建它的形参，并用实参来进行初始化。<u>形参初始化的机理与变量初始化一样。</u>形参的类型决定了形参与实参的交互方式。如果形参是引用类型，它将绑定到对应的实参上。否则，将实参的值拷贝后赋给形参。
- passed by reference: 形参是实参的别名；passed by value: 形参和实参是两个独立的对象。注意指针也是passed by value。
- C++中建议使用引用类型的形参代替指针，可以避免拷贝。(引用在编译器层面使用指针实现的)


- 如果形参是const的，当用实参初始化形参时会忽略掉顶层const。传给它常量对象或者非常量对象都是可以的。

- > void func(const int i)  { /* */ }
  >
  > void func(int i)  { /* */ }             // 错误，重复定义func


- 把函数不会改变的形参定义为普通引用是一种比较常见的错误，这么做会给函数的调用者一种误导，即函数可以修改它的实参的值。此外，使用引用而非常量引用也会<u>极大的限制</u>函数所能接受的实参类型。<u>不能把const对象，字面值或者需要类型转换的对象传递给普通的引用形参</u>。
- 数组的两个性质：<u>不允许拷贝数组以及使用数组时（通常）会将其转换为指针</u>。<u>因为不能拷贝数组，所以无法以值传递的方式使用数组参数。</u>因为数组会被转换成指针，所以当我们为函数传递一个数组时，实际上传递的时指向数组首元素的指针。（为啥不允许数组的拷贝呢？基于效率的考虑？）


- initializer_list对象中的元素<u>永远是常量值</u>，无法改变其中的元素；所以当拷贝或者赋值一个initializer_list对象时不会拷贝赋值列表中的元素；拷贝后，原始列表和副本<u>共享</u>元素。


- 返回一个值的方式和初始化一个变量或形参的方式完全一样：返回的值用于初始化调用点的一个临时量，该临时量就是函数调用的结果。
- <u>decltype并不负责把数组类型转换成对应的指针类型，所以decltype的结果是个数组。</u>
- <u>函数匹配</u>是指一个过程，在这个过程中我们把函数调用与一组重载函数中的某一个关联起来，函数匹配也叫做<u>重载确定</u>。
- 当调用重载函数时有三个可能结果：<u>最佳匹配、无匹配、二义性调用</u>。
- <u>constexpr函数</u>是指能用于常量表达式的函数。定义constexpr函数的方法与其他函数类似，不过要遵循几项约定：<u>函数的返回值类型以及所有形参的类型都得是字面值类型，而且函数体中必须有且只有一条return语句</u>。
- <u>constexpr函数不一定返回常量表达式</u>。（这一点还是挺令人惊奇的）。另外编译器需要把对constexpr函数的调用在编译时展开，用其结果替换，<u>constexpr函数被隐式的指定为内联函数</u>。
- <u>内联函数和constexpr函数放在头文件内</u>：和其他函数不一样，内联函数和constexpr函数可以在程序中多次定义。毕竟，编译器要想展开仅有函数声明是不够的，还需要函数的定义。不过，对于某个给定的内联或者constexpr函数，它的多个定义必须完全一致。基于这个原因，<u>内联函数和constexpr函数通常定义在一个头文件中</u>。
- `__func__`：C++编译器为每个函数都定义了，它是const char的一个静态数组，用于存放函数的名字。
- 以下几个都是预处理器定义的4个对于调试很有用的名字：
- `__FILE__`：存放文件名的字符串字面值。
- `__LINE__`：存放当前行号的整型字面值。
- `__TIME__`：存放文件编译时间的字符串字面值。
- `__DATE__`：存放文件编译日期的字符串字面值。


- <u>牢记当我们将decltype作用于某个函数的时候，它返回函数类型而非指针类型（跟作用于数组时是一致的）</u>。