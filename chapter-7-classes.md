# Chapter 7 Classes

**Exercise 7.1:** Write a version of the transaction-processing program from § 1.6 (p. 24) using the Sales_data class you defined for the exercises in § 2.6.1 (p. 72).

**Exercise 7.2:** Add the combine and isbn members to the Sales_data class youwrote for the exercises in § 2.6.2 (p. 76).

**Exercise 7.3:** Revise your transaction-processing program from § 7.1.1 (p. 256) to usethese members.

**Exercise 7.4:** Write a class named Person that represents the name and address ofa person. Use a string to hold each of these elements. Subsequent exercises will incrementally add features to this class.

```c++
#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

class Person {
public:
    Person() = default;

private:
    std::string name_, addr_;
};

#endif
```

**Exercise 7.5:** Provide operations in your Person class to return the name and address. Should these functions be const? Explain your choice.

```c++
std::string name() const { return name_; }
std::string addr() const { return addr_; }

// 这些函数应该是const的，因为并未有改变成员的动作
```

**Exercise 7.6:** Define your own versions of the add, read, and print functions.Exercise 7.7: Rewrite the transaction-processing program you wrote for the exercises in § 7.1.2 (p. 260) to use these new functions.

**Exercise 7.8:** Why does read define its Sales_data parameter as a plain reference and print define its parameter as a reference to const?

**Exercise 7.9:** Add operations to read and print Person objects to the code you wrote for the exercises in § 7.1.2 (p. 260).

```c++
std::istream &read(std::istream &is, Person &person) {
    is >> person.name_ >> person.addr_;
    return is;
}

std::ostream &print(std::ostream &os, const Person &person) {
    os << person.name_ << " " << person.addr_;
    return os;
}
```

**Exercise 7.10:** What does the condition in the following if statement do?

```c++
if (read(read(cin, data1), data2))

---
// 条件部分的作用是以此读入两个数据分别到data1和data2
```

**Exercise 7.11:** Add constructors to your Sales_data class and write a program touse each of the constructors.

**Exercise 7.12:** Move the definition of the Sales_data constructor that takes anistream into the body of the Sales_data class.

**Exercise 7.13:** Rewrite the program from page 255 to use the istream constructor.

**Exercise 7.14:** Write a version of the default constructor that explicitly initializes the members to the values we have provided as in-class initializers.

**Exercise 7.15:** Add appropriate constructors to your Person class.

```c++
Person(std::string n, std::string a) : name_(n), addr_(a) {}
Person(std::istream &is) { read(is, *this); }
```

**Exercise 7.16:** What, if any, are the constraints on where and how often an access specifier may appear inside a class definition? What kinds of members should be defined after a public specifier? What kinds should be private?

**Exercise 7.17:** What, if any, are the differences between using class or struct ?

**Exercise 7.18:** What is encapsulation? Why is it useful?		

**Exercise 7.19:** Indicate which members of your Person class you would declare as public and which you would declare as private. Explain your choice.

**Exercise 7.20:** When are friends useful? Discuss the pros and cons of using friends.

```c++
// 友元在作为类接口的一部分，而又不是对象的成员函数，但需要访问类的私有成员时，需要设置为对象的友元(为什么把friends翻译为友元？？)
// pros and cons: 好处就是直接访问私有成员；坏处就是相当于开后门，破坏了类的封装。
```

**Exercise 7.21:** Update your Sales_data class to hide its implementation. The pro-grams you’ve written to use Sales_data operations should still continue to work.Recompile those programs with your new class definition to verify that they still work.

**Exercise 7.22:** Update your Person class to hide its implementation.

```c++
friend std::istream &read(std::istream &is, Person &person);
friend std::ostream &print(std::ostream &os, const Person &person);
```

**Exercise 7.23:** Write your own version of the Screen class.

**Exercise 7.24:** Give your Screen class three constructors: a default constructor; a con-structor that takes values for height and width and initializes the contents to hold thegiven number of blanks; and a constructor that takes values for height, width, and acharacter to use as the contents of the screen.

**Exercise 7.25:** Can Screen safely rely on the default versions of copy and assign-ment? If so, why? If not, why not?

**Exercise 7.26:** Define Sales_data::avg_price as an inline function.

**Exercise 7.27:** Add the move, set, and display operations to your version of Screen. Test your class by executing the following code:

```c++
Screen myScreen(5, 5, ’X’); 
myScreen.move(4,0).set(’#’).display(cout); 
cout << "\n";
myScreen.display(cout);
cout << "\n";
```

**Exercise 7.28:** What would happen in the previous exercise if the return type of move,set, and display was Screen rather than Screen&?

```c++
// 如果是Screen，则无法连着使用这些成员函数
```

**Exercise 7.29:** Revise your Screen class so that move, set, and display functionsreturn Screen and check your prediction from the previous exercise.

**Exercise 7.30:** It is legal but redundant to refer to members through the this pointer.Discuss the pros and cons of explicitly using the this pointer to access members.

```c++
// 优点就是清晰明确；缺点就是多余。
```

**Exercise 7.31:** Define a pair of classes X and Y, in which X has a pointer to Y, and Y has an object of type X.

**Exercise 7.32:** Define your own versions of Screen and Window_mgr in which clear is a member of Window_mgr and a friend of Screen.

```c++
// 简单的类可以定义其他类的成员函数作为友元，不过随着类之间的依赖关系的复杂，直接声明其他类为自己的友元会更加简单些
```

**Exercise 7.33:** What would happen if we gave Screen a size member defined as follows? Fix any problems you identify.

```c++
pos Screen::size() const
{
	return height * width;
}

---
// 应该修改为， 应该制定pos是在Screen类中定义的类型
Screen::pos Screen::size() const
{
	return height * width;
}
```

**Exercise 7.34:** What would happen if we put the typedef of pos in the Screen classon page 285 as the last line in the class?

```c++
// 成员函数就无法使用pos类型了
```

**Exercise 7.35:** Explain the following code, indicating which definition of Type or initVal is used for each use of those names. Say how you would fix any errors.

```c++
typedef string Type;
Type initVal();
class Exercise {
   public:
       typedef double Type;
       Type setVal(Type);
       Type initVal();
   private:
       int val;
};
Type Exercise::setVal(Type parm) {
    val = parm + initVal();
	return val; 
}

---
// 使用的是 typedef double Type; initVal是Exercise类中定义的版本。
Exercise::Type Exercise::setVal(Type parm) {
    val = parm + initVal();
	return val; 
}
```

**Exercise 7.36:** The following initializer is in error. Identify and fix the problem.

```c++
struct X {
	X (int i, int j): base(i), rem(base % j) { } 
  	int rem, base;
};

---
// 避免使用类的成员变量初始化其他成员变量；对于这个例子，rem会初始化，而不是base。
struct X {
	X (int i, int j): base(i), rem(i % j) { } 
  	int rem, base;
};
```

**Exercise 7.37:** Using the version of Sales_data from this section, determine which constructor is used to initialize each of the following variables and list the values of the data members in each object:

```c++
Sales_data first_item(cin);
int main() {
    Sales_data next;
    Sales_data last("9-999-99999-9");
}

---
first_item 使用了有一个istream &参数的构造函数
next使用了默认构造函数
last使用了有一个const string&参数的构造函数
```

**Exercise 7.38:** We might want to supply cin as a default argument to the constructorthat takes an istream&. Write the constructor declaration that uses cin as a defaultargument.

```c++
Sales_data(std::istream & = std::cin);
```

**Exercise 7.39:** Would it be legal for both the constructor that takes a string and theone that takes an istream& to have default arguments? If not, why not?'

```c++
// 不合法，因为相当于定义了两个默认构造函数，引起二义性。
```

**Exercise 7.40:** Choose one of the following abstractions (or an abstraction of yourown choosing). Determine what data are needed in the class. Provide an appropriateset of constructors. Explain your decisions.

```c++
(a) Book (b) Date (c) Employee (d) Vehicle (e) Object (f) Tree
```

**Exercise 7.41:** Rewrite your own version of the Sales_data class to use delegatingconstructors. Add a statement to the body of each of the constructors that prints amessage whenever it is executed. Write declarations to construct a Sales_data objectin every way possible. Study the output until you are certain you understand the orderof execution among delegating constructors.

**Exercise 7.42:** For the class you wrote for exercise 7.40 in § 7.5.1 (p. 291), decidewhether any of the constructors might use delegation. If so, write the delegating con-structor(s) for your class. If not, look at the list of abstractions and choose one that youthink would use a delegating constructor. Write the class definition for that abstraction.

**Exercise 7.43:** Assume we have a class named NoDefault that has a constructor thattakes an int, but has no default constructor. Define a class C that has a member oftype NoDefault. Define the default constructor for C.

```c++
class NoDefault {
public:
    explicit NoDefault(int v) { val = v; }

private:
    int val;
};

class C {
public:
    C() : no(100) {}

private:
    NoDefault no;
};
```

**Exercise 7.44:** Is the following declaration legal? If not, why not? 

```c++
vector<NoDefault> vec(10);

---
// 不合法，在上面的调用中，因为没有提供对象初始值，vector构造函数使用NoDefault的构造函数来初始化容器中的元素，但是Nodefault没有定义默认构造函数

// std::vector<NoDefault> ivec(5, NoDefault(1)); 像这样，如果提供了初值就没有问题了。
```

**Exercise 7.45:** What if we defined the vector in the previous execercise to hold objects of type C?

```c++
// 合法。因为类C有默认构造函数
```

**Exercise 7.46:** Which, if any, of the following statements are untrue? Why?

(a) A class must provide at least one constructor.

(b) A default constructor is a constructor with an empty parameter list

(c) If there are no meaningful default values for a class, the class should not provide a default constructor.

(d) If a class does not define a default constructor, the compiler generates one that initializes each data member to the default value of its associated type.

```c++
// (a) 不正确；如果没有提供，编译器会合成默认构造函数
// (b) 不正确；如果构造函数的参数都有默认实参，则等效的定义了默认构造函数
// (c) 不提供默认构造函数会限制类的使用范围；可以使用默认实参的方法，提供默认构造函数
// (d) 不准确。前提是在类没有定义其他的构造函数的情况下
```

**Exercise 7.47:** Explain whether the Sales_data constructor that takes a string should be explicit. What are the benefits of making the constructor explicit? What are the drawbacks?

```c++
// 不应该是explicit的。
// benefits:  好处就是类型转换自动发生，在需要Sales_data的地方，可以提供一个string
// drawbacks: 坏处就是容易用错，体统不合法的string，意外的转换为了Sales_data
```

**Exercise 7.48:** Assuming the Sales_data constructors are not explicit, what op-erations happen during the following definitions; What happens if the Sales_data constructors are explicit?

```c++
string null_isbn("9-999-99999-9");
Sales_data item1(null_isbn);
Sales_data item2("9-999-99999-9");

---
string null_isbn("9-999-99999-9");
Sales_data item1(null_isbn);
// 执行直接初始化，调用有一个const string&为参数构造函数

Sales_data item2("9-999-99999-9");
// 首先,字符串字面值会隐式转换为string，然后调用有一个const string&参数的构造函数

// Sales_data的构造函数是否是explicit的，以上item1和item2的定义都是合法的。
```

**Exercise 7.49:** For each of the three following declarations of combine, explain what happens if we call i.combine(s), where i is a Sales_data and s is a string:

```c++
(a) Sales_data &combine(Sales_data);
(b) Sales_data &combine(Sales_data&);
(c) Sales_data &combine(const Sales_data&) const;

---
(a) s会隐式的转换为Sales_data，生成一个临时变量，通过有一个const string&参数的构造函数，合法
(b) 不合法。隐式转换同a；形参是Sales_data的引用，又因为不允许修改临时变量，调用失败
(c) 不合法。隐式转换同a；形参是const Sales_data引用，可以使用临时变量调用。但又因为该成员函数定义为了const，无法修改当前对象，和函数语义不符。
```

**Exercise 7.50:** Determine whether any of your Person class constructors should be explicit.

```c++
// 不需要
```

**Exercise 7.51:** Why do you think vector defines its single-argument constructor as explicit, but string does not?

```c++
// trade off
// vector：防止意外的隐式类型转换
// string: 方便使用，因为经常需要将const char*类型转换为string
```

**Exercise 7.52:** Using our first version of Sales_data from § 2.6.1 (p. 72), explain the following initialization. Identify and fix any problems.

```c++
Sales_data item = {"978-0590353403", 25, 15.99};

---
// 聚合类通过{}成员初始化列表进行初始化
```

**Exercise 7.53:** Define your own version of Debug.

**Exercise 7.54:** Should the members of Debug that begin with set_ be declared as a constexpr? If not, why not?

**Exercise 7.55:** Is the Data class from § 7.5.5 (p. 298) a literal class? If not, why not? If so, explain why it is literal.

**Exercise 7.56:** What is a static class member? What are the advantages of static members? How do they differ from ordinary members?

```c++
// 类静态成员是和类本真直接相关的，而不是与类的对象相关联的成员。
// 和普通成员不同地方就是静态成员是所有对象共享的类的属性。
```

**Exercise 7.57:** Write your own version of the Account class.

**Exercise 7.58:** Which, if any, of the following static data member declarations and definitions are errors? Explain why.

```c++
// example.h 
class Example { 
  public:
	static double rate = 6.5;
	static const int vecSize = 20; 
	static vector<double> vec(vecSize);
};

// example.C
#include "example.h"
double Example::rate; 
vector<double> Example::vec;

---
// example.h 
class Example {
public:
    static constexpr double rate = 6.5;
    static const int vecSize;
    static std::vector<double> vec;
};

// example.C
#include "example.h"
constexpr double Example::rate;
const int Example::vecSize = 20;
std::vector<double> Example::vec(vecSize);
```

### Notes

- 在C++语言中， 使用类定义自己的数据类型。<u>通过定义新的类型来反映待解决问题中的各种概念</u>。


- 成员函数通过一个名为<u>this</u>的<u>额外的隐式参数</u>来访问调用它的那个对象。
- const成员函数：<u>const的作用是修改隐式this指针的类型。</u>默认情况下this的指针类型是<u>常量指针</u>（也就是说this指针不能在成员函数中被赋值/修改）：`Sales_data *const`，经过成员函数经过const修饰后就变成了`const Sales_data *const`，也就是指向常量对象的常量指针。
- <u>常量对象，以及常量对象的引用和指针都只能调用常量成员函数</u>。
- 类通过一个特殊的构造函数来控制默认初始化过程，这个函数叫做默认构造函数，<u>默认构造函数无须任何参数</u>（没有参数或者包含默认参数，是默认构造函数的<u>充分必要条件</u>）。默认构造函数在很多方面都有其特殊性。其中之一是，<u>如果我们的类没有显式地定义构造函数，那么编译器就会为我们隐式的定义一个默认构造函数</u>。这个合成的默认构造函数按照以下规则初始化类的数据成员：
  - 如果存在类内的初始值，用它来初始化成员。
  - 否则，默认初始化该成员。


- <u>只有当类没有声明任何构造函数时，编译器才会自动地生成默认构造函数</u>。


- `= default`表示要求编译器生成构造函数。其中`= default`既可以和声明一起出现在类的内部，也可以作为定义出现在类的外部。和其他函数一样，如果`= default`出现在类的内部，则默认构造函数是内联的；如果在类的外部，则该成员默认情况下不是内联的。<u>一般情况下，出现`= default`所表达的含义是：我们定义了其他的构造函数，但是还需要默认构造函数，我们希望这个函数的作用完全等同于之前使用的合成默认构造函数</u>。


- 构造函数初值列表：如果成员包含引用，const对象，则这个地方是唯一能够进行初始化的机会。
- 拷贝：初始化变量以及以值的方式传递和返回一个对象时，发生对象拷贝
- 赋值：当使用了赋值运算符时会发生对象的赋值操作
- 析构：当对象不再存在时执行销毁的操作，比如一个局部对象会在创建它的块结束时被销毁，<u>当vector对象（或者数组）销毁时存储在其中的对象也会被销毁</u>


- 尽管编译器能替我们合成拷贝、赋值和销毁的操作，但是必须要清楚的一点是，对于某些类来说合成的版本无法正常工作。<u>特别是，当类需要分配对象之外的资源时，合成版本常常会失效</u>。进一步讲，<u>如果类包含vector或者string成员，则其拷贝、赋值和销毁的合成版本能够工作</u>。


- 使用class和struct定义类唯一的区别就是<u>默认的访问权限</u>。即从定义开始到遇到第一个访问说明符（access specifier）前的访问权限，class是private的，struct是public的。


- <u>可以在类的内部把inline作为声明的一部分显式的声明成员函数，同样的，也能在类的外部用inline关键字修饰函数的的定义。</u>——这点和static、explicit不一样，注意区分，这两者只能出现在类中，不过编译器帮助发现类似错误。
- 有时会发生这样一种情况，我们希望能修改类的某个数据成员，即使是在一个const成员函数内。可以通过在变量的声明中加入<u>mutable</u>关键字做到这一点。<u>可变数据成员</u>永远不会是const，即使它是const对象的成员。


- 当提供一个类内初始值时，必须以<u>符号=或者花括号</u>表示。
- 一个const成员函数如果以引用的形式返回`*this`，那么它的返回类型将是常量引用。


- 类的定义分两个步骤（<u>编译器处理完类中的全部声明后才会处理成员函数的定义</u>）：
  - 首先，编译成员的声明
  - 直到类全部可见后才编译函数体。
  - 这两个步骤特别重要，因此可以在类中的任意位置引用成员（<u>不包括类中定义的类型，类型必须出现在使用之前</u>），无论是成员变量还是成员函数。


- <u>类型名的定义通常出现在类的开始处</u>，这样就能确保所有使用该类型的成员都出现在类名的定义之后。


- 有时可以忽略数据成员初始化和赋值之间的差异，但并非总是这样。<u>如果成员是const的或者是引用，或者属于某种未提供默认构造函数的类类型，必须而且只能通过构造函数初始值列表为这些成员提供初始值</u>。


- 如果一个构造函数为所有参数都提供了默认实参，则它<u>实际上</u>也定义了默认构造函数。（充分必要条件）
- 委托构造函数，有意思的特性，减少了代码重复。<u>一个委托构造函数使用它所属类的其他构造函数执行它自己的初始化过程，或者说它把它自己的一些（或者全部）职责委托给了其他构造函数</u>。


- <u>当用explicit关键字声明构造函数时，它将只能以直接初始化的形式使用</u>。而且，<u>编译器将不会再自动转换过程中使用该构造函数</u>。并且explicit只能出现在类内部的构造函数声明处。static也一样；不过inline都可以。


- C++语言在内置类型之间定义了几种自动转换规则，同样的，我们也能为类定义隐式转换规则。如果构造函数接受一个实参，<u>则它实际上定义了转换为此类类型的隐式转换机制，有时我们把这种构造函数称作转换构造函数</u>。


- 标准库中含有显式构造函数的类
  - <u>接受一个参数的const char*的string构造函数不是explicit的</u>。
  - <u>接受一个容量参数的vector构造函数是explicit的</u>。


- 聚合类（aggregate class）使得用户可以直接访问其成员，并且具有特殊的初始化语法形式。当一个类满足如下条件时，我们说它是聚合的：
  - 所有成员都是public的
  - 没有定义任何构造函数
  - 没有类内初始值
  - 没有基类，也没有virtual函数
  - 注：<u>基本上就是用struct定义的一组对象的集合，可以使用初始值列表进行初始化，在某些情况下会很方便</u>


- 当对象被<u>默认初始化</u>或<u>值初始化</u>时自动执行默认构造函数（个人理解默认初始化和值初始化的区别在于有没有初始化这个动作，如果有，则如果在初始化过程中被略过了，则是值初始化，否则就是默认初始化。只是区分的如此细是否有必要）。<u>默认初始化在以下情况下发生</u>：

  - 当在块作用域内不使用任何初始值定义一个非静态变量或者数组时
  - 当类本身含有类类型的成员且使用合成的默认构造函数时
  - 当类类型的成员没有在构造函数初始值列表中显示地初始化时

  <u>值初始化在以下情况下发生</u>：

  - 在数组初始化的过程中如果我们提供的初始值数量<u>少于</u>数组的大小时
  - 当<u>不使用初始值定义一个局部静态变量时</u>（静态变量和全局变量都会被编译器默认初始化）
  - 当通过书写形如`T()`的表达式<u>显式地请求值初始化时</u>，其中T时类型名（vector的一个构造函数只接受一个实参用于说明vector大小），它就是使用一个这种形式的实参来对它的元素初始化器进行值初始化的


- <u>字面值常量类（Literal Classes，不知道有什么用，很多限制）</u>


- <u>即使一个常量静态数据成员在类内部被初始化了，通常情况下也应该在类的外部定义一下该成员。</u>