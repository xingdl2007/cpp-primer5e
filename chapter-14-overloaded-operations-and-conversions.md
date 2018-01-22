# Chapter 14 Overloaded Operations and Conversions

**Exercise 14.1:** In what ways does an overloaded operator differ from a built-in opera-tor? In what ways are overloaded operators the same as the built-in operators?

```c++
// 区别：重载运算符本质是函数调用，对于定义了求值顺序(逗号，逻辑与、逻辑或)的运算符，重载版本无法保留。
// 相同：要求的运算对象个数，优先级和结合律和内置版本一致
// 另外，无法重载语言中不存在的运算符，e.g. **
```

**Exercise 14.2:** Write declarations for the overloaded input, output, addition, and compound-assignment operators for Sales_data.

```c++
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;  // copy data members from lhs into sum
    sum.combine(rhs);      // add data members from rhs into sum
    return sum;
}

// transactions contain ISBN, number of copies sold, and sales price
istream &operator>>(istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &operator<<(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}
```

**Exercise 14.3:** Both string and vector define an overloaded == that can be used to compare objects of those types. Assuming svec1 and svec2 are vectors that hold strings, identify which version of == is applied in each of the following expressions:

```c++
(a) "cobble" == "stone" 
(b) svec1[0] == svec2[0] 
(c) svec1 == svec2 
(d) "svec1[0] == "stone"
  
---
(a) 字符串字面值比较，使用针对const char*的版本，如果没有可能隐式转换为string，使用为string定义的==。
(b) string定义的==
(c) vector定义的==，元素比较时还会使用string定义的==
(d) string定义的==
```

**Exercise 14.4:** Explain how to decide whether the following should be class members:

```c++
(a)% (b)%= (c)++ (d)-> (e)<< (f)&& (g)== (h)()

---
(a) 由于可能交互运算对象，应该定义为普通函数
(b) 复合赋值一般定义为成员函数
(c) 递增++一般定义为成员函数
(d) 成员访问必须定义为成员函数
(e) 移位运算符重载为IO时，定义为普通函数
(f) 一般不重载，如果要重载应该定义为普通函数
(g) 一般不重载，如果要重载应该定义为普通函数
(h) 调用运算符必须定义为成员函数
```

**Exercise 14.5:** In exercise 7.40 from § 7.5.1 (p. 291) you wrote a sketch of one of the following classes. Decide what, if any, overloaded operators your class should provide.

```c++
(a) Book (b) Date (c) Employee (d) Vehicle (e) Object (f) Tree
```

**Exercise 14.6:** Define an output operator for your Sales_data class.

```c++
ostream &operator<<(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}
```

**Exercise 14.7:** Define an output operator for you String class you wrote for the exercises in § 13.5 (p. 531).

```c++
std::ostream &operator<<(std::ostream &out, const String &s) {
    if (s.element) {
        auto it = s.element;
        while (it != s.first_free) {
            out << *it++;
        }
    }
    return out;
}
```

**Exercise 14.8:** Define an output operator for the class you chose in exercise 7.40 from§ 7.5.1 (p. 291).

**Exercise 14.9:** Define an input operator for your Sales_data class.

```c++
// transactions contain ISBN, number of copies sold, and sales price
istream &operator>>(istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
  	if (is) item.revenue = price * item.units_sold;
  	else item = Sales_data();
    return is;
}
```

**Exercise 14.10:** Describe the behavior of the Sales_data input operator if given the following input:

```c++
(a) 0-201-99999-9 10 24.95 (b) 10 24.95 0-210-99999-9
  
---
(a) 输入流不会遇到错误
(b) 估计：输入流出错，对象被使用默认构造函数的临时对象赋值；实际：测试输入流cin没有出错，会进行类型转换。
```

**Exercise 14.11:** What, if anything, is wrong with the following Sales_data input operator? What would happen if we gave this operator the data in the previous exercise?

```c++
istream& operator>>(istream& in, Sales_data& s) {
	double price;
	in >> s.bookNo >> s.units_sold >> price; 
  	s.revenue = s.units_sold * price; return in;
}

---
10 24.95 0-210-99999-9
10 24 22.8 0.95
```

**Exercise 14.12:** Define an input operator for the class you used in exercise 7.40 from § 7.5.1 (p. 291). Be sure the operator handles input errors.

**Exercise 14.13:** Which other arithmetic operators (Table 4.1 (p. 139)), if any, do youthink Sales_data ought to support? Define any you think the class should include.

```c++
// 好像没有了
```

**Exercise 14.14:** Why do you think it is more efficient to define operator+ to call operator+= rather than the other way around?

```c++
// 可以使用已经定义的函数，显然更方便
```

**Exercise 14.15:** Should the class you chose for exercise 7.40 from § 7.5.1 (p. 291) defineany of the arithmetic operators? If so, implement them. If not, explain why not.

```c++

```

**Exercise 14.16:** Define equality and inequality operators for your StrBlob (§ 12.1.1,p. 456), StrBlobPtr (§ 12.1.6, p. 474), StrVec (§ 13.5, p. 526), and String (§ 13.5,p. 531) classes.

**Exercise 14.17:** Should the class you chose for exercise 7.40 from § 7.5.1 (p. 291) definethe equality operators? If so, implement them. If not, explain why not.

**Exercise 14.18:** Define relational operators for your StrBlob, StrBlobPtr, StrVec,and String classes.

**Exercise 14.19:** Should the class you chose for exercise 7.40 from § 7.5.1 (p. 291) definethe relational operators? If so, implement them. If not, explain why not.

**Exercise 14.20:** Define the addition and compound-assignment operators for yourSales_data class.

**Exercise 14.21:** Write the Sales_data operators so that + does the actual additionand += calls +. Discuss the disadvantages of this approach compared to the way these operators were defined in § 14.3 (p. 560) and § 14.4 (p. 564).

```c++
// 如果定义+做实际的工作，+=调用+，效率不高
// +返回值是一个新的类，+=对+的使用，需要临时对象参与赋值；翻过来如果实现+=做实际的工作，效率高些
```

**Exercise 14.22:** Define a version of the assignment operator that can assign a string representing an ISBN to a Sales_data.

```c++
Sales_data &Sales_data::operator=(const std::string &s) {
    bookNo = s;
    units_sold = 0;
    revenue = 0;
    return *this;
}
```

**Exercise 14.23:** Define an initializer_list assignment operator for your versionof the StrVec class.

**Exercise 14.24:** Decide whether the class you used in exercise 7.40 from § 7.5.1 (p. 291)needs a copy- and move-assignment operator. If so, define those operators.

**Exercise 14.25:** Implement any other assignment operators your class should define.Explain which types should be used as operands and why.

**Exercise 14.26:** Define subscript operators for your StrVec, String, StrBlob, and StrBlobPtr classes.

**Exercise 14.27:** Add increment and decrement operators to your StrBlobPtr class.

**Exercise 14.28:** Define addition and subtraction for StrBlobPtr so that these operators implement pointer arithmetic (§ 3.5.3, p. 119).

**Exercise 14.29:** We did not define a const version of the increment and decrement operators. Why not?

**Exercise 14.30:** Add dereference and arrow operators to your StrBlobPtr class andto the ConstStrBlobPtr class that you defined in exercise 12.22 from § 12.1.6 (p. 476).Note that the operators in constStrBlobPtr must return const references becausethe data member in constStrBlobPtr points to a const vector.

**Exercise 14.31:** Our StrBlobPtr class does not define the copy constructor, assign-ment operator, or a destructor. Why is that okay?

**Exercise 14.32:** Define a class that holds a pointer to a StrBlobPtr. Define the over-loaded arrow operator for that class.

**Exercise 14.33:** How many operands may an overloaded function-call operator take?

**Exercise 14.34:** Define a function-object class to perform an if-then-else operation: Thecall operator for this class should take three parameters. It should test its first parame-ter and if that test succeeds, it should return its second parameter; otherwise, it shouldreturn its third parameter.

**Exercise 14.35:** Write a class like PrintString that reads a line of input from anistream and returns a string representing what was read. If the read fails, returnthe empty string.

**Exercise 14.36:** Use the class from the previous exercise to read the standard input,storing each line as an element in a vector.

**Exercise 14.37:** Write a class that tests whether two values are equal. Use that objectand the library algorithms to write a program to replace all instances of a given valuein a sequence.

**Exercise 14.38:** Write a class that tests whether the length of a given string matchesa given bound. Use that object to write a program to report how many words in aninput file are of sizes 1 through 10 inclusive.

**Exercise 14.39:** Revise the previous program to report the count of words that are sizes1 through 9 and 10 or more.

**Exercise 14.40:** Rewrite the biggies function from § 10.3.2 (p. 391) to use function-object classes in place of lambdas.

**Exercise 14.41:** Why do you suppose the new standard added lambdas? Explainwhen you would use a lambda and when you would write a class instead.

**Exercise 14.42:** Using library function objects and adaptors, define an expression to

```c++
(a) Count the number of values that are greater than 1024 
(b) Find the first string that is not equal to pooh
(c) Multiply all values by 2
```

**Exercise 14.43:** Using library function objects, determine whether a given int value is divisible by any element in a container of ints.

**Exercise 14.44:** Write your own version of a simple desk calculator that can handle binary operations.


**Exercise 14.45:** Write conversion operators to convert a Sales_data to string andto double. What values do you think these operators should return?

**Exercise 14.46:** Explain whether defining these Sales_data conversion operators isa good idea and whether they should be explicit.

**Exercise 14.47:** Explain the difference between these two conversion operators:

```c++
struct Integral {
       operator const int();
       operator int() const;
};		
```

**Exercise 14.48:** Determine whether the class you used in exercise 7.40 from § 7.5.1(p. 291) should have a conversion to bool. If so, explain why, and explain whether theoperator should be explicit. If not, explain why not.

**Exercise 14.49:** Regardless of whether it is a good idea to do so, define a conversionto bool for the class from the previous exercise.

**Exercise 14.50:** Show the possible class-type conversion sequences for the initializations of ex1 and ex2. Explain whether the initializations are legal or not.

```c++
struct LongDouble { 
	LongDouble(double = 0.0); 
	operator double(); 
	operator float();
};
LongDouble ldObj;
int ex1 = ldObj;
float ex2 = ldObj;
```

**Exercise 14.51:** Show the conversion sequences (if any) needed to call each version of calc and explain why the best viable function is selected.

```c++
void calc(int);
void calc(LongDouble); 
double dval; 
calc(dval);// which calc?				
```

**Exercise 14.52:** Which `operator+`, if any, is selected for each of the addition expressions? List the candidate functions, the viable functions, and the type conversions on the arguments for each viable function:

```c++
struct LongDouble {
	// memberoperator+forillustrationpurposes;+isusuallyanonmember 
  	LongDouble operator+(const SmallInt&);
	// other members as in § 14.9.2 (p. 587)
};
LongDouble operator+(LongDouble&, double); SmallInt si;
LongDouble ld;
ld = si + ld;
ld = ld + si;
```

**Exercise 14.53:** Given the definition of SmallInt on page 588, determine whether the following addition expression is legal. If so, what addition operator is used? If not, how might you change the code to make it legal?

```c++
SmallInt s1;
double d = s1 + 3.14;
```

### Notes

- 当运算符被用于类类型的对象时，C++语言允许我们为其指定新的含义；同时，也能自定义类类型之间的转换规则。和内置类型的转换一样，类类型转换隐式的将一种类型的对象转换为另一种所需类型的对象。

- <u>当运算符作用于类类型的运算对象时，可以通过运算符重载重新定义该运算符的含义</u>。明智的使用运算符重载能令程序更易于编写和阅读。

- 重载的运算符是<u>具有特殊名字的函数</u>。<u>除了重载的调用运算符operator()外，其他重载运算符不能含有默认实参</u>。

- 运算符函数或者是类的成员，或者至少含有一个类类型的参数（因此运算符重载无法作用于内置类型）；对于重载的运算符，其优先级和结合律与对应的内置运算符保持一致。

- ```c++
  e.g. error: 'int operator+(int, int)' must have an argument of class or enumerated type
  ```

- 通常情况，将运算符作用于类型正确的实参，从而以这种间接方式调用重载的运算符函数。然而，也可以像普通函数一样直接调用运算符函数。
- 使用重载的运算符<u>本质上是一次函数调用</u>，所以关于运算对象求值顺序的规则无法应用到重载的运算符上。特别是，<u>逻辑与、逻辑或和逗号运算符</u>的运算对象求值顺序规则无法保留下来。&&和||运算符的重载版本也无法保留内置的运算符的<u>短路求值属性，两个运算对象总是会被求值</u>。还有一个原因使得一般不重载逗号和取地址运算符：C++语言已经定义了这两种运算符作用于类类型的特殊含义（**什么特殊含义**？&应该是用来表示引用了，那么逗号呢？）。


- <u>通常情况下，不应该重载逗号、取地址、逻辑与和逻辑或运算符</u>。
- 重载运算符的返回类型通常应该与内置版本的返回类型兼容：<u>逻辑运算符和关系运算符应该返回bool，算术运算符应该返回一个类类型的值（新创建的对象），赋值运算符和复合赋值运算符应该返回左侧运算对象的一个引用（方便连接多个动作）</u>。


- 选择作为成员或非成员函数
  - 赋值（=）、下标（[ ]）、调用（()）和成员访问箭头（—>）运算符必须是成员（*感觉和语言实现特别是类的相关，所以必须是成员函数*）。
  - 复合赋值运算符一般来说应该是成员，但并非必须，这一点与赋值运算符略有不同。
  - 改变对象状态的运算符或者与给定类型密切相关的运算符，如递增、递减和解引用运算符，通常应该是成员。
  - 具有对称性的运算符可能转换任意一端的运算对象，例如算术、相等性、关系和位运算符等等，因此它们通常应该是普通的非成员函数。<u>当把一个运算符定义为成员函数时，它的左侧运算对象必须是运算符所属类的一个对象</u>，**而这会限制类对象的使用场景**，特别是可以交换运算对象的运算符中，所以对这种运算符（一般是二元运算符）定义为普通的函数。


- 如果为类定义IO运算符，则其<u>必须是非成员函数</u>，IO运算符通常要读写类的非公有数据成员，所以IO运算符一般声明为友元。


- 输入运算符必须处理输入可能失败的情况，而输出运算符不需要。


- <u>如果一个类在逻辑上有相等性的含义，则该类应该定义operator==</u>。


- 如果存在唯一一种逻辑可靠的<定义，则应该考虑为这个类定义<运算符。如果类同时还包含`==`，则当且仅当<的定义和`==`产生的结果一致时才定义<运算符。


- <u>如果一个类包含下标运算符，则它通常会定义两个版本：一个返回普通引用，另一个是类的常量成员并返回常量引用</u>。

