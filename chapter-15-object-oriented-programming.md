# Chapter 15 Object-Oriented Programming

**Exercise 15.1:** What is a virtual member?

```c++
// 基类将允许派生类override的成员定义成virtual的；一般是成员函数，也就是说virtual member是允许派生类override的成员。
```

**Exercise 15.2:** How does the protected access specifier differ from private?

```c++
// private对所有类的用户来说都是private的，无论这个用户是别的无关类，还是这个类的派生类
// protected提供了区分派生类和非派生类的访问控制手段，即派生类可以访问基类的protected成员
```

**Exercise 15.3:** Define your own versions of the Quote class and the print_total function.

```c++
class Quote {
public:
    // constructors
    Quote() = default;

    Quote(const std::string &s, double sales_price) :
            bookNo(s), price(sales_price) {}

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const {
        return n * price;
    }

    virtual ~Quote() = default;

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

double print_total(ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}
```

**Exercise 15.4:** Which of the following declarations, if any, are incorrect? Explain why.

```c++
class Base { ... };
(a) class Derived : public Derived { ... }; 
(b) class Derived : private Base { ... }; 
(c) class Derived : public Base;

---
(a) 一个类的直接基类不能是其本身
(b) 正确
(c) 声明不能包含派生类列表
```

**Exercise 15.5:** Define your own version of the Bulk_quote class.

```c++
class Bulk_Quote : public Quote {
public:
    Bulk_Quote() = default;

    Bulk_Quote(const std::string &s, double p, std::size_t min, double dis)
            : Quote(s, p), min_qty(min), discount(dis) {}

    double net_price(std::size_t n) const override {
        if (n >= min_qty) {
            return price * (1 - discount) * n;
        }
        return price * n;
    }

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
```

**Exercise 15.6:** Test your print_total function from the exercises in § 15.2.1 (p. 595) by passing both Quote and Bulk_quote objects o that function.

```c++
#include <string>
#include <iostream>
#include "book.h"

using namespace std;

double print_total(ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

int main() {
    Quote q("111-222-333-444", 10.51);
    Bulk_Quote b("444-333-222-111", 99.99, 50, 0.2);
    print_total(cout, q, 100);
    print_total(cout, b, 100);
    return 0;
}
```

**Exercise 15.7:** Define a class that implements a limited discount strategy, which ap-plies a discount to books purchased up to a given limit. If the number of copies exceedsthat limit, the normal price applies to those purchased beyond the limit.

```c++
class Limited_Quote : public Quote {
public:
    Limited_Quote() = default;

    Limited_Quote(const std::string &s, double p, std::size_t max, double dis)
            : Quote(s, p), max_qty(max), discount(dis) {}

    double net_price(std::size_t n) const override {
        if (n > max_qty) {
            return n * price;
        }
        return n * (1 - discount) * price;
    }

    ~Limited_Quote() = default;

private:
    std::size_t max_qty = 0;
    double discount = 0.0;
};
```

**Exercise 15.8:** Define static type and dynamic type.

```c++
// static type: 表达式的静态类型总是已知的，它是变量声明时的类型或表达式生成的类型。
// dynamic type: 变量或表达式表示的内存中的对象的类型。动态类型只有在运行时才可知。
```

**Exercise 15.9:** When is it possible for an expression’s static type to differ from its dynamic type? Give three examples in which the static and dynamic type differ.

```c++
// 1. 空指针；空指针通常有静态类型，但实际不指向任何对象，也就没有动态类型
// 2. const char *；静态类型是const字符指针，实际可能指向了一个字符数组
// 3. 基类指针；静态类型是指向基类对象的指针，实际可能指向的是派生类对象
```

**Exercise 15.10:** Recalling the discussion from § 8.1 (p. 311), explain how the programon page 317 that passed an ifstream to the Sales_data read function works.

```c++
// read函数接受istream&的参数，当传递ifstream的对象时，发生了派生类到基类的隐式转换，形参绑定到了派生类的对象
// 上了。 调用重载的>>运算符时，实际从文件流中获得数据，推断此重载运算符是虚函数 (当然实际情况更加复杂)
```

**Exercise 15.11:** Add a virtual debug function to your Quote class hierarchy that displays the data members of the respective classes.

```c++
virtual void debug() const {
  std::cout << "Quote: <bookNO: " << bookNo
    << "> <price: " << price << "> " << std::endl;
}

virtual void debug() const {
  std::cout << "Bulk Quote: <bookNO: " << isbn()
    << "> <price: " << price << "> "
    << "<min_qty: " << min_qty
    << "> <discount: " << discount << ">"
    << std::endl;
}

virtual void debug() const {
  std::cout << "Limited Quote: <bookNO: " << isbn()
    << "> <price: " << price << "> "
    << "<max_qty: " << max_qty
    << "> <discount: " << discount << ">"
    << std::endl;
}
```

**Exercise 15.12:** Is it ever useful to declare a member function as both override and final? Why or why not?

```c++
// 没有；final隐含包括了override的含义，所以只声明为final就ok了
```

**Exercise 15.13:** Given the following classes, explain each print function:

```c++
class base {
public:
	string name() { return basename; }
	virtual void print(ostream &os) { os << basename; } 
private:
    string basename;
};

class derived : public base {
public:
	void print(ostream &os) { print(os); os << " " << i; } 
private:
	int i; 
};

---
// infinit loop if call derived::print
// derived中override了基类中继承的虚函数，但是没有显式的指明使用基类的print，导致死循环
```

If there is a problem in this code, how would you fix it?

```c++
// yes
void print(ostream &os) { base::print(os); os << " " << i;}
```


**Exercise 15.14:** Given the classes from the previous exercise and the following objects, determine which function is called at run time:

```c++
base bobj; 
base *bp1 = &bobj; 
base &br1 = bobj; 

derived dobj; 
base *bp2 = &dobj; 
base &br2 = dobj; 

(a) bobj.print(); (b) dobj.print(); (c) bp1->name(); 
(d) bp2->name(); (e) br1.print(); (f) br2.print();

(a) base
(b) derived
(c) base
(d) base
(e) base
(f) derived
```

**Exercise 15.15:** Define your own versions of Disc_quote and Bulk_quote.

```c++
class Disc_Quote : public Quote {
public:
    Disc_Quote() = default;

    Disc_Quote(const std::string &s, double p, std::size_t min, double dis)
            : Quote(s, p), quantity(min), discount(dis) {}

    double net_price(std::size_t n) const =0;

    virtual void debug() const = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_Quote : public Disc_Quote {
public:
    Bulk_Quote() = default;

    Bulk_Quote(const std::string &s, double p, std::size_t min, double dis)
            : Disc_Quote(s, p, min, dis) {}

    double net_price(std::size_t n) const override {
        if (n >= quantity) {
            return price * (1 - discount) * n;
        }
        return price * n;
    }

    virtual void debug() const {
        std::cout << "Bulk Quote: <bookNO: " << isbn()
                  << "> <price: " << price << "> "
                  << "<min_qty: " << quantity
                  << "> <discount: " << discount << ">"
                  << std::endl;
    }
};
```

**Exercise 15.16:** Rewrite the class representing a limited discount strategy, which you wrote for the exercises in § 15.2.2 (p. 601), to inherit from Disc_quote.

```c++
class Limited_Quote : public Disc_Quote {
public:
    Limited_Quote() = default;

    Limited_Quote(const std::string &s, double p, std::size_t max, double dis)
            : Disc_Quote(s, p, max, dis) {}

    double net_price(std::size_t n) const override {
        if (n > quantity) {
            return n * price;
        }
        return n * (1 - discount) * price;
    }

    ~Limited_Quote() = default;

    virtual void debug() const {
        std::cout << "Limited Quote: <bookNO: " << isbn()
                  << "> <price: " << price << "> "
                  << "<max_qty: " << quantity
                  << "> <discount: " << discount << ">"
                  << std::endl;
    }
};
```

**Exercise 15.17:** Try to define an object of type Disc_quote and see what errors youget from the compiler.

```c++
// error: cannot declare variable 'd' to be of abstract type 'Disc_Quote'
```

**Exercise 15.18:** Given the classes from page 612 and page 613, and assuming each object has the type specified in the comments, determine which of these assignments are legal. Explain why those that are illegal aren’t allowed:

```c++
(1) Base *p = &d1; 	// d1 has type Pub_Derv
(2) p = &d2;       	// d2 has type Priv_Derv
(3) p = &d3; 		// d3 has type Prot_Derv
(4) p = &dd1; 		// dd1 has type Derived_from_Public
(5) p = &dd2;  		// dd2 has type Derived_from_Private
(6) p = &dd3;		// dd3 has type Derived_from_Protected

---
(1) public继承，允许派生类到基类的转换
(2) private继承，不允许派生类到基类的转换
(3) protedted继承，不允许派生类到基类的转换
(4) public继承，允许`派生类的派生类`到基类的转换
(5) private继承，不允许`派生类的派生类`到基类的转换
(6) protected继承，不允许`派生类的派生类`到基类的转换

// 编译器给出错误提示是： error: 'lecture::Base' is an inaccessible base of 
```

**Exercise 15.19:** Assume that each of the classes from page 612 and page 613 has a member function of the form:

```c++
void memfcn(Base &b) { b = *this; }

---
// Pub_Derv: legal
// Priv_Derv: legal
// Prot_Derv: legal
// Derived_from_Public: legal
// Derived_from_Private: illegal
// Derived_from_Protected: legal
```

For each class, determine whether this function would be legal.

**Exercise 15.20:** Write code to test your answers to the previous two exercises.

```c++
// 可访问性实验
```

**Exercise 15.21:** Choose one of the following general abstractions containing a familyof types (or choose one of your own). Organize the types into an inheritance hierarchy:

```c++
(a) Graphical file formats(such as gif,tiff,jpeg,bmp)
(b) Geometric primitives(suchasbox,circle,sphere,cone)
(c) C++ language types(suchasclass,function,member function)
```

**Exercise 15.22:** For the class you chose in the previous exercise, identify some of the likely virtual functions as well as public and protected members.

**Exercise 15.23:** Assuming class D1 on page 620 had intended to override its inherited fcn function, how would you fix that class? Assuming you fixed the class so that fcn matched the definition in Base, how would the calls in that section be resolved?

```c++
// int fcn();

// bp2->fcn(); 将在运行时调用D1::fcn
// p2->fcn(42); 错误，D1中没有接受一个int的fcn
```

**Exercise 15.24:** What kinds of classes need a virtual destructor? What operations must a virtual destructor perform?

```c++
// 类派生体系作为基类的类通常需要定义一个虚析构；因为需要时虚函数，所以必须显式定义，即使函数体为空
// 主要目的在与，当基类的指针实际指向一个派生类的时候，delete有正确的行为，虚函数的动态绑定使得调用派生类的
// 析构函数，否则行为未定义；定义了基类的虚析构函数之后，就可以动态分配继承体系中的对象了。
```

**Exercise 15.25:** Why did we define a default constructor for Disc_quote? What effect, if any, would removing that constructor have on the behavior of Bulk_quote?

```c++
// 为了可以使派生类使用默认的构造函数构造派生类对象

// 如果去掉了Disc_quote中的默认构造函数，因为定义了其他构造函数，编译器不会合成默认构造函数
// 那么，则类似Bulk_quote b; 会因为没有没有可用的默认构造函数而失败
// error: no matching function for call to 'Disc_Quote::Disc_Quote()'
```

**Exercise 15.26:** Define the Quote and Bulk_quote copy-control members to do the same job as the synthesized versions. Give them and the other constructors print statements that identify which function is running. Write programs using these classes and predict what objects will be created and destroyed. Compare your predictions with the output and continue experimenting until your predictions are reliably correct.

**Exercise 15.27:** Redefine your Bulk_quote class to inherit its constructors.

```c++
// using Disc_Quote::Disc_Quote;
```

**Exercise 15.28:** Define a vector to hold Quote objects but put Bulk_quote objectsinto that vector. Compute the total net_price of all the elements in the vector.

```c++
// 由于发生了派生类到基类对象的拷贝，会slice down，容器里存放的实际都是Quote类对象
```

**Exercise 15.29:** Repeat your program, but this time store shared_ptrs to objects oftype Quote. Explain any discrepancy in the sum generated by the this version and theprevious program. If there is no discrepancy, explain why there isn’t one.			

```c++
// 由于智能指针的语义类似内置指针，支持指向派生类的shared_ptr隐式转换为指向基类的shard_ptr，所以
// 在计算net_price的时候，虚函数机制会发生作用，根据实际智能指针指向的对象类型，计算总价格
```

**Exercise 15.30:** Write your own version of the Basket class and use it to compute prices for the same transactions as you used in the previous exercises.

```c++
class Basket {
public:
    void add_item(const std::shared_ptr<Quote> &sale) {
        items.insert(sale);
        std::cout << "void add_item(const std::shared_ptr<Quote> &sale) " << std::endl;
    }

    // overloaded add_item
    // copy Quote
    void add_item(const Quote &sale) {
        items.insert(std::shared_ptr<Quote>(sale.clone()));
        std::cout << "void add_item(const Quote &sale) " << std::endl;
    }

    // move Quote
    void add_item(Quote &&sale) {
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
        std::cout << "void add_item(Quote &&sale) " << std::endl;
    }

    double total_receipt(std::ostream &) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs) {
        return lhs->isbn() < rhs->isbn();
    }

    // in-class initialization must use {} or =
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};
```

**Exercise 15.31:** Given that s1, s2, s3, and s4 are all strings, determine what objects are created in the following expressions:

```c++
(a) Query(s1) | Query(s2) & ~ Query(s3);
(b) Query(s1) | (Query(s2) & ~ Query(s3));
(c) (Query(s1) & (Query(s2)) | (Query(s3) & Query(s4)));
```


**Exercise 15.32:** What happens when an object of type Query is copied, moved, as-signed, and destroyed?

**Exercise 15.33:** What about objects of type Query_base?						

**Exercise 15.34:** For the expression built in Figure 15.3 (p. 638):

```c++
(a) List the constructors executed in processing that expression. 
(b) List the calls to rep that are made from cout<<q.
(c) List the calls to eval made from q.eval().
```

**Exercise 15.35:** Implement the Query and Query_base classes, including a defini-tion of rep but omitting the definition of eval.

**Exercise 15.36:** Put print statements in the constructors and rep members and runyour code to check your answers to (a) and (b) from the first exercise.

**Exercise 15.37:** What changes would your classes need if the derived classes hadmembers of type `shared_ptr<Query_base>` rather than of type Query?

**Exercise 15.38:** Are the following declarations legal? If not, why not? If so, explainwhat the declarations mean.

```c++
BinaryQuery a = Query("fiery") & Query("bird"); 
AndQuery b = Query("fiery") & Query("bird"); 
OrQuery c = Query("fiery") & Query("bird");
```


**Exercise 15.39:** Implement the Query and Query_base classes. Test your applicationby evaluating and printing a query such as the one in Figure 15.3 (p. 638).

**Exercise 15.40:** In the OrQuery eval function what would happen if its rhs memberreturned an empty set? What if its lhs member did so? What if both rhs and lhsreturned empty sets?

**Exercise 15.41:** Reimplement your classes to use built-in pointers to Query_base rather than shared_ptrs. Remember that your classes will no longer be able to use the synthesized copy-control members.

**Exercise 15.42:** Design and implement one of the following enhancements:		

```c++
(a) Print words only once per sentence rather than once per line.
(b) Introduce a history system in which the user can refer to a previous query by number, possibly adding to it or combining it with another.
(c) Allow the user to limit the results so that only matches in a given range of lines are displayed.
```

### Notes

- 面向对象程序设计基于三个基本概念：**数据抽象、继承和动态绑定**。*继承*和*动态绑定*对程序的编写有两方面的影响：一是可以更容易地定义与其他类相似但不完全相同的新类；二是在使用这些彼此相似的类编写程序时，可以在一定程度上忽略掉它们的区别。

- **面向对象程序设计（object-oriented programming）的核心思想是数据抽象、继承和动态绑定**。通过使用数据抽象，可以将类的接口与实现分离；使用继承，可以定义相似的类型**并对其相似关系建模**；使用动态绑定，可以在一定程度上忽略相似类型的区别，而以统一的方式使用它们的对象。

  在C++中，当使用基类的引用（指针）调用一个虚函数时将发生**动态绑定**。


- 派生类必须通过使用**类派生列表**（class derivation list）明确指出它是从哪个（哪些）基类继承而来的。**如果一个派生是公有的（public），则基类的公有成员也是派生类接口的组成部分**。此外，我们能将公有派生类型的对象绑定到基类的引用或指针上。
- 派生类可以在它覆盖的函数前使用virtual关键字，但不是非得这么做。**C++新标准允许派生类显式的注明它使用某个成员函数覆盖了它继承的虚函数**，通过override关键字，编译器会检查是否真的覆盖成功。
- 基类通常都应该定义一个虚析构函数，即使该函数不执行任何实际操作也是如此：**其目的在于当delete baseptr的时候，可以正确的析构一个派生类的对象**。
- 一个派生类对象包含多个组成部分：一个含有派生类自己定义的（非静态）成员的子对象，以及一个与该派生类继承的基类对应的子对象，如果有多个基类，那么这样的子对象有多个。**C++标准并没有明确规定派生类的对象在内存中如何分布，所以在一个对象中，继承自基类的部分和派生类自定义的部分不一定是连续存储的**。
- 在派生类中含有与其基类对应的组成部分，这一事实是继承的关键所在，所以可以把**派生类的对象当成基类对象**使用，也能将**基类的指针或引用绑定到派生类对象中的基类部分**上。这种转换通常称为**派生类到基类的类型**转换，和其他类型转换一样，编译器会隐式的执行派生类到基类的转换。
- **除非显式的指出，否则派生类对象的基类部分会像数据成员一样执行默认初始化**。每个类控制它自己的成员初始化过程。首先初始化基类的部分，然后按照声明的顺序依次初始化派生类的成员。
- 基类中的静态成员，在整个继承体系中只存在该成员的唯一定义。
- **一条声明语句的目的是令程序知晓某个名字的存在以及该名字表示一个什么样的实体，如一个类、一个函数或一个变量**。派生列表以及与定义有关的其他细节必须与类的主题一起出现。
- 被用作基类的类，必须已经定义而非仅仅声明：派生类中包含并且可以使用它从基类继承而来的成员，为了使用这些成员，派生类当然要知道它们是什么。因此该规定还有一层隐含的意思，即一个类不能派生它本身。
- **C++11新表准提供了一种防止继承发生的方法，即在类名后跟一个关键字final**。（final和override貌似copy自Java）
- **理解基类和派生类之间的类型转换**是理解C++语言面向对象编程的关键所在。
- 可以将基类指针或引用绑定到派生类对象上有一层极为重要的含义：**当使用基类的引用（或指针）时，实际上我们并不清楚该引用（指针）所绑定对象的真实类型**，可能是基类的对象，也可能是派生类的对象。
- 和内置指针一样，**智能指针类也支持派生类向基类的类型转换，这意味着可以将一个派生类对象的指针存储在一个基类的指针指针内**。（这个就很有用了）


- 不存在从基类到派生类的隐式类型转换，在对象之间不存在类型转换（sliced down）。

  - ```c++
    Quote base;
    Bulk_quote *bulkP = &base;  // error
    Bulk_quote &bulkRef = base; // error
    ```

  - ```c++
    Bulk_quote bulk;
    Quote *itemP = &bulk;
    Bulk_quote *bulkP = itemP;  // error

    // 编译器在编译时无法确定某个特定的转换在运行时是否安全，这是因为编译器只能通过检查指针或引用的静态类
    // 型来推断该转换是否合法。如果在基类中含有一个或多个虚函数，可以使用dynamic_cast请求一个类型转换，
    // 该转换的安全检查将在运行时执行。同样，如果已知某个基类向派生类的转换时安全的，则可以使用
    // static_cast来强制覆盖掉编译器的检查工作。
    ```


- 当用一个派生类对象为一个基类对象初始化或赋值时，只有该派生类对象中的基类部分会被拷贝、移动或赋值，它的派生类部分将被忽略掉。尽管自动类型转换只对指针或引用有效，但是继承体系中的大多数类仍然（显式或隐式地）定义了拷贝控制成员。因此，通常能够将一个派生类对象拷贝、移动、赋值给一个基类对象。不过，这种操作只处理派生类对象的基类部分。
- 引用或指针的静态类型与动态类型不同这一事实正是C++语言支持多态性的**根本原因**。**当且仅当**对通过指针或引用调用虚函数时，才会在运行时解析该调用，也**只有在这种情况下**对象的动态类型才有可能与静态类型不同。
- <u>一旦某个函数被声明成虚函数，则在所有派生类中它都是虚函数</u>。一个派生类的函数如果override了**某个继承而来**的虚函数，则它的形参类型和返回类型必须与被它覆盖的基类函数完全一致。一个例外是，**如果基类的虚函数的返回类型时类本身的指针或引用时**，上述规则无效。
- **使用作用域运算符可以使得对虚函数的调用不要进行动态绑定，而是强迫其执行虚函数的某个特定版本**。


- 含有纯虚函数的类是**抽象基类**。抽象基类负责定义接口，后续的其他类可以覆盖该接口，**不能直接创建一个抽象街垒的对象**。
- **每个类分别控制自己的成员初始化过程**，还分别控制着其成员对于派生类来说是否**可访问（accessible）**。
  - 派生类的成员或友元**只能通过派生类对象**来访问基类的protected成员**。派生类对**于一个基类对象中protected成员没有任何访问特权。


- 某个类对其继承而来的成员的访问权限受到两个因素的影响：*一是在基类中该成员的访问说明符*，<u>二是在派生类的派生列表中的访问说明符</u>。
  - 派生访问说明符对于派生类的成员（及友元）能否访问其直接基类的成员没有影响，对基类成员的访问权限只与基类中的访问说明符有关。
  - 派生类访问说明符的目的是控制派生类用户（包括派生类的派生类在内）对于基类成员的访问权限。


- 派生类向基类转换的可访问性由<u>使用该转换的代码决定</u>，同时派生类的派生访问说明符也会有影响。假设D继承自B：
  - 只有当D公有继承B时，用户代码才能使用派生类像基类的转换；如果D继承B的方式是protected或者private的，则用户代码不能使用该转换。
  - 不论D继承B的方式如何，D的成员函数和友元都能使用派生类向基类的转换；派生类向其**直接基类**的类型转换对于**派生类的成员和友元来说永远是可访问的**。
  - 如果D继承B的方式是public或者protected的，则**D的派生类的**成员和友元可以使用D向B的转换；如果D继承B的方式是私有的，则不能使用。
  - Summary：**对于代码中的某个给定节点来说，如果基类的公有成员时可访问的，则派生类向基类的类型转换也是可访问的**，否则不行。


- **不能继承友元关系**（*具体到某一个类，而不是类的继承体系*）；每个类负责控制各自成员的访问权限，**即使该对象内嵌在其派生类对象中的情况**。
- 派生类只能为那些它可以访问的名字提供using声明。
- struct和class的差别：**唯一的**差别就是默认成员访问说明符以及默认派生访问说明符，struct是public的，class是private的。


- 每个类定义自己的作用域，当存在继承关系时，**派生类的作用域嵌套在其基类的作用域之内**。
- 一个对象、引用或指针的静态类型决定了该对象的哪些成员是可见的。即使静态类型与动态类型可能不一致，但是能使用哪些成员仍然是由静态类型决定的。
- **派生类的成员将隐藏同名的基类成员**，可以通过作用域操作符来使用隐藏的成员。
- C++中，名字查找先于类型检查。


- 成员函数无论是否是虚函数都能被重载。派生类可以覆盖重载函数的0个或多个实例。一条基类成员函数的using声明就可以把该函数的所有重载实例添加到派生类作用域中。


- **如果基类的析构函数不是虚函数，则delete一个指向派生类对象的基类指针将产生未定义的行为**。只要基类的析构函数是虚函数，就能确保当delete基类指针时将运行正确的析构函数版本。
- **虚析构函数将阻止合成移动操作**。如果一个类定义了析构函数，即使它通过=default的形式使用了合成的版本，编译器也不会为这个类合成移动操作。


- 实际编程过程中，如果基类中没有默认、拷贝或移动构造函数，则一般情况下派生类也不会定义相应的操作。


- 当派生类定义了拷贝或移动操作时，该操作负责拷贝和移动包括基类部分在内的整个对象，不同的是，析构函数只负责销毁派生类自己分配的资源，对象的成员是被隐式销毁的，派生类对象的基类部分也是自动销毁的。
- 在默认情况下，**基类默认构造函数初始化派生类对象的基类部分**。如果我们想拷贝（或移动）基类部分，则必须在派生类的构造函数列表中显式地使用基类的拷贝（或移动）构造函数。


- 与拷贝和移动构造一样，派生类的赋值运算符也**必须显式地为其基类部分赋值**，基类的赋值运算符不会自动被调用，而基类的构造函数和赋值运算符是自定义的版本还是合成版本无关紧要。
- **如果构造函数或析构函数中调用了某个虚函数，则我们应该执行与构造函数或析构函数所属类型相对应的虚函数版本**。 


- 通常情况下，using声明语句只是令某个名字在当前作用域内可见。而当作用域构造函数时，using声明语句将令编译器产生代码，对于基类的每个构造函数，编译器都生成一个与之对应的派生类构造函数。换句话说，对于基类的每个构造函数，编译器都在派生类中生成一个形参列表完全相同的构造函数。如果派生类含有自己的数据成员，则这些成员将被默认初始化。一个类只能初始化它的直接基类，出于同样的原因，一个类也只继承其直接基类的构造函数。类不能继承默认、拷贝和移动构造函数。`derived(params) : base(args) {}`


- 继承的构造函数：一个构造函数的using声明不会改变该构造函数的访问级别，而且也不能指定explicit或constexpr，继承的构造函数拥有和基类相同的属性。


- **对于C++面向对象来说，一个悖论是我们无法直接使用对象进行面向对象编程。相反，必须使用指针和引用**。