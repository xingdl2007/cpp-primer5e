# Chapter 12 Dynamic Memory

**Exercise 12.1:** How many elements do b1 and b2 have at the end of this code?

```c++
StrBlob b1; {
	StrBlob b2 = {"a", "an", "the"}; b1 = b2;
	b2.push_back("about");
}

---
// 4个元素
```

**Exercise 12.2:** Write your own version of the StrBlob class including the const versions of front and back.

```c++
// 参见配套代码
inline const std::string &StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

inline const std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}
```

**Exercise 12.3:** Does this class need const versions of push_back and pop_back? If so, add them. If not, why aren’t they needed?

```c++
// 不需要，从语义上讲，push_back/pop_back修改了类的数据成员
```

**Exercise 12.4:** In our check function we didn’t check whether i was greater thanzero. Why is it okay to omit that check?

```c++
// 因为形参类型为size_t类型，是无符号数，肯定是大于0的，不需要检查
```

**Exercise 12.5:** We did not make the constructor that takes an initializer_listexplicit (§ 7.5.4, p. 296). Discuss the pros and cons of this design choice.

```c++
// 接受initializer_list的构造函数不是explicit的，可以在需要StrBlob的地方，使用{}，增加了使用的灵活性，缺点就是可能误用。
```

**Exercise 12.6:** Write a function that returns a dynamically allocated vector of ints.Pass that vector to another function that reads the standard input to give values tothe elements. Pass the vector to another function to print the values that were read.Remember to delete the vector at the appropriate time.

```c++
#include <iostream>
#include <vector>
#include <memory>

using std::cin; using std::cout; using std::endl;
using std::vector; using std::shared_ptr;

vector<int> *factory() {
    return new vector<int>();
}

vector<int> *fill(vector<int> *ivec) {
    for (int i = 1; i <= 10; i++) {
        ivec->push_back(i);
    }
    return ivec;
}

void print(vector<int> *ivec) {
    auto b = ivec->cbegin(), e = ivec->cend();
    while (b != e) {
        cout << *b << endl;
        ++b;
    }
    delete ivec;
}
```

**Exercise 12.7:** Redo the previous exercise, this time using shared_ptr.

```c++
// shared_ptr version
shared_ptr<vector<int>> factory2() {
    return std::make_shared<vector<int>>();
}

shared_ptr<vector<int>> fill2(shared_ptr<vector<int>> ivec) {
    for (int i = 1; i <= 10; i++) {
        ivec->push_back(11 - i);
    }
    return ivec;
}

void print2(shared_ptr<vector<int>> ivec) {
    auto b = ivec->cbegin(), e = ivec->cend();
    while (b != e) {
        cout << *b << endl;
        ++b;
    }
}

int main() {
    // new/read/print
    print(fill(factory()));

    // shared_ptr version
    print2(fill2(factory2()));
    return 0;
}
```

**Exercise 12.8:** Explain what if anything is wrong with the following function.

```c++
bool b() {
	int* p = new int; // . . .
	return p;
}

---
// 指针指向了一个对象，所以会返回true，但是有内存泄漏。
```

**Exercise 12.9:** Explain what happens in the following code:

```c++
int *q = new int(42), *r = new int(100);
r = q;
auto q2 = make_shared<int>(42), r2 = make_shared<int>(100); 
r2 = q2;

---
// 结果类似；只是raw指针的版本有内存泄漏。智能指针的版本没有。
```

**Exercise 12.10:** Explain whether the following call to the process function defined on page 464 is correct. If not, how would you correct the call?

```c++
shared_ptr<int> p(new int(42));
process(shared_ptr<int>(p));

---
// 正确，不过为什么要构造一个临时的shared_ptr，直接传p就好了。
```

**Exercise 12.11:** What would happen if we called process as follows?

```c++
process(shared_ptr<int>(p.get()));

---
// 函数调用完会导致对象释放，错误的使用。
```

**Exercise 12.12:** Using the declarations of p and sp explain each of the following calls to process. If the call is legal, explain what it does. If the call is illegal, explain why:

```c++
auto p = new int();
auto sp = make_shared<int>(); 
(a) process(sp);
(b) process(new int());
(c) process(p);
(d) process(shared_ptr<int>(p));

---
(a) legal, 使用sp拷贝初始化process参数，函数调用期间引用计数至少是2
(b) illegal, 必须直接初始化shared_ptr，不能copy 初始化
(c) illegal，同上
(d) legal，不过函数调用结束，p指向的对象已经被释放了。
```

**Exercise 12.13:** What happens if we execute the following code?

```c++
auto sp = make_shared<int>();
auto p = sp.get();
delete p;

---
// 导致sp中保存的指针是空悬指针
```

**Exercise 12.14:** Write your own version of a function that uses a shared_ptr to manage a connection.

```c++
#include <iostream>
#include <memory>
using std::cin; using std::cout; using std::endl;
using std::shared_ptr;

struct connection {
    int conn;
};
connection connect() {
    return {100};
}
void disconnect(connection conn) {
    cout << conn.conn << endl;
}
void end_connection(connection *p) {
    disconnect(*p);
}
int main() {
    connection c = connect();
    shared_ptr<connection> ptr(&c, end_connection);
    return 0;
}
```

**Exercise 12.15:** Rewrite the first exercise to use a lambda (§ 10.3.2, p. 388) in place ofthe end_connection function.

```c++
shared_ptr<connection> ptr(&c, [](connection *p) { disconnect(*p); });
```

**Exercise 12.16:** Compilers don’t always give easy-to-understand error messages if weattempt to copy or assign a unique_ptr. Write a program that contains these errorsto see how your compiler diagnoses them.

```c++
// 错误信息还是很明显的
```

**Exercise 12.17:** Which of the following unique_ptr declarations are illegal or likelyto result in subsequent program error? Explain what the problem is with each one.

```c++
int ix = 1024, *pi = &ix, *pi2 = new int(2048); 
typedef unique_ptr<int> IntP;
(a) IntP p0(ix);
(b) IntP p1(pi);
(c) IntP p2(pi2);
(d) IntP p3(&ix);
(e) IntP p4(new int(2048));
(f) IntP p5(p2.get());

---
(a) illegal, 类型错误，ix不是指针类型
(b) undefined, pi指向局部变量 
(c) legal
(d) undefined，ix指向局部变量
(e) legal
(f) illegal，两个unique_ptr指向同一个对象
```

**Exercise 12.18:** Why doesn’t shared_ptr have a release member?

```c++
// 因为可能有多个shared_ptr指向相同的对象，无法可靠实现release；只能修改自己。
```

**Exercise 12.19:** Define your own version of StrBlobPtr and update your StrBlobclass with the appropriate friend declaration and begin and end members.

```c++
// 参见作者配套代码
```

**Exercise 12.20:** Write a program that reads an input file a line at a time into a StrBloband uses a StrBlobPtr to print each element in that StrBlob.

```c++
// 参见作者配套代码
```

**Exercise 12.21:** We could have written StrBlobPtr’s deref member as follows:

```c++
std::string& deref() const
{ return (*check(curr, "dereference past end"))[curr]; }

---
// 这个不好，不易读
```

Which version do you think is better and why?

**Exercise 12.22:** What changes would need to be made to StrBlobPtr to create a class that can be used with a const StrBlob? Define a class named ConstStrBlobPtr that can point to a const StrBlob.

```c++
// 1. 需要修改StrBlobPtr的构造函数，接受一个const StrBlob&
// 2. 定义ConstStrBlobPtr类型
// 3. 增加StrBlob的begin和end函数的const重载版本，返回ConstStrBlobPtr类型
// 4. 在ConstStrBlobPtr类型中的deref()函数，返回const string&，阻止修改。
```

**Exercise 12.23:** Write a program to concatenate two string literals, putting the resultin a dynamically allocated array of char. Write a program to concatenate two librarystrings that have the same value as the literals used in the first program.

**Exercise 12.24:** Write a program that reads a string from the standard input into adynamically allocated character array. Describe how your program handles varyingsize inputs. Test your program by giving it a string of data that is longer than the arraysize you’ve allocated.

**Exercise 12.25:** Given the following new expression, how would you delete pa?

```c++
int *pa = new int[10];

---
delete[] pa;
```

**Exercise 12.26:** Rewrite the program on page 481 using an allocator.

```c++
// 参考作者配套代码
```

**Exercise 12.27:** The TextQuery and QueryResult classes use only capabilities thatwe have already covered. Without looking ahead, write your own versions of theseclasses.

**Exercise 12.28:** Write a program to implement text queries without defining classes tomanage the data. Your program should take a file and interact with a user to query forwords in that file. Use vector, map, and set containers to hold the data for the fileand to generate the results for the queries.

**Exercise 12.29:** We could have written the loop to manage the interaction with theuser as a do while (§ 5.4.4, p. 189) loop. Rewrite the loop to use a do while. Explainwhich version you prefer and why.

**Exercise 12.30:** Define your own versions of the TextQuery and QueryResultclasses and execute the runQueries function from § 12.3.1 (p. 486).

**Exercise 12.31:** What difference(s) would it make if we used a vector instead of aset to hold the line numbers? Which approach is better? Why?

**Exercise 12.32:** Rewrite the TextQuery and QueryResult classes to use a StrBlobinstead of a vector<string> to hold the input file.

**Exercise 12.33:** In Chapter 15 we’ll extend our query system and will need some addi-tional members in the QueryResult class. Add members named begin and end thatreturn iterators into the set of line numbers returned by a given query, and a membernamed get_file that returns a shared_ptr to the file in the QueryResult object.

### Notes

- <u>全局对象在程序启动时分配，在程序结束时销毁。对于局部自动对象，当我们进入其定义所在的程序块时被创建，在离开块时被销毁。**局部static对象在第一次使用前分配，在程序结束时销毁**。</u>


- 除了自动和static对象外，C++还支持动态分配对象。动态分配的对象的生命期与它们在哪里创建的是无关的，只有当显示地被释放时，这些对象才会销毁。<u>标准库定义了两个智能指针类型来管理动态分配的对象，当一个对象应该被释放时，指向它的智能指针可以确保自动释放它</u>。
- <u>空悬指针（dangling pointer）</u>，指向一块曾经保存数据对象但现在已经无效的内存的指针。
- <u>野指针</u>，为初始化的指针。


- <u>智能指针接受原始指针参数的构造函数是explicit的</u>，因此必须使用直接初始化形式来初始化一个智能指针。


- <u>不能拷贝unique_ptr的规则有一个例外</u>：可以拷贝或者赋值一个将要被销毁的unique_ptr。<u>最常见的情况就是从函数返回一个unique_ptr</u>。这种情况下也是控制权的转移。

- ```c++
  unique_ptr<int> clone(int p) {
      return unique_ptr<int>(new int(p));
  }
  unique_ptr<int> clone2(int p) {
      unique_ptr<int> ret(new int(p));
      return ret;
  }
  ```


- new有一些灵活性上的局限，其中一方面表现在它将内存分配和对象构造组合在了一起。类似的，delete将对象析构和内存释放组合在了一起。