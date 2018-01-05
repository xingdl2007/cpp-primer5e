# Chapter 2 Variables and Basic Types

**Exercise 2.1:** What are the differences between int, long, long long, and short? Between an unsigned and a signed type? Between a float and a double?

```
short,int,long,long long: 位宽不同，语言标准仅定义最低位宽，cpu-arch相关
unsigned,singed: 有符号，无符号数
float,double: 精度不同，因为使用的不同的位宽来表示
```

**Exercise 2.2:** To calculate a mortgage payment, what types would you use for the rate, principal, and payment? Explain why you selected each type.

```
利率（rate）：浮点类型 e.g. double
本金（principal）：整型/浮点类型 e.g. unsigned/double
付款（payment）：浮点类型 e.g. double

整型在计算机中是精确的，没有误差；浮点类型表示的实数有精度限制，不是精确的。
```

**Exercise 2.3:** What output will the following code produce?

```c++
unsigned u = 10, u2 = 42;
std::cout << u2 - u << std::endl;  // 32
std::cout << u - u2 << std::endl;  // 4294967264
int i = 10, i2 = 42;
std::cout << i2 - i << std::endl;  // 32
std::cout << i - i2 << std::endl;  // -32
std::cout << i - u << std::endl;   // 0
std::cout << u - i << std::endl;   // 0
```

**Exercise 2.4:** Write a program to check whether your predictions were correct. If not, study this section until you understand what the problem is.

```
正确
```

**Exercise 2.5:** Determine the type of each of the following literals. Explain the differences among the literals in each of the four examples:

```c++
(a) ’a’,L’a’,"a",L"a"
    'a' : char
	L'a': wchar_t
	"a" : char[]
	L"a": wchar_t[]
(b) 10,10u,10L,10uL,012,0xC 
    10  : int
	10u : unsigned int
	10L : long
	10uL: unsigned long
	012 : int
	0xC : int
(c) 3.14,3.14f,3.14L
    3.14 : double
	3.14f: float
	3.14L: long double
(d) 10,10u,10.,10e-2
    10   : int
	10u  : unsigned int
	10.  : double
	10e-2: double
```


**Exercise 2.6:** What, if any, are the differences between the following definitions:

```c++
int month = 9, day = 7;
int month = 09, day = 07;

字面值一个是十进制，一个是八进制，其他无区别
```

**Exercise 2.7:** What values do these literals represent? What type does each have?

```c++
(a) "Who goes with F\145rgus?\012"
(b) 3.14e1L (c) 1024f (d) 3.14L
  
答：
(a) Who goes with Fergus\n?
(b) 31.4 (long double)
(c) 1024.0 (float)
(d) 3.14 (long double)
```

**Exercise 2.8:** Using escape sequences, write a program to print 2M followed by a newline. Modify the program to print 2, then a tab, then an M, followed by a newline.

```c++
std::cout << "2M\n";
std::cout << "2\tM\n";				
```


**Exercise 2.9:** Explain the following definitions. For those that are illegal, explain what’s wrong and how to correct it.

```c++
(a) std::cin >> int input_value; 
	wrong: int input_value; std::cin >> input_value;

(b) int i = { 3.14 }; 
	wrong: double i = {3.14};
      
(c) double salary = wage = 9999.99; 
	wrong: double salary=9999.99, wage=salary;

(d) int i = 3.14;
    wrong: double i = 3.14
```

**Exercise 2.10:** What are the initial values, if any, of each of the following variables?

```c++
std::string global_str;
int global_int;
int main() {
	int local_int;
	std::string local_str;
}

global_str: ""(empty string)
global_int: 0
local_int : uninitialized（undefined value）
local_str : ""(empty string)
```


**Exercise 2.11:** Explain whether each of the following is a declaration or a definition:

```c++
(a) extern int ix = 1024; 
	defination
	
(b) int iy;
	defination

(c) extern int iz;
	declaration
```

**Exercise 2.12:** Which, if any, of the following names are invalid?

```c++
(a) int double = 3.14; 
	invalid

(b) int _;
	valid

(c) int catch-22; 
	invalid (because of '-')

(d) int 1_or_2 = 1; 
	invalid (because of '1', start with number)

(e) double Double = 3.14;
	valid
```

**Exercise 2.13:** What is the value of j in the following program?

```c++
int i = 42;
int main() {
	int i = 100;
	int j = i; 
}

---
100
```

**Exercise 2.14:** Is the following program legal? If so, what values are printed?

```c++
int i = 100, sum = 0;
for (int i = 0; i != 10; ++i)
	sum += i;
std::cout << i << " " << sum << std::endl;

---
100 45
```

**Exercise 2.15:** Which of the following definitions, if any, are invalid? Why?

```c++
(a) int ival = 1.01; 
	valid (会进行初始值的类型转换)

(b) int &rval1 = 1.01;
	invalid (1.01 字面量不是变量，普通引用需要bind到变量)

(c) int &rval2 = ival; 
	valid

(d) int &rval3;
	invalid (引用没有初始化)
```

**Exercise 2.16:** Which, if any, of the following assignments are invalid? If they are valid, explain what they do.			

```c++
int i = 0, &r1 = i; double d = 0, &r2 = d; 
(a) r2 = 3.14159; 
	valid, d = 3.14159;

(b) r2 = r1;
	valid，d = 0.0;

(c) i=r2;
	valid, i = 3;

(d) r1=d;
	valid, i = 3;
```

**Exercise 2.17:** What does the following code print?				

```c++
int i, &ri = i;
i = 5; ri = 10;
std::cout << i << " " << ri << std::endl;

---
10 10
```

**Exercise 2.18:** Write code to change the value of a pointer. Write code to change the value to which the pointer points.

```c++
int i = 100, j = 101, *p;
p = &i;
std::cout << *p << std::endl;
p = &j;
std::cout << *p << std::endl;

---
  
int i = 100, *p = &i;
*p += 1;
std::cout << *p << std::endl;
```

**Exercise 2.19:** Explain the key differences between pointers and references.

```c++
// 指针是对象，可以修改其值，也就是指向了另外的对象。
// 引用是别名不是对象，仅在初始化时绑定到某对象，在其生命周期中不能修改而绑定到另外的对象。
```

**Exercise 2.20:** What does the following program do?

```c++
int i = 42;
int *p1 = &i;
*p1 = *p1 * *p1;

---
42*42
```

**Exercise 2.21:** Explain each of the following definitions. Indicate whether any are illegal and, if so, why.

```c++
int i = 0;
(a) double *dp=&i; 
	illegal, base类型错误

(b) int *ip=i; 
	illegal, i不是指针

(c) int *p=&i;
	legal
```

**Exercise 2.22:** Assuming p is a pointer to int, explain the following code:

```c++
if (p)  // ... if p不是空指针
if (*p) // ... if p指向的对象不是0
```

**Exercise 2.23:** Given a pointer p, can you determine whether p points to a valid object? If so, how? If not, why not?

```c++
// 可以检查指针p是否指向了某个对象，还是空，仅此而已。如果不是空指针，至于指针指向的对象是否是valid，无法判断。
```

**Exercise 2.24:** Why is the initialization of p legal but that of lp illegal?

```c++
int i=42; void *p=&i; long *lp=&i;

void* 指针可以存放任意类型的指针。
```

**Exercise 2.25:** Determine the types and values of each of the following variables.

```c++
(a) int *ip,i,&r=i;
	ip,i的初始值取决于定位的位置，如果是全局的则为0，否则是未初始化的，未定义的；r是i的引用。

(b) int i, *ip=0; 
	i的初始值取决于定位的位置，如果是全局的则为0，否则是未初始化的，未定义的；ip为0，空指针。

(c) int *ip, ip2;
	ip/ip2的初始值取决于定位的位置，如果是全局的则为空指针/0，否则是未初始化的，未定义的；
```

**Exercise 2.26:** Which of the following are legal? For those that are illegal, explain why.

```c++
(a) const int buf;
	illegal, 没有初始化式

(b) int cnt = 0; 
	legal

(c) const int sz = cnt; 
	legal(运行时初始化)

(d) ++cnt; ++sz;
	illegal, sz是常量，不能修改
```

**Exercise 2.27:** Which of the following initializations are legal? Explain why.

```c++
(a) int i = -1, &r = 0; 
	illegal

(b) int *const p2 = &i2;
	legal, const指针有初始化式

(c) const int i = -1, &r = 0; 
	legal, const变量和引用都有初始化式

(d) const int *const p3 = &i2;
	legal， 指向const对象的const指针包含初始化式

(e) const int *p1 = &i2; 
	legal，要求i2是常量对象

(f) const int &const r2;
	illegal

(g) const int i2 = i, &r = i;
	illegal
```

**Exercise 2.28:** Explain the following definitions. Identify any that are illegal.

```c++
(a) int i, *const cp;
	illegal，缺少初始化式

(b) int *p1, *const p2;
	illegal, p2是常量指针，缺少初始化式

(c) const int ic, &r = ic;
	illegal, ic没有出初始化

(d) const int *const p3;
	illegal, p3是指向常量的常量指针，没有初始化式

(e) const int *p;
	legal, p是指向常量的普通指针，可以没有初始化式
```

**Exercise 2.29:** Uing the variables in the previous exercise, which of the following assignments are legal? Explain why.

```c++
(a) i = ic;
	legal, 普通变量赋值

(b) p1 = p3; 
	legal, 普通指针赋值

(c) p1 = &ic; 
	illegal, ic是const的

(d) p3 = &ic; 
	illegal, const指针不能修改

(e) p2 = p1;
	illegal, const指针不能修改

(f) ic = *p3;
	illegal, const变量不能修改
```

**Exercise 2.30:** For each of the following declarations indicate whether the object being declared has top-level or low-level const.

```c++
const int v2 = 0; int v1 = v2;
int *p1 = &v1, &r1 = v1;
const int *p2 = &v2, *const p3 = &i, &r2 = v2;

v1, v2: top-level const
p1: non const
p2: low-level const
p3: top-level and low-level const
  
r2: low-level const

all reference is top-level const by default
```

**Exercise 2.31:** Given the declarations in the previous exercise determine whether the following assignments are legal. Explain how the top-level or low-level const applies in each case.

```c++
r1 = v2;
legal: top-level const不影响赋值，v2的const属性不变化

p1 = p2; p2 = p1; 
p1 = p2: legal
p2 = p1: illegal, low-leval const不同

p1 = p3; p2 = p3;
p1 = p3: illegal, p1和p3的low-level const不同
p2 = p3: legal, p2和p3的low-level const相同


// 在赋值时，如果被拷贝一侧有low-level const，则待赋值的对象也必须有low-level const.
```

**Exercise 2.32:** Is the following code legal or not? If not, how might you make it legal?

```c++
int null = 0, *p = null;

---
illegal: int null = 0, *p = nullptr;
```

**Exercise 2.33:** Using the variable definitions from this section, determine what happens in each of these assignments:

```c++
a=42; b=42; c=42;
d=42; e=42; g=42;

---
type of a: int
type of b: int
type of c: int
type of d: int *
type of e: const int *
type of f: const int
type of g: const int &
  
// 以上是a-g的类型，推断出a,b,c的赋值可以执行，d,e,g编译错误。
```

**Exercise 2.34:** Write a program containing the variables and assignments from the previous exercise. Print the variables before and after the assignments to check whether your predictions in the previous exercise were correct. If not, study the examples until you can convince yourself you know what led you to the wrong conclusion.

**Exercise 2.35:** Determine the types deduced in each of the following definitions. Once you’ve figured out the types, write a program to see whether you were correct.

```c++
const int i = 42;
auto j = i; const auto &k = i; auto *p = &i; 
const auto j2 = i, &k2 = i;

---
type of j : int
type of k : const int &
type of p : const int *
type of j2: const int
type of k2: const int &
```

**Exercise 2.36:** In the following code, determine the type of each variable and the value each variable has when the code finishes:

```c++
int a = 3, b = 4;
decltype(a) c = a;
decltype((b)) d = a;
++c;
++d;

---
a: int, 4
b: int, 4
c: int, 4
d: int &,4 
```

**Exercise 2.37:** Assignment is an example of an expression that yields a reference type. The type is a reference to the type of the left-hand operand. That is, if i is an int, then the type of the expression i = x is int&. Using that knowledge, determine the type and value of each variable in this code:

```c++
int a = 3, b = 4;
decltype(a) c = a;
decltype(a = b) d = a;

---
a: int, 3
b: int, 4
c: int, 3
d: int &, 3

// 虽然a=b表达式返回的是a的引用，但是这个赋值表达式不会真的执行，所以a的值不会改变
```

**Exercise 2.38:** Describe the differences in type deduction between decltype and auto. Give an example of an expression where auto and decltype will deduce the same type and an example where they will deduce differing types.

```c++
int i = 0;
decltype(i) j = i;
auto k = i;

j: int
k: int

---
int i = 100, &j = i;
decltype(j) k1 = i;
auto k2 = j;

k1: int & 
k2: int

// 区别还是很大的，特别是对引用的处理，decltype对表达式会返回引用类型
```

**Exercise 2.39:** Compile the following program to see what happens when you forget the semicolon after a class definition. Remember the message for future reference.

```c++
struct Foo { /* empty */ } // Note: no semicolon 
int main()
{
	return 0; 
}

---
expected ';' after struct definition
```

**Exercise 2.40:** Write your own version of the Sales_data class.

```c++
struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
```

**Exercise 2.41:** Use your Sales_data class to rewrite the exercises in § 1.5.1 (p. 22),§ 1.5.2 (p. 24), and § 1.6 (p. 25). For now, you should define your Sales_data class in the same file as your main function.

**Exercise 2.42:** Write your own version of the Sales_data.h header and use it to rewrite the exercise from § 2.6.2 (p. 76).

```c++
// 参见作者配套代码
```

### Notes

- 数据类型是程序的基础：它告诉我们数据的意义以及我们能在数据上执行的操作。
- 空类型（void）不对应具体的的值，仅用于一些特殊的场合，e.g.当函数不返回任何值时使用空类型作为返回类型。
- 对C++程序来说，“变量（variable）”和“对象(object)”一般可以互换使用。
- 在C++语言中，初始化和赋值是两个完全不同的操作：初始化不是赋值，初始化的含义是创建变量时赋予其一个初始值，而赋值的含义是把对象的当前值擦除，而以一个新值来替代。
- 声明和定义的区别看起来也许微不足道，但实际上却非常重要。如果要在多个文件中使用同一个变量，就必须将声明和定义分离。
- “用户自定义的标识符中不能连续两个下划线，也不能以下划线紧邻大写字母开头。此外，定义在函数体外的标识符不能以下划线开头”：**但是在gcc 7.2.0中均不成立，编译器会接受上文所述的变量名**。
- 一旦初始化完成，引用将和它的初始值对象绑定在一起。因为无法令引用重新绑定到另外一个对象，因此引用必须初始化。
- 指针的声明语句中指针的类型实际上被用于指定它所指向对象的类型，所以两者必须匹配。
- const对象必须初始化，可以在编译时或者运行时。
- 指针本身是一个对象，它又指向另外一个对象。因此，指针本身是不是常量以及指针所指的是不是一个常量就是两个相互独立的问题。用名词顶层const（top-level const）表示指针本身是个常量，而用名词底层const（low-level const）表示指针所指向的对象是一个常量。
- 常量表达式是指值不会改变并且在编译过程就能得到计算结果的表达式。
- C++新标准规定，允许将变量声明为constexpr类型以便由编译器来验证变量的值是否是一个常量表达式。声明为constexpr的变量一定是一个常量，而且必须用常量表达式初始化。
- 目前为止，只有指针、引用、算数类型是“字面值类型”，只有这些才能用在constexpr声明之中。尽管指针和引用都能定义成constexpr，但它们的初值却受到严格限制。一个constexpr指针的初始值必须是nullptr或者0，或者是存储于某个固定地址中的对象。constexpr声明中如果定义了一个指针，限定符constexpr仅对指针有效，而对指针所指向的对象无关（关关键在于constexpr把它所定义的对象置为了顶层const）。
- 引用从来都是作为所指对象的同义词出现，只有用在decltype处是一个例外。
- decltype()(variable))（注意是双层括号）的结果永远是引用，而decltype(variable)结果只有当variable本身就是一个运用时才是引用。