# Chapter 13 Copy Control

**Exercise 13.1:** What is a copy constructor? When is it used?

```c++
// 拷贝构造函首先是一个构造函数，可以使用合适的参数来使用，编译器则根据参数进行函数匹配，然后构造对象。
// 如果使用`=`来定义对象，或者函数调用、参数返回、{}初始化列表等情况下，会隐式的使用拷贝构造函数进行对象的初始化
```

**Exercise 13.2:** Explain why the following declaration is illegal:

```c++
Sales_data::Sales_data(Sales_data rhs);

---
// 接受一个非引用对象的构造函数是非法的，会造成死循环，事实上编译器会报错，不会接受类似代码。
// error: invalid constructor; you probably meant 'Sales_data (Sales_data FOO&)'
```

**Exercise 13.3:** What happens when we copy a StrBlob? What about StrBlobPtrs?

```c++
// StrBlob没有定义拷贝构造函数，使用编译器合成的版本，会拷贝private的shared_ptr(vector)，指针语义
// StrBlobPtrs同样没有定义了拷贝构造函数，会拷贝private的数据成员，一个weak_ptr和一个int
```

**Exercise 13.4:** Assuming Point is a class type with a public copy constructor, identify each use of the copy constructor in this program fragment:

```c++
Point global;
Point foo_bar(Point arg)
{
    Point local = arg, *heap = new Point(global); 
  	*heap = local;
    Point pa[ 4 ] = { local, *heap };
    return *heap;
}

---
1. 函数调用的实参
2. Point local = arg
3. Point *heap = new Point(global), 一次是new Point显示使用，一次是隐式使用同2
4. Point pa[ 4 ] = { local, *heap }; {}列表初始化式会使用2次，进行对象拷贝
5. return *heap; 使用拷贝构造函数初始化调用点对象
```

**Exercise 13.5:** Given the following sketch of a class, write a copy constructor that copies all the members. Your constructor should dynamically allocate a new string (§ 12.1.2, p. 458) and copy the object to which ps points, rather than copying ps itself.

```c++
class HasPtr {
public:
	HasPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0) { }
private:
	std::string *ps;
	int i; 
};

---
HasPtr(const HasPtr &rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {}
```

**Exercise 13.6:** What is a copy-assignment operator? When is this operator used?What does the synthesized copy-assignment operator do? When is it synthesized?

```c++
// operator=，重载赋值运算符，本质上也是一个函数
// 当使用类类型对象对另外一个同类型的对象赋值时使用
// 类似合成构造函数，进行逐成员拷贝
// 如果类没有定义自己的拷贝赋值运算符，编译器就会生成一个
```

**Exercise 13.7:** What happens when we assign one StrBlob to another? What about StrBlobPtrs?

```c++
// 这两个类都没有定义自己的拷贝赋值运算符，所以都使用编译器合成的版本
// 就是逐个成员赋值，使用成员类型的赋值运算
```

**Exercise 13.8:** Write the assignment operator for the HasPtr class from exercise 13.5 in § 13.1.1 (p. 499). As with the copy constructor, your assignment operator should copy the object to which ps points.

```c++
HasPtr &operator=(const HasPtr &rhs) {
    if (this != &rhs) {
        delete ps;
        ps = new std::string(*rhs.ps);
        i = rhs.i;
    }
    return *this;
}
```

**Exercise 13.9:** What is a destructor? What does the synthesized destructor do? When is a destructor synthesized?

```c++
// 析构函数是负责对象销毁时做什么，析构函数释放对象使用的资源，并销毁对象的非static数据成员
// 按数据成员初始化逆序逐个销毁非static数据成员
// 当类没有定义自己的析构函数时，编译器会合成析构函数
```

**Exercise 13.10:** What happens when a StrBlob object is destroyed? What about a StrBlobPtr?

```c++
// StrBlob没有定义自己的析构函数，使用编译器合成的版本，函数体为空，会销毁vector数据成员，因此会调用vector的析构函数完成成员销毁
// StrBlobPtr包含一个weak_ptr和一个内置类型，销毁内置类型什么也不做，销毁weak_ptr则调用其析构函数
```

**Exercise 13.11:** Add a destructor to your HasPtr class from the previous exercises.

```c++
~HasPtr() { delete ps; }
// 因为ps是内置类型，没有析构函数，所以需要在函数体中显示的释放动态申请的内存
```

**Exercise 13.12:** How many destructor calls occur in the following code fragment?

```c++
bool fcn(const Sales_data *trans, Sales_data accum) {
	Sales_data item1(*trans), item2(accum);
	return item1.isbn() != item2.isbn(); 
}

---
3，分别是item1、item2、accm离开作用域时，即函数返回
```

**Exercise 13.13:** A good way to understand copy-control members and constructors is to define a simple class with these members in which each member prints its name:

```c++
struct X {
	X() {std::cout << "X()" << std::endl;}
	X(const X&) {std::cout << "X(const X&)" << std::endl;}
};
```

Add the copy-assignment operator and destructor to X and write a program using X objects in various ways: Pass them as nonreference and reference parameters; dynamically allocate them; put them in containers; and so forth. Study the output until you are certain you understand when and why each copy-control member is used. As you read the output, remember that the compiler can omit calls to the copy constructor.

```c++
X test(X x) {
    return x;
}
X test2(X &x) {
    return x;
}
// 13.13
{
     X x;
     X x2 = test(x);
}
std::cout << std::endl;
{
    X x;
    X x2 = test2(x);
}
std::cout << std::endl;
{
    X *x3 = new X();
    delete x3;
}
std::cout << std::endl;
std::vector<X> xvec(3);
```

**Exercise 13.14:** Assume that numbered is a class with a default constructor that generates a unique serial number for each object, which is stored in a data member named mysn. Assuming numbered uses the synthesized copy-control members and given the following function:

```c++
void f (numbered s) { cout << s.mysn << endl; }
```

what output does the following code produce?

```c++
numbered a, b = a, c = b;
f(a); f(b); f(c);


---
// 输出的都是a的序号
```

**Exercise 13.15:** Assume numbered has a copy constructor that generates a new serialnumber. Does that change the output of the calls in the previous exercise? If so, why? What output gets generated?

```c++
// 会，输出三个不同的序列号，但是却不是a、b、c的，而是在函数调用中新生成的
```

**Exercise 13.16:** What if the parameter in f were `const numbered&`? Does that change the output? If so, why? What output gets generated?

```c++
// 会，输出a、b、c的序列
```

**Exercise 13.17:** Write versions of numbered and f corresponding to the previous three exercises and check whether you correctly predicted the output.

```c++
class numberd {
public:
    numberd() : mysn(src++) {}
    numberd(const numberd &rhs) : mysn(src++) {}
    int mysn;
private:
    static int src;
};

void f(numberd s) {
    std::cout << s.mysn << std::endl;
}
void f2(const numberd &s) {
    std::cout << s.mysn << std::endl;
}
```

**Exercise 13.18:** Define an Employee class that contains an employee name and aunique employee identifier. Give the class a default constructor and a constructor thattakes a string representing the employee’s name. Each constructor should generatea unique ID by incrementing a static data member.

```c++
class Employee {
public:
    Employee() = default;

    Employee(std::string name_) :
            name(name_), id(src++) {}
    
private:
    std::string name;
    int id;
    static int src;
};
```

**Exercise 13.19:** Does your Employee class need to define its own versions of thecopy-control members? If so, why? If not, why not? Implement whatever copy-controlmembers you think Employee needs.

```c++
// 不需要自定义任何拷贝控制成员，使用编译器合成版本即可
```

**Exercise 13.20:** Explain what happens when we copy, assign, or destroy objects of ourTextQuery and QueryResult classes from § 12.3 (p. 484).

```c++
// TextQuery和QueryResult的数据成员要么是容器map和string，要么是shared_ptr，都是值语义
// 在拷贝、赋值时，会产生独立的副本；在销毁时，依次逆序销毁成员
```

**Exercise 13.21:** Do you think the TextQuery and QueryResult classes need to de-fine their own versions of the copy-control members? If so, why? If not, why not?Implement whichever copy-control operations you think these classes require.

```c++
// 不需要，因为都是值语义，使用合成版本即可
```

**Exercise 13.22:** Assume that we want HasPtr to behave like a value. That is, each object should have its own copy of the string to which the objects point. We’ll show the definitions of the copy-control members in the next section. However, you already know everything you need to know to implement these members. Write the HasPtr copy constructor and copy-assignment operator before reading on.

```c++
// copy ctor
HasPtr(const HasPtr &p) :
            ps(new std::string(*p.ps)), i(p.i) {}

HasPtr &HasPtr::operator=(const HasPtr &p) {
    auto *newp = new std::string(*p.ps);
    delete ps;
    ps = newp;
    i = p.i;
    return *this;
}
```

**Exercise 13.23:** Compare the copy-control members that you wrote for the solutionsto the previous section’s exercises to the code presented here. Be sure you understandthe differences, if any, between your code and ours.

**Exercise 13.24:** What would happen if the version of HasPtr in this section didn’tdefine a destructor? What if HasPtr didn’t define the copy constructor?

```c++
// 对象析构时不会释放指针指向的内存，导致内存泄漏
// 没有定义拷贝构造会使用合成版本，当对象拷贝时，导致多个对象指向同样的内存空间，共享同一个stirng
```

**Exercise 13.25:** Assume we want to define a version of StrBlob that acts like a value.Also assume that we want to continue to use a shared_ptr so that our StrBlobPtrclass can still use a weak_ptr to the vector. Your revised class will need a copyconstructor and copy-assignment operator but will not need a destructor. Explain whatthe copy constructor and copy-assignment operators must do. Explain why the classdoes not need a destructor.

```c++
// 因为每个StrBlob都需要有自己的副本
// 拷贝构造函数：必须拷贝一份底层vector，放到shared_ptr之中
// 拷贝赋值操作符：同样必须拷贝一份底层vector
// 不需要析构函数的原因是，shared_ptr析构时会自动释放vector，使用合成版本即可
```

**Exercise 13.26:** Write your own version of the StrBlob class described in the previous exercise.

```c++
using DataType = std::vector<std::string>;

// copy ctor
StrBlob::StrBlob(const StrBlob &s)
        : data(std::make_shared<DataType>()) {
    auto *vec = new std::vector<std::string>(*s.data);
    data.reset(vec);
}

// copy-assignment operator
StrBlob &StrBlob::operator=(const StrBlob &s) {
    auto *vec = new std::vector<std::string>(*s.data);
    data.reset(vec);
    return *this;
}
```

**Exercise 13.27:** Define your own reference-counted version of HasPtr.

```c++
#include <string>
class HasPtr {
public:
    // default ctor
    HasPtr(const std::string &s = std::string()) :
            ps(new std::string(s)), cnt(new std::size_t(1)), i(0) {}
    // copy ctor
    HasPtr(const HasPtr &p) : ps(p.ps), cnt(p.cnt), i(p.i) { ++*cnt; }
    // copy-assignment operator
    HasPtr &operator=(const HasPtr &p);
    // dtor
    ~HasPtr();

private:
    std::string *ps;
    std::size_t *cnt;
    int i;
};
HasPtr::~HasPtr() {
    if (--*cnt == 0) {
        delete ps;
        delete cnt;
    }
}
HasPtr &HasPtr::operator=(const HasPtr &p) {
    ++*p.cnt;
    if (--*cnt == 0) {
        delete ps;
        delete cnt;
    }
    ps = p.ps;
    cnt = p.cnt;
    i = p.i;
    return *this;
}
```

**Exercise 13.28:** Given the following classes, implement a default constructor and the necessary copy-control members.

```c++
(a) 
class TreeNode {
private:
	std::string value;
    int         count;
    TreeNode    *left;
    TreeNode    *right;
};

(b) 
class BinStrTree {
private:
	TreeNode *root;
};

---
class TreeNode {
    TreeNode() : count(0), left(nullptr), right(nullptr) {}

private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;
};

class BinStrTree {
    BinStrTree() : root(nullptr) {}

private:
    TreeNode *root;
};

// 其实上面两个类都没有需要管理类外部资源，因此不需要自定义任何拷贝控制成员，使用合成版本即可。
```

**Exercise 13.29:** Explain why the calls to swap inside `swap(HasPtr&, HasPtr&)` do not cause a recursion loop.

```c++
// swap中调用的swap函数，传入的参数类型是其成员的类型，不会调用自身的swap函数
```

**Exercise 13.30:** Write and test a swap function for your valuelike version of HasPtr. Give your swap a print statement that notes when it is executed.

```c++
inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "- swap -" << std::endl;
}

---
// 赋值时被调用
```

**Exercise 13.31:** Give your class a < operator and define a vector of HasPtrs. Givethat vector some elements and then sort the vector. Note when swap is called.

```c++
bool operator<(const HasPtr &p) { return i < p.i; }
```

**Exercise 13.32:** Would the pointerlike version of HasPtr benefit from defining a swap function? If so, what is the benefit? If not, why not?

```c++
// 不会，类指针的HasPtr行为类似指针，没有额外的拷贝，可以直接使用临时变量进行交换
// 即使定义swap函数，其开销和直接使用临时变量的开销一样，没有任何节约
```

**Exercise 13.33:** Why is the parameter to the `save` and `remove` members of Messagea `Folder&`? Why didn’t we define that parameter as `Folder`? Or `const Folder&`?

```c++
// 因为需要添加到制定的foler，如果是Folder，那么会添加到本地的一个Folder拷贝
// 不是const Folder&的原因，是save/remove会修改Folder对象
```

**Exercise 13.34:** Write the Message class as described in this section.

**Exercise 13.35:** What would happen if Message used the synthesized versions of the copy-control members?

```c++
// 拷贝构造：folder不知道新的message的存在
// 拷贝赋值：message中保存的folder指针指向的不是它自己，而是赋值的那个message
// 析构: folder中保存的message变成空悬指针
```

**Exercise 13.36:** Design and implement the corresponding Folder class. That class should hold a set that points to the Messages in that Folder.

```c++
// folder.h
#ifndef _FOLDER_H_
#define _FOLDER_H_
#include <set>
class Message;
class Folder {
    friend void swap(Folder &, Folder &);
public:
    Folder() = default;
    // copy ctor
    Folder(const Folder &);
    // copy-assignment operator
    Folder &operator=(const Folder &);
    // dtor
    ~Folder();
    void addMsg(Message *);
    void rmMsg(Message *);
private:
    std::set<Message *> messages;
    void add_to_messages(const Folder &);
    void remove_from_messages();
};
inline void Folder::addMsg(Message *m) {
    messages.insert(m);
}
inline void Folder::rmMsg(Message *m) {
    messages.erase(m);
}
void swap(Folder &, Folder &);
#endif

// folder.cc
#include "message.h"
void Folder::add_to_messages(const Folder &f) {
    for (auto *m:f.messages) {
        m->folders.insert(this);
    }
}
void Folder::remove_from_messages() {
    for (auto *m:messages) {
        m->folders.erase(this);
    }
}
// copy ctor
Folder::Folder(const Folder &f) {
    add_to_messages(f);
    messages = f.messages;
}
Folder::~Folder() {
    remove_from_messages();
}
// copy-assignment operator
Folder &Folder::operator=(const Folder &f) {
    if (this != &f) {
        remove_from_messages();
        add_to_messages(f);
        messages = f.messages;
    }
    return *this;
}
void swap(Folder &lhs, Folder &rhs) {
    using std::swap;

    lhs.remove_from_messages();
    rhs.remove_from_messages();

    swap(lhs.messages, rhs.messages);

    lhs.add_to_messages(lhs);
    rhs.add_to_messages(rhs);
}
```

**Exercise 13.37:** Add members to the Message class to insert or remove a givenFolder* into folders. These members are analogous to Folder’s addMsg andremMsg operations.

```c++
inline void Message::addFolder(Folder *f) {
    folders.insert(f);
}
inline void Message::rmFolder(Folder *f) {
    folders.erase(f);
}
```

**Exercise 13.38:** We did not use copy and swap to define the Message assignment operator. Why do you suppose this is so?

```c++
// 因为swap的开销很大，需要扫描两次需要交换的Message的Folder，而正常实现的赋值操作符只需要扫描一次
// 使用copy and swap来实现，则copy+swap的开销大于直接实现
```

**Exercise 13.39:** Write your own version of StrVec, including versions of reserve,capacity (§ 9.4, p. 356), and resize (§ 9.3.5, p. 352).

**Exercise 13.40:** Add a constructor that takes an initializer_list<string> toyour StrVec class.

**Exercise 13.41:** Why did we use postfix increment in the call to construct insidepush_back? What would happen if it used the prefix increment?

```c++
// 因为first_free指向的是第一个还没有使用的空间
// 如果使用前置递增，会导致空洞
```

**Exercise 13.42:** Test your StrVec class by using it in place of the vector<string>in your TextQuery and QueryResult classes (§ 12.3, p. 484).

**Exercise 13.43:** Rewrite the free member to use for_each and a lambda (§ 10.3.2,p. 388) in place of the for loop to destroy the elements. Which implementation do you prefer, and why?

```c++
std::for_each(element, first_free,
              [&](const std::string) {
                  alloc.destroy(--first_free);
              });
// for_each+lambda的版本不是很直观，个人更倾向于for loop版本
// 因为for_each穿给lambda的参数是元素，而destory需要的是指向元素的指针，不能很好的配合
```

**Exercise 13.44:** Write a class named String that is a simplified version of the library string class. Your class should have at least a default constructor and a constructor that takes a pointer to a C-style string. Use an allocator to allocate memory that your String class uses.

```c++
// good exercise
```

**Exercise 13.45:** Distinguish between an rvalue reference and an lvalue reference.

**Exercise 13.46:** Which kind of reference can be bound to the following initializers?

```c++
int f();
vector<int> vi(100);
int? r1 = f();
int? r2 = vi[0];
int? r3 = r1;
int? r4 = vi[0] * f();
```

**Exercise 13.47:** Give the copy constructor and copy-assignment operator in yourString class from exercise 13.44 in § 13.5 (p. 531) a statement that prints a messageeach time the function is executed.

**Exercise 13.48:** Define a `vector<String>` and call push_back several times on thatvector. Run your program and see how often Strings are copied.	Exercise 13.49: Add a move constructor and move-assignment operator to yourStrVec, String, and Message classes.

**Exercise 13.50:** Put print statements in the move operations in your String class andrerun the program from exercise 13.48 in § 13.6.1 (p. 534) that used a vector<String>to see when the copies are avoided.

**Exercise 13.51:** Although unique_ptrs cannot be copied, in § 12.1.5 (p. 471) wewrote a clone function that returned a unique_ptr by value. Explain why that func-tion is legal and how it works.

**Exercise 13.52:** Explain in detail what happens in the assignments of the HasPtr ob-jects on page 541. In particular, describe step by step what happens to values of hp,hp2, and of the rhs parameter in the HasPtr assignment operator.

**Exercise 13.53:** As a matter of low-level efficiency, the HasPtr assignment operatoris not ideal. Explain why. Implement a copy-assignment and move-assignment oper-ator for HasPtr and compare the operations executed in your new move-assignmentoperator versus the copy-and-swap version.

**Exercise 13.54:** What would happen if we defined a HasPtr move-assignment oper-ator but did not change the copy-and-swap operator? Write code to test your answer.

**Exercise 13.55:** Add an rvalue reference version of push_back to your StrBlob.

**Exercise 13.56:** What would happen if we defined sorted as:

```c++
Foo Foo::sorted() const & { Foo ret(*this);
	return ret.sorted();
}
```

**Exercise 13.57:** What if we defined sorted as:

```c++
Foo Foo::sorted() const & { return Foo(*this).sorted(); }
```

**Exercise 13.58:** Write versions of class Foo with print statements in their sorted functions to test your answers to the previous two exercises.

### Notes

- 在C++中，通过定义<u>构造函数</u>来控制在类类型的对象<u>初始化</u>时做什么。类还可以控制在<u>对象拷贝、赋值、移动和销毁</u>时做什么。在这方面，C++和其他语言是不同的，其他很多语言都没有给予类设计者控制这些操作的能力。
- 类通过特殊的成员函数来控制这些操作，包括：<u>拷贝构造</u>函数、<u>移动构造</u>函数、<u>拷贝赋值</u>运算符、<u>移动赋值</u>运算符。


- 拷贝构造和移动构造函数定义了<u>当用同类型的另外一个对象初始化本对象时</u>做什么。拷贝和赋值运算符定义了<u>将一个对象赋予同类型的另一个对象时</u>做什么。析构函数定义了当此类型对象销毁时做什么。我们称这些操作为<u>拷贝控制操作（copy control）</u>。
- **直接初始化**：实际上是要求编译器使用普通的函数匹配在选择与提供的参数最匹配的构造函数。
- **拷贝初始化**：要求编译器将右侧运算对象拷贝到正在创建的对象中，如果需要还要进行类型转换。<u>在函数调用传参数和返回时（非引用类型）会进行拷贝初始化</u>，直接创建对象时用拷贝初始化的情形大概不会很多，毕竟直接调用合适的构造函数就好了，为何非要构造一个临时对象，然后再进行拷贝呢。
- 拷贝初始化再<u>用 = 定义变量</u>时会发生，在下列情形中也会发生：（下面的情况才是更为常见的情形）
  - 将一个对象作为实参传递给一个非引用类型的形参
  - 从一个返回类型为非引用类型的函数返回一个对象
  - <u>用花括号初始化列表初始化一个数组中的元素或一个聚合类中的成员</u>（新标准引用的统一花括号初始化进行的也是拷贝初始化）
  - Notes：上述情况都是隐式的使用拷贝构造函数，<u>因为不应该将拷贝构造定义为explicit的</u>。


- 与合成默认构造函数不同，即使定义了其他构造函数，但没有定义拷贝构造函数，编译器也会合成一个拷贝构造函数。也就是说，<u>拷贝构造函数是必须的</u>，每个类类型必须有，如果要禁止拷贝，则需要显示的说明，使用deleted。


- 拷贝构造函数被用来初始化非引用类型参数，这一特性解释了<u>为什么拷贝构造函数自己的参数必须是引用类型</u>。如果其参数不是引用类型，则调用永远也不会成功——为了调用拷贝构造函数，必须拷贝它的实参，但为了拷贝实参，又需要调用拷贝构造函数，如此无限循环。


- <u>与拷贝构造函数一样，如果类未定义自己的拷贝赋值运算符，编译器会为它合成一个</u>。


- 赋值运算符通常应该<u>返回一个指向其左侧运算对象的引用</u>。（为了与内置类型的赋值保持一致，支持连续赋值）
- 由于析构函数不接受参数，因此不能被重载。对于一个类，只会有唯一一个析构函数。
- <u>隐式销毁一个内置指针类型的成员不会delete它所指向的对象</u>。
- 如果构造函数有一个**初始化部分**和**一个函数体**，析构函数也有**一个函数体**和一个**析构部分**。在构造函数中，成员的初始化是在函数体执行前完成的，且按照它们在类中出现的顺序进行初始化。在析构函数中，首先执行函数体，然后销毁成员。成员按初始化顺序的逆序销毁。<u>在析构函数中，不存在类似构造函数中初始化列表的东西来控制成员如何销毁，析构部分是隐式的</u>。成员析构是发生什么完全依赖于成员的类型。销毁类类型的成员需要执行成员<u>自己的析构函数。内置类型没有析构函数，因此析构内置类型成员什么也不需要做</u>。


- 无论何时一个<u>对象被销毁</u>，就会自动调用其析构函数:（<u>销毁和析构是伴随发生的</u>，这个保证还是非常强的）
  - 变量在离开其作用域时被销毁
  - 当一个对象被销毁时，其成员被销毁
  - 容器（标准库容器、数组）被销毁时，其元素被销毁
  - 对于动态分配的对象，当对指向它的指针应用delete运算符时被销毁
  - <u>对于临时对象，当创建它的完整表达式结束时被销毁</u>。（什么时候是“完整表达式结束”的时候？）


- <u>当指向一个对象的引用或指针离开作用域时，析构函数不会执行</u>。


- <u>当一个类未定义自己的析构函数时，编译器会为它定义一个合成析构函数</u>。
- <u>认识到析构函数自身不直接销毁成员是非常重要的</u>。<u>成员是在析构函数体之后隐含的析构阶段中被销毁的</u>。<u>在整个对象销毁过程中，析构函数体是作为成员销毁步骤之外的另一部分而进行的</u>。


- 需要析构的类也需要拷贝和复制操作
- 需要拷贝操作的类也需要赋值操作，反之亦然，但都不必然意味着也需要析构函数。


- 使用`=default`来显式的要求编译器生成合成的版本
- 在新标准下，可以通过将拷贝构造函数和拷贝赋值运算符定义为<u>删除的函数（deleted function）来阻止拷贝</u>。删除的函数指：<u>虽然声明了它们，但不能以任何方式使用它们</u>。在函数参数列表后加上`=delete`指出定义为删除的。


- 对于一个删除了析构函数的类型，<u>编译器将不允许定义该类型的变量或创建该类的临时对象</u>，但是却可以动态分配这种类型的对象，只是不能释放这些对象。
- <u>本质上，当不可能拷贝、赋值或销毁类的成员时，类的合成拷贝控制成员函数就被定义为删除的</u>。
- <u>希望阻止拷贝的类应该使用`= delete`来定义它们自己的拷贝构造函数和拷贝赋值运算符，而不应该将它们声明为private的</u>。


- 确定类型对象的拷贝语义，一般来说，有两种选择：可以定义拷贝操作，使类的行为看起来像一个值或者像一个指针。标准库容器和string类的行为像一个值，shared_ptr类提供类似指针的行为，IO类型和unique_ptr不允许拷贝或赋值，因此它们的行为既不像值也不像指针。
- 编写赋值运算符时，有两点需要记住：
  - 如果将一个对象赋予它自身，赋值运算符必须能正常工作。
  - 大多数赋值运算符组合了析构函数和拷贝构造函数的工作。
  - 一个好的模式是先将右侧运算对象拷贝到一个局部临时对象中，拷贝完成后，销毁左侧运算对象就是安全的了。一旦左侧运算对象的资源被销毁，就只剩下讲数据从临时对象拷贝到左侧运算对象的成员中了。


- <u>swap函数应该调用swap，而不是std::swap</u>。<u>每个swap调用都应该是未加限定的，如果存在特定类型的swap版本，其匹配程度会优于std中定义的版本</u>。因此如果存在特定类型的swap版本，swap调用会与之匹配。如果不存在类型特定的版本，则会使用std的版本。