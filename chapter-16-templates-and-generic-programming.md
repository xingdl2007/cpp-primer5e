# Chapter 16 Templates and Generic Programming

​		
**Exercise 16.1:** Define instantiation.

```c++
// 实例化：编译器根据提供的模板参数生成一个特定的函数或类的过程。
```

**Exercise 16.2:** Write and test your own versions of the compare functions.

**Exercise 16.3:** Call your compare function on two Sales_data objects to see howyour compiler handles errors during instantiation.

```c++
error: no match for 'operator<' (operand types are 'const Sales_data' and 'const Sales_data')
     if (v1 < v2) { return -1; }
```

**Exercise 16.4:** Write a template that acts like the library find algorithm. The function will need two template type parameters, one to represent the function’s iterator parameters and the other for the type of the value. Use your function to find a given value in a `vector<int>` and in a `list<string>`.

```c++
template<typename T, typename V>
T find(const T &b, const T &e, V v) {
    T ret = b;
    while (ret != e) {
        if (*ret == v) {
            return ret;
        } else {
            ++ret;
        }
    }
    return e;
};
```

**Exercise 16.5:** Write a template version of the print function from § 6.2.4 (p. 217) that takes a reference to an array and can handle arrays of any size and any element type.

```c++
template<typename T, unsigned N>
void print(T (&arr)[N]) {
    for (auto e:arr) {
        cout << e << endl;
    }
}
```

**Exercise 16.6:** How do you think the library begin and end functions that take an array argument work? Define your own versions of these functions.

```c++
template<typename T, unsigned N>
T *begin(T (&arr)[N]) {
    return arr;
};

template<typename T, unsigned N>
T *end(T (&arr)[N]) {
    return arr + N;
};
```

**Exercise 16.7:** Write a constexpr template that returns the size of a given array.

```c++
template<typename T, unsigned N>
constexpr unsigned arraySize(T (&array)[N]) {
  return N;
};
```

**Exercise 16.8:** In the “Key Concept” box on page 108, we noted that as a matter of habit C++ programmers prefer using `!=` to using `<`. Explain the rationale for this habit.

```c++
// 主要是由于迭代器引起的；作为语言的一种约定；因为迭代器标准接口中只有!=，也就是说迭代器都支持不等判断，但不能保证迭代器支持<操作；依赖<会限制算法的适用范围。
```

**Exercise 16.9:** What is a function template? What is a class template?

```c++
// function template: 生成函数的blueprint
// class template: 生成类的blueprint
```

**Exercise 16.10:** What happens when a class template is instantiated?

```c++
// 编译器使用类模板的类型实参重写模板，生成一个特定的类，其中只有被用到的成员才会实例化。
```

**Exercise 16.11:** The following definition of List is incorrect. How would you fix it?

```c++
template <typename elemType> class ListItem; 
template <typename elemType> class List { 
public:
	List<elemType>();
	List<elemType>(const List<elemType> &); 
  	List<elemType>& operator=(const List<elemType> &); 
  	~List();
	void insert(ListItem *ptr, elemType value);
private:
    ListItem *front, *end;
};

---
template <typename elemType> class ListItem; 
template <typename elemType> class List { 
public:
	List<elemType>();
	List<elemType>(const List<elemType> &); 
  	List<elemType>& operator=(const List<elemType> &); 
  	~List();
	void insert(ListItem<elemType> *ptr, elemType value);
private:
    ListItem<elemType> *front, *end;
};
```

**Exercise 16.12:** Write your own version of the Blob and BlobPtr templates. including the various const members that were not shown in the text.

**Exercise 16.13:** Explain which kind of friendship you chose for the equality and relational operators for BlobPtr.

```c++
// 一对一的友元关系
```

**Exercise 16.14:** Write a Screen class template that uses nontype parameters to definethe height and width of the Screen.

```c++
template<unsigned H, unsigned W>
class Screen;

template<unsigned H, unsigned W>
ostream &operator<<(ostream &os, Screen<H, W> screen);

template<unsigned H, unsigned W>
istream &operator>>(istream &is, Screen<H, W> screen);

template<unsigned H, unsigned W>
class Screen {
  friend ostream &operator<<
    <H, W>(ostream &, Screen<H, W>);

  friend istream &operator>>
    <H, W>(istream &, Screen<H, W>);

  public:
  Screen(unsigned h = H, unsigned w = W) : height(h), width(w) {}

  private:
  unsigned height;
  unsigned width;
};

template<unsigned H, unsigned W>
ostream &operator<<(ostream &os, Screen<H, W> screen) {
  os << "height: " << screen.height << " weight: " << screen.width;
  return os;
};

template<unsigned H, unsigned W>
istream &operator>>(istream &is, Screen<H, W> screen) {
  is >> screen.height >> screen.width;
  return is;
};
```

**Exercise 16.15:** Implement input and output operators for your Screen template.Which, if any, friends are necessary in class Screen to make the input and outputoperators work? Explain why each friend declaration, if any, was needed.

```c++
// 见上题
// 需要将输入和输出重载运算符作为友元，因为输入输出通常都会访问对象的内部状态，所以需要设置为友元
```

**Exercise 16.16:** Rewrite the StrVec class (§ 13.5, p. 526) as a template named Vec.

**Exercise 16.17:** What, if any, are the differences between a type parameter that is de-clared as a typename and one that is declared as a class? When must typename beused?

```c++
// 没有不同；
// 在需要使用模板实参中的类型成员时，需要使用typename显式的告知编译器，这是一个类型，这个时候只能使用typename
```

**Exercise 16.18:** Explain each of the following function template declarations and iden-tify whether any are illegal. Correct each error that you find.

```c++
(a) template <typename T, U, typename V> void f1(T, U, V); 
(b) template <typename T> T f2(int &T);
(c) inline template <typename T> T foo(T, unsigned int*); 
(d) template <typename T> f4(T, T);
(e) typedef char Ctype;
	template <typename Ctype> Ctype f5(Ctype a);

---
(a) template <typename T, typename U, typename V> void f1(T, U, V);
(b) template <typename T> T f2(int &);
(c) template <typename T> inline T foo(T, unsigned int*); 
(d) template <typename T> void f4(T, T);
(e)	typedef char Ctype;
	template <typename Ctype> Ctype f5(Ctype a);  // right, but ambiguous for human
```

**Exercise 16.19:** Write a function that takes a reference to a container and prints the elements in that container. Use the container’s size_type and size members to control the loop that prints the elements.

```c++
template<typename T>
void print(const T &t) {
    typename T::size_type s = 0, size = t.size();
    while (s != size) {
        cout << t[s] << endl;
        ++s;
    }
}
// 实现依赖下标操作
```

**Exercise 16.20:** Rewrite the function from the previous exercise to use iterators re-turned from begin and end to control the loop.

```c++
template<typename T>
void print2(T &t) {
    auto it = t.begin();
    while (it != t.end()) {
        cout << *it++ << endl;
    }
}
// 仅使用迭代器接口
```

**Exercise 16.21:** Write your own version of DebugDelete.

```c++
class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}

    template<typename T>
    void operator()(T *p) const {
        os << "deleting unique_ptr" << std::endl;
        delete p;
    }

private:
    std::ostream &os;
};
```

**Exercise 16.22:** Revise your TextQuery programs from § 12.3 (p. 484) so that the shared_ptr members use a DebugDelete as their deleter (§ 12.1.4, p. 468).

**Exercise 16.23:** Predict when the call operator will be executed in your main query program. If your expectations and what happens differ, be sure you understand why.

**Exercise 16.24:** Add a constructor that takes two iterators to your Blob template.

```c++
template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e):data(std::make_shared<DataType>(b, e)) {}
```

**Exercise 16.25:** Explain the meaning of these declarations:

```c++
extern template class vector<string>;
template class vector<Sales_data>;

---
(1) 实例化声明vector<string>，保证定义在其他文件中出现
(2) 实例化定义
```

**Exercise 16.26:** Assuming NoDefault is a class that does not have a default constructor, can we explicitly instantiate `vector<NoDefault>`? If not, why not?

```c++
// 不能；因为显式实例化会实例化类的所有成员；而vector中包含有成员函数要求模板参数定义了默认构造函数，而NoDefault没有定义，导致实例化失败
```

**Exercise 16.27:** For each labeled statement explain what, if any, instantiations happen. If a template is instantiated, explain why; if not, explain why not.

```c++
template <typename T> class Stack { };
void f1(Stack<char>);     				// (a) 出现在函数声明中，不会实例化
class Exercise {
    Stack<double> &rsd;    				// (b) 出现在类定义中，由于是引用不会实例化
    Stack<int>    si; 					// (c) 出现在类定义中，会实例化
};
int main() {
	Stack<char> *sc;					// (d) 指针，不会实例化
	f1(*sc);							// (e) 函数调用，实例化
	int iObj = sizeof(Stack< string >);	// (f) 实例化，sizeof时类型定义必须是可见的，所以会实例化
}

// 模板在使用的时候编译器才会进行实例化
```

**Exercise 16.28:** Write your own versions of shared_ptr and unique_ptr.

```c++
// deleter
class deleter {
  public:
  template<typename T>
  void operator()(T *p) const {
    std::cout << "info from deleter" << std::endl;
    delete p;
  }
};

/****************************************************************
*
        _                        _            _
    ___| |__   __ _ _ __ ___  __| |     _ __ | |_ _ __
   / __| '_ \ / _` | '__/ _ \/ _` |    | '_ \| __| '__|
   \__ \ | | | (_| | | |  __/ (_| |    | |_) | |_| |
   |___/_| |_|\__,_|_|  \___|\__,_|____| .__/ \__|_|
                                 |_____|_|

*
****************************************************************/

template<typename T>
class shared_ptr;

template<typename T>
bool operator==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs);

template<typename T>
class shared_ptr {
  friend bool operator==<T>(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs);

  public:
  shared_ptr() : ptr(nullptr), cnt(nullptr) {}

  shared_ptr(T *p, std::function<void(T *)> d = deleter())
    : ptr(p), del(d), cnt(new std::size_t(1)) {}

  // copy-control
  shared_ptr(const shared_ptr &p)
    : ptr(p.ptr), del(p.del), cnt(p.cnt) {
      ++*cnt;
      debug();
    }

  // copy assignment
  shared_ptr &operator=(const shared_ptr &p);

  // member
  T operator*() const { return *ptr; }

  // arrow
  T *operator->() const { return ptr; }

  operator bool() const { return ptr != nullptr; }

  // reset
  void reset(T *p);

  void reset(T *p, std::function<void(T *)> deleter);

  ~shared_ptr();

  void debug() const {
    if (cnt) {
      std::cout << "ref cnt: " << *cnt << std::endl;
    } else {
      throw std::runtime_error("should not happen");
    }
  }

  private:
  T *ptr;
  std::function<void(T *)> del;
  std::size_t *cnt;
};

template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr &p) {
  ++*p.cnt;
  if (--*cnt == 0) {
    del ? del(ptr) : delete ptr;
    delete cnt;
  }
  ptr = p.ptr;
  del = p.del;
  cnt = p.cnt;
  debug();
  return *this;
}

template<typename T>
void shared_ptr<T>::reset(T *p) {
  if (cnt && --*cnt == 0) {
    del ? del(ptr) : delete ptr;
    delete cnt;
  }
  ptr = p;
  cnt = new std::size_t(1);
}

template<typename T>
void shared_ptr<T>::reset(T *p, std::function<void(T *)> deleter) {
  reset(p);
  del = deleter;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
  if (--*cnt == 0) {
    del ? del(ptr) : delete ptr;
    delete cnt;
  }
}

// == and != operator
template<typename T>
bool operator==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
  return lhs.ptr == rhs.ptr;
}

template<typename T>
bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
  return !(lhs == rhs);
}

// helper function, simulate std::make_shared()
template<typename T>
shared_ptr<T> make_shared() {
  shared_ptr<T> s(new T);
  return s;
}

/****************************************************************
*
               _                             _
   _   _ _ __ (_) __ _ _   _  ___      _ __ | |_ _ __
  | | | | '_ \| |/ _` | | | |/ _ \    | '_ \| __| '__|
  | |_| | | | | | (_| | |_| |  __/    | |_) | |_| |
   \__,_|_| |_|_|\__, |\__,_|\___|____| .__/ \__|_|
                    |_|         |_____|_|

*
****************************************************************/
template<typename T, typename D = deleter>
class unique_ptr {
public:
unique_ptr(T *p = nullptr, D d = deleter()) : ptr(p), del(d) {}

~unique_ptr() { del(ptr); }

// move ctor
unique_ptr(unique_ptr &&u) : ptr(u.ptr), del(u.del) { u.ptr = nullptr; }

// move assignment
unique_ptr &operator=(unique_ptr &&u);

T operator*() const { return *ptr; }

T *operator->() const { return ptr; }

void reset(T *p) {
    del(ptr);
    ptr = p;
}

void reset(T *p, D d) {
    reset(p);
    del = d;
}

private:
    T *ptr;
    D del;
};

template<typename T, typename D>
unique_ptr<T, D> &unique_ptr<T, D>::operator=(unique_ptr &&u) {
  if (this != &u) {
    del(ptr);
    ptr = u.ptr;
    del = u.del;

    u.ptr = nullptr;
  }
  return *this;
}
```

**Exercise 16.29:** Revise your Blob class to use your version of shared_ptr rather than the library version.

```c++
// 替换std::shared_ptr 为 exercise::shared_ptr
// 替换std::make_shared为 exercise::make_shared
```

**Exercise 16.30:** Rerun some of your programs to verify your shared_ptr and re-vised Blob classes. (Note: Implementing the weak_ptr type is beyond the scope ofthis Primer, so you will not be able to use the BlobPtr class with your revised Blob.)

```c++
// 暂时注释掉接受列表初始化式和迭代器的构造函数，以及begin() end()，正如题目所说，weak_ptr未实现
```

**Exercise 16.31:** Explain how the compiler might inline the call to the deleter if we used DebugDelete with unique_ptr.

```c++
// 编译器将删除器处理为内联形式?
// 因为删除器重载了调用运算符，并且在类的定义中实现，默认是inline的，编译器可能在调用点将其展开
```

**Exercise 16.32:** What happens during template argument deduction?

```c++
// 在模板实参推断过程中，编译器使用函数调用中的实参类型来寻找模板实参，用这些模板实参生成的函数版本与给定的函数调用最为匹配。
```

**Exercise 16.33:** Name two type conversions allowed on function arguments involved in template argument deduction.

```c++
// 1. const转换，顶层const被忽略，非const引用或指针可以自动转换为const引用或指针
// 2. 模板实参非引用类型时，数组或函数自动转换为指针
```

**Exercise 16.34:** Given only the following code, explain whether each of these calls is legal. If so, what is the type of T? If not, why not?		

```c++
template <class T> int compare(const T&, const T&);
(a) compare("hi", "world"); 
(b) compare("bye", "dad");

---
(a) illegal, 因为是引用类型，数组的长度不一样，推断出的类型不匹配
(b) legal, const char (&)[]
```

**Exercise 16.35:** Which, if any, of the following calls are errors? If the call is legal, what is the type of T? If the call is not legal, what is the problem?

```c++
template <typename T> T calc(T, int); 
template <typename T> T fcn(T, T); 

double d; float f; char c;

(a) calc(c, ’c’); 
(b) calc(d, f);
(c) fcn(c, ’c’); 
(d) fcn(d, f);

---
(a) T: char
(b) T: float
(c) T: char
(d) illegal，类型不匹配，不会进行类型转换
```

**Exercise 16.36:** What happens in the following calls:

```c++
template <typename T> f1(T, T);
template <typename T1, typename T2) f2(T1, T2); 

int i = 0, j = 42, *p1 = &i, *p2 = &j;
const int *cp1 = &i, *cp2 = &j;

(a) f1(p1, p2); 
(b) f2(p1, p2);
(c) f1(cp1, cp2); 
(d) f2(cp1, cp2); 
(e) f1(p1, cp1); 
(f) f2(p1, cp1);

---
(a) T: int
(b) T1: int, T2: int 
(c) T: const int*
(d) T1: const int *, T2: const int *
(e) illegal: error: no matching function for call to 'ff1(int*&, const int*&)'
(f) T1: int*, T2: const int*
```

**Exercise 16.37:** The library max function has two function parameters and returns thelarger of its arguments. This function has one template type parameter. Could you callmax passing it an int and a double? If so, how? If not, why not?

```c++
// 不能直接调用，error: no matching function for call to 'max(int&, double&)'
// 需要显式的制定模板参数

std::max<double>(i_int, d_double) 
```

**Exercise 16.38:** When we call make_shared (§ 12.1.1, p. 451), we have to provide an explicit template argument. Explain why that argument is needed and how it is used.

```c++
// make_shared需要根据制定的类型参数在堆上分配对象，因为函数没有参数，所以必须给出模板参数
```

**Exercise 16.39:** Use an explicit template argument to make it sensible to pass twostring literals to the original version of compare from § 16.1.1 (p. 652).

```c++
template<typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) { return -1; }
    if (v2 < v1) { return 1; }
    return 0;
}

template<>
int compare(const char *const &v1, const char *const &v2) {
    return strcmp(v1, v2);
}

cout << compare("hello", "world") << endl;
cout << compare<const char *>("world", "hello") << endl;

// 上面个两个调用的情况不一样
// 1: 由于没有指定模板实参，编译器推断出T为 char (&)[5] (如果两个字符串字面量长度不同，实例化会出错)
// 2: 显式指定模板类型参数，使用特化版本，字符数组自动转为指针，两个字符串长度不同也不会有问题
```

**Exercise 16.40:** Is the following function legal? If not, why not? If it is legal, what, if any, are the restrictions on the argument type(s) that can be passed, and what is the return type?

```c++
template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0) {
	// process the range
	return *beg; // return a copy of an element from the range 
}

---
// 合法的
// 需要迭代器指向的类型定义了和数值类型的重载+操作符，返回类型时重载的（或内件的）+可能经过类型转换的结果
```

**Exercise 16.41:** Write a version of sum with a return type that is guaranteed to be large enough to hold the result of the addition.

```c++
template<typename T>
auto sum(T lhs, T rhs) -> typename make_unsigned<decltype(lhs + rhs)>::type {
    return lhs + rhs;
}

// 这个函数限制较大，只能处理有符号数的加法上溢，不能处理下溢，也不能处理无符号数
```

**Exercise 16.42:** Determine the type of T and of val in each of the following calls:

```c++
template <typename T> void g(T&& val);
int i = 0; const int ci = i;
(a) g(i); (b) g(ci); (c) g(i * ci);

---
(a) val: int; T: int &
(b) val: const int; T: const int &
(c) val: int; T: int
```

**Exercise 16.43:** Using the function defined in the previous exercise, what would the template parameter of g be if we called g(i = ci)?

```c++
// i = ci; 返回的是左值，普通引用; T: int &
```

**Exercise 16.44:** Using the same three calls as in the first exercise, determine the typesfor T if g’s function parameter is declared as T (not T&&). What if g’s function parame-ter is const T&?

```c++
template <typename T> void g(T val);
int i = 0; const int ci = i;
(a) g(i); (b) g(ci); (c) g(i * ci);

---
(a) int
(b) const ci
(c) int
  

template <typename T> void g(T& val);
int i = 0; const int ci = i;
(a) g(i); (b) g(ci); (c) g(i * ci);

---
(a) int
(b) const int
(c) illegal
```

**Exercise 16.45:** Given the following template, explain what happens if we call g on aliteral value such as 42. What if we call g on a variable of type int?

```c++
template <typename T> void g(T&& val) { vector<T> v; }

---
// (1) 42：T将推断为int类型，函数体重定义了一个自动变量的vector<int>
// (2) int：T将推断为int&，引用不能作为容器的元素，实例化错误
```

**Exercise 16.46:** Explain this loop from StrVec::reallocate in § 13.5 (p. 530):

```c++
for (size_t i = 0; i != size(); ++i) 
  alloc.construct(dest++, std::move(*elem++));

---
// *elem++； 返回的是左值引用，经过std::move转换为右值引用
// 然后construct函数使用元素的移动构造函数构造新的元素
```

**Exercise 16.47:** Write your own version of the flip function and test it by calling functions that have lvalue and rvalue reference parameters.

```c++
template<typename F, typename T1, typename T2>
void flip3(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::fo
    rward<T1>(t1));
};

// 使用std::move，将右值引用绑定到左值上
// 使用std::forward，返回右值引用类型，看起来特别适合做实参的转发
```

**Exercise 16.48:** Write your own versions of the debug_rep functions.

```c++
// l-value or const r-value
template<typename T>
string debug_rep(const T &t) {
ostringstream ret;
ret << t;
return ret.str();
}

// overloaded version
template<typename T>
string debug_rep(T *p) {
ostringstream ret;
ret << "pointer: " << p;
if (p) {
ret << " value: " << debug_rep(*p);
} else {
ret << " null pointer";
}
return ret.str();
}

string debug_rep(const string &s) {
return '"' + s + '"';
}

// plain overloaded function for char *
string debug_rep(char *p) {
return debug_rep(string(p));
}

// plain overloaded function for const char *
string debug_rep(const char *p) {
return debug_rep(string(p));
}
```

**Exercise 16.49:** Explain what happens in each of the following calls:

```c++
template <typename T> void f(T); 
template <typename T> void f(const T*); 
template <typename T> void g(T); 
template <typename T> void g(T*);

int i = 42, *p = &i;
const int ci = 0, *p2 = &ci;

g(42); g(p); g(ci); g(p2); f(42); f(p); f(ci); f(p2);

---
g(42): g(T),  T->int
g(p) : g(T*), T->int
g(ci): g(T),  T->int
g(p2): g(T*), T->const int

f(42): f(T),  T->int
f(p) : f(const T*), T->int   //应该是 f(T), T-> int*, 不需要指针的const转换，所以选第一个 ！
f(ci): f(T), T->const int
f(p2): f(const T*), T->int
```

**Exercise 16.50:** Define the functions from the previous exercise so that they print an identifying message. Run the code from that exercise. If the calls behave differently from what you expected, make sure you understand why.

```c++
f(p) : f(T), T->int*   // 不需要指针的const转换，所以选这个
```

**Exercise 16.51:** Determine what sizeof...(Args) and sizeof...(rest) returnfor each call to foo in this section.

```c++
// 3 3
// 2 2
// 1 1
// 0 0
```

**Exercise 16.52:** Write a program to check your answer to the previous question.				

**Exercise 16.53:** Write your own version of the print functions and test them by print-ing one, two, and five arguments, each of which should have different types.

```c++
template<typename T>
ostream &print(ostream &os, const T &t) {
  os << t;
  return os;
}

template<typename T, typename... Args>
    ostream &print(ostream &os, const T &t, const Args &... rest) {
        os << t;
        return print(os, rest...);
    };
```

**Exercise 16.54:** What happens if we call print on a type that doesn’t have an <<operator?

```c++
// 编译报错，无法实例化
```

**Exercise 16.55:** Explain how the variadic version of print would execute if we de-clared the nonvariadic version of print after the definition of the variadic version.

```c++
// 编译错误，模板在实例化时，发现没有定义
// error: no matching function for call to 'print(std::ostream&)'的版本

// 作者说：当定义可变参数版本的print时，非可变参数版本的声明必须在作用域中，否则，可变参数版本会无限递归。
// gcc 7.2.0中，在编译时会报错
```

**Exercise 16.56:** Write and test a variadic version of errorMsg.

```c++
template<typename... Args>
    ostream &errorMsg(ostream &os, const Args &... args) {
        return print(os, debug_rep(args)...);
    }
```

**Exercise 16.57:** Compare your variadic version of errorMsg to the error_msg func-tion in § 6.2.6 (p. 220). What are the advantages and disadvantages of each approach?

```c++
// error_msg接受initializer_list作为参数，优点实现简单，缺点要求参数类型一致
// errMsg是函数模板，优点是允许参数类型不一致，缺点是实现复杂
```

**Exercise 16.58:** Write the emplace_back function for your StrVec class and for the Vec class that you wrote for the exercises in § 16.1.2 (p. 668).

```c++
template<typename T>
template<typename ... Args>
void Vec<T>::emplace_back(Args &&...args) {
    check_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}
```

**Exercise 16.59:** Assuming s is a string, explain `svec.emplace_back(s)`.

```c++
// s是string，意味着s是左值
// 当svec.emplace_back(s)发生时，emplace_back推断出的模板实参为string&
// 然后将参数传递给constrct，construct函数继续将string&类型的参数传递给string的拷贝构造函数
// 构造出s的一个副本
```

**Exercise 16.60:** Explain how make_shared (§ 12.1.1, p. 451) works.

```c++
// make_shared是个可变参数模板函数
// 第一个是其内部要保存的指针的类型；
// 第二个参数可变，会传递给第一个类型参数的构造函数
```

**Exercise 16.61:** Define your own version of make_shared.

```c++
// helper function, simulate std::make_shared()
template<typename T, typename ... Args>
shared_ptr<T> make_shared(Args &&... args) {
    shared_ptr<T> s(new T(std::forward<Args>(args)...));
    return s;
}
```

**Exercise 16.62:** Define your own version of `hash<Sales_data>` and define an unordered_multiset of Sales_data objects. Put several transactions into the container and print its contents.

```c++
// Sales_data.h
namespace std {
    template<>
    struct hash<Sales_data> {
        typedef std::size_t result_type;
        typedef Sales_data argument_type;

        std::size_t operator()(const Sales_data &s) const;
    };
}

// Sales_data.cc
namespace std {
    std::size_t hash<Sales_data>::operator()(const Sales_data &s) const {
        return hash<string>()(s.bookNo) ^
               hash<unsigned>()(s.units_sold) ^
               hash<double>()(s.revenue);
    }
}
```

**Exercise 16.63:** Define a function template to count the number of occurrences of agiven value in a vector. Test your program by passing it a vector of doubles, avector of ints, and a vector of strings.

```c++
template<typename T>
std::size_t count(const std::vector<T> &c, T v) {
  std::size_t cnt = 0;
  for (auto it = c.begin(); it != c.end(); ++it) {
    if (*it == v) {
      ++cnt;
    }
  }
  return cnt;
}
```

**Exercise 16.64:** Write a specialized version of the template from the previous exerciseto handle `vector<const char*>` and a program that uses this specialization.

```c++
template<>
std::size_t count(const std::vector<const char *> &c, const char *v) {
    std::size_t cnt = 0;
    for (auto it = c.begin(); it != c.end(); ++it) {
        if (strcmp(*it, v) == 0) {
            ++cnt;
        }
    }
    return cnt;
}
```

**Exercise 16.65:** In § 16.3 (p. 698) we defined overloaded two versions of debug_repone had a const char* and the other a char* parameter. Rewrite these functions as specializations.

```c++
 template<>
string debug_rep(char *p) {
    return debug_rep(string(p));
}

template<>
string debug_rep(const char *p) {
    return debug_rep(string(p));
}
```

**Exercise 16.66:** What are the advantages and disadvantages of overloading these debug_rep functions as compared to defining specializations?

```c++
// 缺点：重载会改变函数匹配，特例化不会改变函数匹配
// 优点：优先级高，不会出现在多个文件中存在相同实例的问题
```

**Exercise 16.67:** Would defining these specializations affect function matching fordebug_rep? If so, how? If not, why not?

```c++
// 不会；特例化只是给出模板某一个实例化的实现，接管了编译器的部分工作。
```

### Notes

- 面向对象编程（OOP）和泛型编程都能处理在编写程序时不知道类型的情况。不同之处在于：OOP能处理类型在程序运行之前都未知的情况：<u>而在泛型编程中，在编译时就能获知类型了</u>。**模板是泛型编程的基础**。
- 在模板定义中，模板参数列表不能为空。模板参数（template parameter）表示在类或函数定义中用到的<u>类型或值</u>。使用模板时，我们（隐式地或显式地）指定**模板实参**（template argument），将其绑定到模板参数上。
- 编译器使用推断出的模板参数来**实例化（instantiate）**一个特定版本的函数，这些编译器生成的版本通常被称为**模板的实例（instantiation）**。
- 模板定义中可以<u>使用类型参数（type parameter）或非类型参数(nontype parameter)</u>。一个非类型参数表示一个值而非一个类型，使用**特定的类型名**而非关键字class或typename来指定非类型参数。当一个模板被实例化时，非类型参数被一个用户提供的或编译器推断出的值所代替。这些值必须是**常量表达式**，从而允许编译器在编译时实例化模板。（关键的地方是模板是**编译期实例化的**，必须提供常量表达式）
- 一个非类型参数可以是一个整数，或者是一个指向对象或函数类型的指针或（左值）引用。绑定到非类型整数参数的实参必须是一个**常量表达式**。<u>绑定到指针或引用非类型参数的实参必须具有静态的生存期。不能用一个普通（非static）局部变量或动态对象作为指针或引用非类型模板参数的实参</u>。指针参数也可以用nullptr或一个值为0的常量表达式来实例化。
- 编译器遇到一个模板定义时，并不生成代码。只有当实例化出模板的一个特定版本时，编译器才会生成代码，这一特性影响了代码的组织以及错误何时被检测到。
- 为了生成一个实例化版本，编译器需要掌握函数模板和类模板成员函数的定义。因此，**函数模板和类模板成员函数的定义通常放在头文件中**。
- 大多数编译错误在实例化期间报告
- 类模板是用来生成类的蓝图。与函数模板不同，编译器不能为类模板推断模板参数类型。
- 在使用类模板时，必须提供显式模板实参（explicit template argument）列表，它们被绑定到模板参数。**一个类模板的每个实例都形成一个独立的类**。*<u>类模板的名字不是一个类型，类模板用来实例化类型，而一个实例化的类型总是包含模板参数的</u>*。
- 类模板成员函数的实例化：默认情况下，**一个类模板的成员函数只有当程序用到它时才进行实例化**。如果一个成员函数没有被使用，则它不会被实例化。*这一特性使得某些类型不能完全符合模板操作的要求，仍然能用该类型实例化类*。
- **在使用一个类模板类型时必须提供模板参数**，但有一个例外，当在类模板自己的作用域中时，可以直接使用模板名而不提供实参。
- 当一个类包含一个友元声明时，类有友元各自是否是模板是**相互无关**的。如果一个类模板包含一个非模板友元，则友元被授权可以访问所有模板实例。**如果友元自身是模板，类可以授权给所有友元模板的实例，也可以只授权给特定实例**。


- 模板参数遵循普通的作用域规则，但是参数名不能重用，所以一个模板参数名在一个特定模板参数列表中**只能出现一次**。

- **当希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能使用class**。

- 一个类（无论是普通类还是模板类）可以包含本身是模板的成员函数。这种成员被称为**成员模板（member  template）**。成员模板不能是虚函数。

- 当模板被使用时才会进行实例化，这一特性意味着，相同的实例可能出现在多个对象文件中。**当两个或多个独立编译的源文件使用了相同的模板，并提供了相同的模板参数时，每个文件中就都会有该模板的一个实例**。

- *实例化定义会实例化所有成员，因此在一个类模板的实例化定义中，所用类型必须能用于模板的所有成员*。

- 对于函数模板，编译器利用调用中的函数参数来确定其模板参数，从**函数实参来确定模板实参**的过程被称为**模板实参推断**（template argument deduction）。编译器使用函数调用中的实参类型来寻找模板实参，用这些模板实参生成的函数版本与给定的函数调用最为匹配。

- **将实参传递给带模板类型的函数形参时，能够自动应用的类型转换只有const转及数组或函数到指针的转换**。

  - 与往常一样，*顶层const无论是在形参中还是在实参中，都会被忽略*。在其他类型转换中，能在调用中应用于函数模板的包括如下两项：

    1. **const转换**：可以将一个非const对象的引用（或指针）传递给一个const引用（或指针）形参。
    2. **数组或函数指针转换**：*如果函数形参**不是引用类型**，则可以对数组或函数类型的实参应用正常的指针转换*。一个数组实参可以转换为一个指向其首元素的指针。类似的，一个函数实参可以转换为一个该函数类型的指针。(<u>这里必须要注意的是要求形参不是引用类型</u>)

    ```c++
    template <typename T> T fobj(T,T);
    template <typename T> T fref(const T&, const T&);

    string s1("a value");
    const string s2("another value");

    fobj(s1,s2); // fobj(string,string); const is ignored
    fref(s1,s2); // fref(const string&, const string&); s1 conver to const is allowed

    int a[10],b[42];
    fobj(a,b);   // fobj(int *, int *)
    fref(a,b);   // error: array type is not match
    ```


- 如果函数参数类型不是模板参数，则对实参进行正常的类型转换。
- **当用一个函数模板初始化一个函数指针或为一个函数指针赋值时，编译器使用指针的类型来推断模板实参**。当参数是一个函数模板实例的地址时，程序上下文必须满足：对每个模板参数，能唯一确定其类型或值。
- **引用折叠只能应用于间接创建的引用的引用，如类型别名或模板参数**。
- 引用折叠规则和右值引用的特殊类型推断规则，导致了两个重要结果：
  - 如果一个函数参数是一个指向模板类型参数的右值引用（如，T&&），则它可以被绑定到一个左值，且
  - 如果实参是一个左值，则推断出的模板实参类型将是一个左值引用，且函数参数将被实例化为一个（普通）左值引用参数（T&）.
  - ——这两个规则暗示：可以将任意类型的实参传递给T&&类型的函数参数。


- 如果一个函数参数是指向模板参数的右值引用（T&&），则可以传递给它任意类型的实参。如果将一个左值传递给这样的参数，则函数实参被实例化为一个普通的左值引用（T&）；显然也可以传递给它右值。

- 右值引用通常用于两种情况：**模板转发实参**或**模板被重载**。使用右值引用的函数模板使用通常的方式进行重载：

  - ```c++
    template <typename T> void f(T&&);      // 绑定到非const右值
    template <typename T> void f(const T&); // 左值和const右值
    ```


- 从一个左值static_cast到一个右值引用是允许的：通常情况下，static_case只能用于其他合法的类型转换。但是，这里又有一条针对右值引用的特许规则：**虽然不能隐式地将一个左值转换为右值引用，但是可以使用static_cast显式地将一个左值转换为一个右值引用**。对于操作右值引用的代码来说，讲一个右值绑定到一个左值的特性允许它们截断左值。虽然可以直接编写这种类型转换，但使用标准库move函数是容易的方式，而且统一使用std::move使得在程序中查找潜在的截断左值的代码变得容易。


- forward<T>的返回类型时T&&。通常情况下，使用forward传递那些定义为模板类型参数的右值引用的函数参数。相当于加上了&&：

- ```c++
  T: T&&
  T&: T& && -> T&
  T&&: T&& && -> T&&
  ```


- **当用于一个指向模板参数类型的右值引用函数参数(T&&)时，forward会保持实参类型的所有细节**。


- **当有多个重载模板对一个调用提供同样好的匹配时，应选择最特例化的版本**。
- **对于一个调用，如果一个非函数模板于一个函数模板提供同样好的匹配，则选择非模板版本**。


- 一个可**变参数模板（variadic template）**就是一个接受可变数目参数的模板函数或模板类。可变数目的参数被称为**参数包（parameter package）**。存在两种参数包**：模板参数包，**表示零个或多个模板参数；**函数参数包**，表示零个或多个函数参数。


- 对于一个参数包，除了获取其大小外，我们能对它做的唯一的事情就是**扩展（expand）它**。当扩展一个包时，还要提供用于每个扩展元素的**模式（pattern）**。**扩展一个包就是将它分解为构成的元素，对每个元素应用模式，获得扩展后的列表**。
- **扩展中的模式会独立的应用于包中的每个元素**。


- 特例化本质是实例化一个模板，而非重载它。因此，特例化不影响函数匹配。当定义函数模板的特例化版本时，本质上<u>接管了编译器的工作</u>，即**为原模板的一个特殊实例提供了定义**。


- 与函数模板不同，类模板的特例化不必为所有模板参数提供实参。可以只指定**一部分而非所有模板参数，或是参数的一部分而非全部特性**。一个类模板的**部分特例化（partial specialization）**本身是一个模板，*使用时还必须为那些在特例化版本中未指定的模板参数提供实参*。