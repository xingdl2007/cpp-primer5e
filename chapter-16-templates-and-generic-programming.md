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

**Exercise 16.18:** Explain each of the following function template declarations and iden-tify whether any are illegal. Correct each error that you find.

```c++
(a) template <typename T, U, typename V> void f1(T, U, V); 
(b) template <typename T> T f2(int &T);
(c) inline template <typename T> T foo(T, unsigned int*); 
(d) template <typename T> f4(T, T);
(e) typedef char Ctype;
	template <typename Ctype> Ctype f5(Ctype a);
```

**Exercise 16.19:** Write a function that takes a reference to a container and prints theelements in that container. Use the container’s size_type and size members tocontrol the loop that prints the elements.

**Exercise 16.20:** Rewrite the function from the previous exercise to use iterators re-turned from begin and end to control the loop.

**Exercise 16.21:** Write your own version of DebugDelete.

**Exercise 16.22:** Revise your TextQuery programs from § 12.3 (p. 484) so that the shared_ptr members use a DebugDelete as their deleter (§ 12.1.4, p. 468).

**Exercise 16.23:** Predict when the call operator will be executed in your main query program. If your expectations and what happens differ, be sure you understand why.

**Exercise 16.24:** Add a constructor that takes two iterators to your Blob template.

**Exercise 16.25:** Explain the meaning of these declarations:

```c++
extern template class vector<string>;
template class vector<Sales_data>;
```


**Exercise 16.26:** Assuming NoDefault is a class that does not have a default constructor, can we explicitly instantiate `vector<NoDefault>`? If not, why not?

**Exercise 16.27:** For each labeled statement explain what, if any, instantiations happen. If a template is instantiated, explain why; if not, explain why not.

```c++
template <typename T> class Stack { };
void f1(Stack<char>);     				// (a)
class Exercise {
    Stack<double> &rsd;    				// (b)
    Stack<int>    si; 					// (c)
};
int main() {
	Stack<char> *sc;					// (d)
	f1(*sc);							// (e)
	int iObj = sizeof(Stack< string >);	// (f)
}
```

**Exercise 16.28:** Write your own versions of shared_ptr and unique_ptr.Exercise 16.29: Revise your Blob class to use your version of shared_ptr rather

than the library version.

**Exercise 16.30:** Rerun some of your programs to verify your shared_ptr and re-vised Blob classes. (Note: Implementing the weak_ptr type is beyond the scope ofthis Primer, so you will not be able to use the BlobPtr class with your revised Blob.)

**Exercise 16.31:** Explain how the compiler might inline the call to the deleter if we usedDebugDelete with unique_ptr.

**Exercise 16.32:** What happens during template argument deduction?

**Exercise 16.33:** Name two type conversions allowed on function arguments involved in template argument deduction.

**Exercise 16.34:** Given only the following code, explain whether each of these calls is legal. If so, what is the type of T? If not, why not?		

```c++
template <class T> int compare(const T&, const T&);
(a) compare("hi", "world"); 
(b) compare("bye", "dad");	
```

**Exercise 16.35:** Which, if any, of the following calls are errors? If the call is legal, what is the type of T? If the call is not legal, what is the problem?

```c++
template <typename T> T calc(T, int); 
template <typename T> T fcn(T, T); 
double d; float f; char c;
(a) calc(c, ’c’); (b) calc(d, f);
(c) fcn(c, ’c’); (d) fcn(d, f);
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
```


**Exercise 16.37:** The library max function has two function parameters and returns thelarger of its arguments. This function has one template type parameter. Could you callmax passing it an int and a double? If so, how? If not, why not?

**Exercise 16.38:** When we call make_shared (§ 12.1.1, p. 451), we have to provide anexplicit template argument. Explain why that argument is needed and how it is used.

**Exercise 16.39:** Use an explicit template argument to make it sensible to pass twostring literals to the original version of compare from § 16.1.1 (p. 652).

**Exercise 16.40:** Is the following function legal? If not, why not? If it is legal, what, if any, are the restrictions on the argument type(s) that can be passed, and what is the return type?

```c++
template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0) {
	// process the range
	return *beg; // return a copy of an element from the range 
}
```

**Exercise 16.41:** Write a version of sum with a return type that is guaranteed to be large enough to hold the result of the addition.

**Exercise 16.42:** Determine the type of T and of val in each of the following calls:

```c++
template <typename T> void g(T&& val);
int i = 0; const int ci = i;
(a) g(i); (b) g(ci); (c) g(i * ci);
```


**Exercise 16.43:** Using the function defined in the previous exercise, what would thetemplate parameter of g be if we called g(i = ci)?

**Exercise 16.44:** Using the same three calls as in the first exercise, determine the typesfor T if g’s function parameter is declared as T (not T&&). What if g’s function parame-ter is const T&?

**Exercise 16.45:** Given the following template, explain what happens if we call g on aliteral value such as 42. What if we call g on a variable of type int?

```c++
template <typename T> void g(T&& val) { vector<T> v; }
```

**Exercise 16.46:** Explain this loop from StrVec::reallocate in § 13.5 (p. 530):

```c++
for (size_t i = 0; i != size(); ++i) 
  alloc.construct(dest++, std::move(*elem++));
```


**Exercise 16.47:** Write your own version of the flip function and test it by calling functions that have lvalue and rvalue reference parameters.

**Exercise 16.48:** Write your own versions of the debug_rep functions.

**Exercise 16.49:** Explain what happens in each of the following calls:

```c++
template <typename T> void f(T); 
template <typename T> void f(const T*); 
template <typename T> void g(T); 
template <typename T> void g(T*);
int i = 42, *p = &i;
const int ci = 0, *p2 = &ci;
g(42); g(p); g(ci); g(p2); f(42); f(p); f(ci); f(p2);
```


**Exercise 16.50:** Define the functions from the previous exercise so that they print an identifying message. Run the code from that exercise. If the calls behave differently from what you expected, make sure you understand why.


**Exercise 16.51:** Determine what sizeof...(Args) and sizeof...(rest) returnfor each call to foo in this section.

**Exercise 16.52:** Write a program to check your answer to the previous question.				

**Exercise 16.53:** Write your own version of the print functions and test them by print-ing one, two, and five arguments, each of which should have different types.

**Exercise 16.54:** What happens if we call print on a type that doesn’t have an <<operator?

**Exercise 16.55:** Explain how the variadic version of print would execute if we de-clared the nonvariadic version of print after the definition of the variadic version.

**Exercise 16.56:** Write and test a variadic version of errorMsg.

**Exercise 16.57:** Compare your variadic version of errorMsg to the error_msg func-tion in § 6.2.6 (p. 220). What are the advantages and disadvantages of each approach?

**Exercise 16.58:** Write the emplace_back function for your StrVec class and for theVec class that you wrote for the exercises in § 16.1.2 (p. 668).

**Exercise 16.59:** Assuming s is a string, explain svec.emplace_back(s).

**Exercise 16.60:** Explain how make_shared (§ 12.1.1, p. 451) works.

**Exercise 16.61:** Define your own version of make_shared.

**Exercise 16.62:** Define your own version of `hash<Sales_data>` and define an unordered_multiset of Sales_data objects. Put several transactions into the container and print its contents.

**Exercise 16.63:** Define a function template to count the number of occurrences of agiven value in a vector. Test your program by passing it a vector of doubles, avector of ints, and a vector of strings.

**Exercise 16.64:** Write a specialized version of the template from the previous exerciseto handle `vector<const char*>` and a program that uses this specialization.

**Exercise 16.65:** In § 16.3 (p. 698) we defined overloaded two versions of debug_repone had a const char* and the other a char* parameter. Rewrite these functions asspecializations.

**Exercise 16.66:** What are the advantages and disadvantages of overloading thesedebug_rep functions as compared to defining specializations?

**Exercise 16.67:** Would defining these specializations affect function matching fordebug_rep? If so, how? If not, why not?

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