# Chapter 3 Strings, Vectors, and Arrays

**Exercise 3.1:** Rewrite the exercises from § 1.4.1 (p. 13) and § 2.6.2 (p. 76) with appropriate using declarations.

```c++
using std::cin;  using std::cout;
using std::endl; using std::cerr;

// ...
```

**Exercise 3.2:** Write a program to read the standard input a line at a time. Modify your program to read a word at a time.

```c++
// read a line a time
void readLine() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << std::endl;
    }
}

// read a word a time
void readWord() {
    std::string word;
    while (std::cin >> word) {
        std::cout << word << std::endl;
    }
}
```

**Exercise 3.3:** Explain how whitespace characters are handled in the *string input operator* and in the *getline* function.

```c++
// std::cin >> string：string类型定义的重载输入运算符会会忽略开始的空白符(即空格符、换行符、制表符等)并从第一个真正的字符开始读起，知道遇到下一处空白为止。

// getline：不会忽略开始的空白符，会一直直到遇到换行符，其中换行符也读入但不会存入string对象，而是丢弃掉。如果第一个遇到的字符就是换行符，则string为空。
```

**Exercise 3.4:** Write a program to read two strings and report whether the strings are equal. If not, report which of the two is larger. Now, change the program to report whether the strings have the same length, and if not, report which is longer.

```c++
// compare two string, report which is bigger
void compare1() {
    std::string item1, item2;
    std::cin >> item1 >> item2;
    if (std::cin) {
        if (item1 < item2) {
            std::cout << item2 << std::endl;
        } else {
            std::cout << item1 << std::endl;
        }
    }
}

// compare two string, report which is longer
void compare2() {
    std::string item1, item2;
    std::cin >> item1 >> item2;
    if (std::cin) {
        if (item1.size() < item2.size()) {
            std::cout << item2 << std::endl;
        } else {
            std::cout << item1 << std::endl;
        }
    }
}
```

**Exercise 3.5:** Write a program to read strings from the standard input, concatenat-ing what is read into one large string. Print the concatenated string. Next, changethe program to separate adjacent input strings by a space.

```c++
void concatenate() {
    std::string word, line;
    while (std::cin >> word) {
        line += word;
    }
    std::cout << line << std::endl;
}

void concatenate2() {
    std::string word, line;
    while (std::cin >> word) {
        line += word + " ";
    }
    std::cout << line << std::endl;
}
```

**Exercise 3.6:** Use a range for to change all the characters in a string to X.

```c++
#include <iostream>
int main() {
    std::string some("hello world.");
    for (auto &c:some) {
        c = 'X';
    }
    std::cout << some << std::endl;
    return 0;
}
```

**Exercise 3.7:** What would happen if you define the loop control variable in the previous exercise as type char? Predict the results and then change your program to use a char to see if you were right.

```c++
// 使用auto推断得到的类型就是char，所以手动改成char也是正确的。
```

**Exercise 3.8:** Rewrite the program in the first exercise, first using a while and again using a traditional for loop. Which of the three approaches do you prefer and why?

```c++
// 显然是range for
```

**Exercise 3.9:** What does the following program do? Is it valid? If not, why not?

```c++
string s;
cout << s[0] << endl;

---
// 输出string s中的第一个字符
// 语法上讲是合法的，但是应该始终检查索引在[0,s.size())内。
// 因为其结果是未定义的，所以并不一定会导致程序崩溃。
```

**Exercise 3.10:** Write a program that reads a string of characters including punctuationand writes what was read but with the punctuation removed.

```c++
// homework: 3.10
std::string original, output;
std::cin >> original;
if (std::cin) {
  for (const auto &c:original) {
    if (!std::ispunct(c)) {
      output += c;
    }
  }
}
std::cout << output << std::endl;
```

**Exercise 3.11:** Is the following range for <u>legal</u>? If so, what is the type of c?

```c++
const string s = "Keep out!"; 
for(auto &c:s){/* ... */}

---
legal: const char &
  
// 这里是有些迷惑的，可以重新查阅第二章的auto部分章节：当auto修饰引用(&)时，顶层const保留，其实类似于指针，当给初值绑定引用或者取初始值地址(指针)时，初始值的顶层const就变成了底层const了。所以看起来const是保留了下来。
```

**Exercise 3.12:** Which, if any, of the following vector definitions are in error? For those that are legal, explain what the definition does. For those that are not legal, explain why they are illegal.

```c++
(a) vector<vector<int>> ivec;
(b) vector<string> svec = ivec;
(c) vector<string> svec(10, "null");

---
(a) legal
(b) illegal: 类型不匹配
(c) legal
```

**Exercise 3.13:** How many elements are there in each of the following vectors? What are the values of the elements?				

```c++
(a) vector<int> v1;
(b) vector<int> v2(10);
(c) vector<int> v3(10, 42);
(d) vector<int> v4{10};
(e) vector<int> v5{10, 42};
(f) vector<string> v6{10};
(g) vector<string> v7{10, "hi"};

---
(a) 0
(b) 10, 元素的值都为0
(c) 10, 元素的值都为42
(d) 1,  元素的值为10
(e) 2,  元素的值分别为10,42
(f) 10, 元素的值均为空字符串
(g) 10, 元素的值均为"hi"
  
 // ()在初始化总是指容量，{}只有在无法作为值初始化时才会作为容量使用，优先作为初始化的值。
```

**Exercise 3.14:** Write a program to read a sequence of ints from cin and store those values in a vector.

```c++
vector<int> vec;
	int num;
    while (cin >> num) {
        vec.push_back(num);
}
```

**Exercise 3.15:** Repeat the previous program but read strings this time.

```c++
vector<string> vec;
    string str;
    while (cin >> str) {
        vec.push_back(str);
}
```

**Exercise 3.16:** Write a program to print the size and contents of the vectors from exercise 3.13. Check whether your answers to that exercise were correct. If not, restudy§ 3.3.1 (p. 97) until you understand why you were wrong.

```c++
// right
```

**Exercise 3.17:** Read a sequence of words from cin and store the values a vector. Af-ter you’ve read all the words, process the vector and change each word to uppercase.Print the transformed elements, eight words to a line.

```c++
void toupper(string &str) {
    for (auto &c:str) {
        c = std::toupper(c);
    }
}

void homework317() {
    vector<string> vec;
    string str;
    while (cin >> str) {
        toupper(str);
        vec.push_back(str);
    }
    for (const string &s:vec) {
        cout << s << endl;
    }
}
```

**Exercise 3.18:** Is the following program legal? If not, how might you fix it?

```c++
vector<int> ivec;
ivec[0] = 42;

---
illegal
fix: vector<int> ivec{42};
```

**Exercise 3.19:** List three ways to define a vector and give it ten elements, each with the value 42. Indicate whether there is a preferred way to do so and why.

```c++
vector<int> ivec(10,42);
vector<int> ivec{42,42,42,42,42,42,42,42,42,42};
// for loop with push_back...

// 第一种是最佳的，代码简洁效率高。
```

**Exercise 3.20:** Read a set of integers into a vector. Print the sum of each pair ofadjacent elements. Change your program so that it prints the sum of the first and lastelements, followed by the sum of the second and second-to-last, and so on.

```c++
vector<int> vec;
int num;
while (cin >> num) {
    vec.push_back(num);
}
for (decltype(vec.size()) i = 0; i != vec.size() - 1; i++) {
    cout << vec[i] + vec[i + 1] << endl;
}
cout << endl;
for (decltype(vec.size()) i = 0; i != vec.size() / 2; i++) {
    cout << vec[i] + vec[vec.size() - i - 1] << endl;
}
if (vec.size() % 2 != 0) {
    cout << vec[vec.size() / 2] * 2 << endl;
}
```

**Exercise 3.21:** Redo the first exercise from § 3.3.3 (p. 105) using iterators.

```c++
for (auto it = v7.cbegin(); it != v7.cend(); ++it) {
	cout << *it << endl;
}
```

**Exercise 3.22:** Revise the loop that printed the first paragraph in text to instead change the elements in text that correspond to the first paragraph to all uppercase. After you’ve updated text, print its contents.

```c++
std::vector<std::string> text = {"hello world", "what's wrong?", "", "hi!"};
for (auto it = text.begin(); it != text.end() && !it->empty(); ++it) {
    if (it == text.begin()) {
        for (auto &c:*it) {
            c = std::toupper(c);
        }
    }
	std::cout << *it << std::endl;
}
```

**Exercise 3.23:** Write a program to create a vector with ten int elements. Using aniterator, assign each element a value that is twice its current value. Test your programby printing the vector.

```c++
std::vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
for (auto it = ivec.begin(); it != ivec.end(); ++it) {
    *it += *it;
}

for (auto i:ivec) {
    std::cout << i << std::endl;
}
```

**Exercise 3.24:** Redo the last exercise from § 3.3.3 (p. 105) using iterators.

```c++
int num;
std::vector<int> vec;
while (std::cin >> num) {
    vec.push_back(num);
}

for (auto it = vec.cbegin(); it != vec.cend() - 1; ++it) {
    std::cout << *it + *(it + 1) << std::endl;
}

std::cout << std::endl;
for (auto it = vec.cbegin(); it != vec.cbegin() + vec.size() / 2; ++it) {
    std::cout << *it + *(vec.cbegin() + (vec.cend() - it - 1)) << std::endl;
}
if ((vec.cend() - vec.cbegin()) % 2 != 0) {
    std::cout << (*(vec.cbegin() + vec.size() / 2)) * 2 << std::endl;
}
```

**Exercise 3.25:** Rewrite the grade clustering program from § 3.3.3 (p. 104) using iterators instead of subscripts.

```c++
std::vector<int> grade{23, 43, 67, 89, 99, 100, 62, 92, 99, 44};
std::vector<int> level(11, 0);

for (auto it = grade.cbegin(); it != grade.cend(); ++it) {
  ++level[*it / 10];
}

for (const auto &l:level) {
  std::cout << l << " ";
}
std::cout << std::endl;
```

**Exercise 3.26:** In the binary search program on page 112, why did we write `mid = beg+(end-beg)/2;`instead of `mid=(beg+end)/2;`?

```c++
// 因为迭代器没有重载+操作符；因此两个迭代器相加是没有意义的。
```

**Exercise 3.27:** Assuming txt_size is a function that takes no arguments and returns an int value, which of the following definitions are illegal? Explain why.

```c++
unsigned buf_size = 1024;
(a) int ia[buf_size];   (b) int ia[4 * 7 - 14];
(c) int ia[txt_size()]; (d) char st[11] = "fundamental";

---
(a) illegal: 按照书上讲的是不合法，buf_size不是常量表达式(constexpr)
(b) legal
(c) illegal: 当txt_size()是constexpr时正确；否则错误
(d) illegal: error: initializer-string for array of chars is too long
```


**Exercise 3.28:** What are the values in the following arrays?

```c++
string sa[10];
int ia[10];
int main() {
    string sa2[10];
    int    ia2[10];
}

---
sa : empty string
ia : 0
sa2: empty string
ia2: uninitialized 

// 默认情况下，数组的元素被默认初始化。和内置类型的变量一样，如果在函数体内定义了某种内置类型的数组，那么默认初始化会令数组含有未定义的值。
```

**Exercise 3.29:** List some of the drawbacks of using an array instead of a vector.

```c++
// 定义数组时必须指定数组的大小，因此数组容量固定，无法在运行时扩展；
// vector可以动态增长和收缩，使用更加灵活；

// 数组不允许拷贝和赋值
```

**Exercise 3.30:** Identify the indexing errors in the following code:

```c++
constexpr size_t array_size = 10;
int ia[array_size];
for (size_t ix = 1; ix <= array_size; ++ix)
	ia[ix] = ix;

---
// 数组下标越界
for (size_t ix = 0; ix < array_size; ++ix)
	ia[ix] = ix;
```

**Exercise 3.31:** Write a program to define an array of ten ints. Give each element the same value as its position in the array.

```c++
int array[10];
for (std::size_t i = 0; i < 10; ++i) {
    array[i] = i;
}

for (auto i:array) {
    std::cout << i << " ";
}
std::cout << std::endl;
```

**Exercise 3.32:** Copy the array you defined in the previous exercise into another array. Rewrite your program to use vectors.

```c++
int copy[10];
for (std::size_t i = 0; i < 10; ++i) {
	copy[i] = array[i];
}

// vector: copy(array)
```

**Exercise 3.33:** What would happen if we did not initialize the scores array in the program on page 116?

```c++
// 由于是在函数内部定义的数组，默认初始化，其初值不一定是0，导致计算错误。
```

**Exercise 3.34:** Given that p1 and p2 point to elements in the same array, what does the following code do? Are there values of p1 or p2 that make this code illegal?

```c++
p1 += p2 - p1;

---
// 将p1移动到p2
// illegal? When and Why? p2 is off-the-end?
// 尾后指针不能执行解引用和递增操作。所以除非p2是尾后指针，执行后对p1进行了解引用操作。
```

**Exercise 3.35:** Using pointers, write a program to set the elements in an array to zero.

```c++
int array[] = {1, 2, 3, 4};
for (auto it = std::begin(array); it != std::end(array); ++it) {
	*it = 0;
}
```

**Exercise 3.36:** Write a program to compare two arrays for equality. Write a similar program to compare two vectors.

```c++
int array1[] = {1, 2, 3, 4};
int array2[] = {4, 3, 2, 1};
std::size_t len1 = sizeof(array1) / sizeof(array1[0]);
std::size_t len2 = sizeof(array2) / sizeof(array1[0]);
if (len1 != len2) {
    return false;
}
for (std::size_t i = 0; i < len1; ++i) {
    if (array1[i] != array2[i]) {
        return false;
    }
}
return true;

// vector: vec1 == vec2
std::vector<int> vec1{1, 2, 3, 4};
std::vector<int> vec2{4, 3, 2, 1};
return vec1 == vec2;		
```

**Exercise 3.37:** What does the following program do?

```c++
const char ca[] = {’h’, ’e’, ’l’, ’l’, ’o’}; 
const char *cp = ca;
while (*cp) {
	cout << *cp << endl;
	++cp; 
}

---
// 程序的意图是输出hello，但是由于没有'\0'结尾，所以输出的内容会从'h'开始，直到遇到空字符'\0'为止。
```

**Exercise 3.38:** In this section, we noted that it was not only illegal but meaningless totry to add two pointers. Why would adding two pointers be meaningless?

```c++
// 指针是地址值，两个指针相加就是两个地址值相加，没有意义。
```

**Exercise 3.39:** Write a program to compare two strings. Now write a program to compare the values of two C-style character strings.

**Exercise 3.40:** Write a program to define two character arrays initialized from stringliterals. Now define a third character array to hold the concatenation of the two arrays. Use strcpy and strcat to copy the two arrays into the third.

**Exercise 3.41:** Write a program to initialize a vector from an array of ints.

```c++
int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
std::vector<int> ivec(std::begin(array), std::end(array));
for (auto i:ivec) {
    std::cout << i << " ";
}
std::cout << std::endl;
```

**Exercise 3.42:** Write a program to copy a vector of ints into an array of ints.

```c++
std::vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// really good, array length can be non-constexpr
int array[ivec.size()];

for (decltype(ivec.size()) i = 0; i < ivec.size(); i++) {
	array[i] = ivec[i];
}
for (auto i:array) {
	std::cout << i << " ";
}
std::cout << std::endl;
```

**Exercise 3.43:** Write three different versions of a program to print the elements of ia.One version should use a range for to manage the iteration, the other two should usean ordinary for loop in one case using subscripts and in the other using pointers. Inall three programs write all the types directly. That is, do not use a type alias, auto, ordecltype to simplify the code.

```c++
const int row = 3, columen = 4;
int multi[row][columen] = {{1, 2,  3,  4},
                           {5, 6,  7,  8},
                           {9, 10, 11, 12}
};

std::cout << "method 1: range for" << std::endl;
for (int(&p)[columen] :multi) {
    for (int i:p) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

std::cout << "\nmethod 2: general for with index" << std::endl;
for (int i = 0; i < row; i++) {
    for (int j = 0; j < columen; j++) {
        std::cout << multi[i][j] << " ";
    }
    std::cout << std::endl;
}

std::cout << "\nmethod 3: general for with pointer" << std::endl;
for (int (*p)[columen] = multi; p != multi + 3; ++p) {
    for (int *q = *p; q != *p + 4; ++q) {
        std::cout << *q << " ";
    }
    std::cout << std::endl;
}
```

**Exercise 3.44:** Rewrite the programs from the previous exercises using a type alias for the type of the loop control variables.

```c++
// define some useful type
// 也可以定义int[4]的类型别名，像书上那样
using ref = int (&)[columen];     //typedef int (&ref)[4];
using pointer = int (*)[columen]; //typedef int(*pointer)[4];

std::cout << "method 4: range for with type alias" << std::endl;
for (ref p :multi) {
    for (int i:p) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

std::cout << "\nmethod 5: general for with pointer with type alias" << std::endl;
for (pointer p = multi; p != multi + 3; ++p) {
    for (int *q = *p; q != *p + 4; ++q) {
        std::cout << *q << " ";
    }
    std::cout << std::endl;
}
```

**Exercise 3.45:** Rewrite the programs again, this time using auto.

```c++
std::cout << "\nmethod 6: auto with begin() and end()" << std::endl;
for (auto p = std::begin(multi); p != std::end(multi); ++p) {
    for (auto q = std::begin(*p); q != std::end(*p); ++q) {
        std::cout << *q << " ";
    }
    std::cout << std::endl;
}
```

### Notes

- <u>如何初始化类的对象是由类本身决定的</u>。一个类可以定义很多种初始化对象的方式。
- 如果使用等号（=）初始化一个变量，实际上执行的是**拷贝初始化**（*copy initialization*），编译器把等号右侧的初始值拷贝到新创建的对象中去。与之相反，如果不适用等号，则执行的是**直接初始化**（*direct initialization*）。
- 尽管我们不太清楚string::size_type类型的细节，但有一点是肯定的：它是一个<u>无符号类型的值而且能够足够存放下任何string对象的大小</u>。所有用于存放string类的size函数返回值的变量，都应该是string::size_type类型的。
- 因为某些历史原因，也为了与C兼容，所以C++语言中的字符串字面值并不是标准库类型string的对象。切记，字符串字面值和string是不同的类型。


- string和vector是两种最重要的标准库类型，前者支持可变长字符串，后者则表示可变长的集合。还有一种标准库类型是迭代器，它是string和vector的配套类型，常被用于访问string中的字符或vector中的元素。
- 内置数组是一种更基础的类型，string和vector都是对它的某种抽象。
- <u>如何初始化类的对象是由类本身决定的</u>。一个类可以定义很多种初始化对象的方式。如果使用等号（=）初始化一个变量，实际上执行的是拷贝初始化（*copy initialization*），编译器把等号右侧的初始值拷贝到新创建的对象中去。与之相反，如果不使用等号，则执行的是直接初始化（*direct initialization*）。
- 尽管我们不太清楚string::size_type类型的细节，但是有一点是肯定的：它是一个无符号类型的值而且能足够
- 使用C++版本的C标准库头文件。一般来说，C++程序应该使用名为cname的头文件而不使用name.h的形式，标准库中的名字总能在命名空间std中找到。
- <u>如果循环体内包含有向vector对象添加元素的语句，则不能使用范围for</u>。（范围for语句体内不应改变其所遍历序列的大小。）另外一个限制是<u>任何一种可能改变vector对象容量的操作，比如push_back，都会使该vector对象的迭代器失效。</u>
- Vector对象能够高速增长，<u>因此没有必要在定义的时候设定大小，事实上如果这么做性能可能更差</u>。只有一种例外情况，就是所有（all）元素的值都一样。通常是预先定义空的vector，在动态插入元素。
- <u>数组是一种复合类型（其他复合类型还有引用和指针）</u>。数组的声明中的维度说明了数组中元素的个数，维度也属于数组类型的一部分，因此，<u>维度必须是一个常量表达式</u>。
- 理解数组声明的含义，最好的办法是<u>从数组的名字开始按照由内向外的顺序阅读</u>。
- 虽然标准库类型string和vector也能执行下标运算，但是数组和他们相比还是有些不同。<u>标准库类型限定使用的下标必须是无符号数类型，而内置的下标运算无此要求</u>。
- <u>在使用范围for语句处理多维数组时，除了最内侧的循环外，其他所有循环的控制变量都应该是引用类型</u>。