# Chapter 10 Generic Algorithms

**Exercise 10.1:** The algorithm header defines a function named count that, likefind, takes a pair of iterators and a value. count returns a count of how often thatvalue appears. Read a sequence of ints into a vector and print the count of howmany elements have a given value.

```c++
vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
cout << count(ivec.begin(), ivec.end(), 0) << endl;
```

**Exercise 10.2:** Repeat the previous program, but read values into a list of strings.

```c++
list<string> ilist{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
cout << count(ilist.begin(), ilist.end(), "0") << endl;
```

**Exercise 10.3:** Use accumulate to sum the elements in a `vector<int>`.

**Exercise 10.4:** Assuming v is a `vector<double>`, what, if anything, is wrong with calling `accumulate(v.cbegin(), v.cend(), 0)`?

```c++
// accumulate根据第三个参数推断元素类型，应该改为.0，否则元素按照int类型累加，小数部分被丢弃
```

**Exercise 10.5:** In the call to equal on rosters, what would happen if both rosters held C-style strings, rather than library strings?

```c++
// 会比较指针是否相等，而不是内容
char data1[] = {'h', 'e', 'l', 'l', 'o', '\0'};
char data2[] = {'h', 'e', 'l', 'l', 'o', '\0'};
char data3[] = {'h', 'e', 'l', 'l', 'o', '\0'};
char data4[] = {'h', 'e', 'l', 'l', 'o', '\0'};

vector<const char *> roster1{data1, data2};
vector<const char *> roster2{data3, data4};
vector<string> roster3{"hello", "hello"};

cout << ((equal(roster1.cbegin(), roster1.cend(), roster2.cbegin())) ? "t" : "f") << endl;
cout << ((equal(roster3.cbegin(), roster3.cend(), roster1.cbegin())) ? "t" : "f") << endl;

// output:
// false
// true
```

**Exercise 10.6:** Using `fill_n`, write a program to set a sequence of int values to 0.

**Exercise 10.7:** Determine if there are any errors in the following programs and, if so, correct the error(s):

```c++
(a) vector<int> vec; list<int> lst; int i; while (cin >> i)
	lst.push_back(i);
	copy(lst.cbegin(), lst.cend(), vec.begin());
(b) vector<int> vec;
	vec.reserve(10); // reserve is covered in § 9.4 (p. 356) 
	fill_n(vec.begin(), 10, 0);

---
(a) copy(lst.cbegin(), lst.cend(), back_inserter(lst));
(b) vec.resize(10);
```

**Exercise 10.8:** We said that algorithms do not change the size of the containers over which they operate. Why doesn’t the use of back_inserter invalidate this claim?

```c++
// 因为算法没有直接更改容器，通过给插入器赋值，插入器负责将元素添加到容器中。
```


**Exercise 10.9:** Implement your own version of elimDups. Test your program by printing the vector after you read the input, after the call to unique, and after thecall to erase.

**Exercise 10.10:** Why do you think the algorithms don’t change the size of containers?

```c++
// 防止迭代器失效
```

**Exercise 10.11:** Write a program that uses stable_sort and isShorter to sort avector passed to your version of elimDups. Print the vector to verify that yourprogram is correct.

**Exercise 10.12:** Write a function named compareIsbn that compares the isbn()members of two Sales_data objects. Use that function to sort a vector that holdsSales_data objects.

**Exercise 10.13:** The library defines an algorithm named partition that takes a pred-icate and partitions the container so that values for which the predicate is true appearin the first part and those for which the predicate is false appear in the second part.The algorithm returns an iterator just past the last element for which the predicatereturned true. Write a function that takes a string and returns a bool indicatingwhether the string has five characters or more. Use that function to partition words.Print the elements that have five or more characters.

```c++
vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
auto ret = std::partition(words.begin(), words.end(),
                              [](const string &s) {
                                  return s.size() < 5;
                              });
// print out
std::for_each(words.begin(), ret,
                  [](const string &s) {
                      cout << std::quoted(s) << endl;
                  });
```

**Exercise 10.14:** Write a lambda that takes two ints and returns their sum.

```c++
auto func = [](int a, int b) { return a + b; };
cout << func(1, 2) << endl;
```

**Exercise 10.15:** Write a lambda that captures an int from its enclosing function and takes an int parameter. The lambda should return the sum of the captured int and the int parameter.

```c++
int cap = 100;
auto func2 = [cap](int i) { return i + cap; };
cout << func2(8) << endl;
```

**Exercise 10.16:** Write your own version of the biggies function using lambdas.

```c++
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>
#include <functional>

using std::string;
using std::vector;
using std::cin; using std::cout; using std::endl;

// comparison function to be used to sort by word length
bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

void print(const vector<string> &words) {
    for_each(words.begin(), words.end(),
             [](const string &s) { cout << std::quoted(s) << " "; });
    cout << endl;
}

void elimDups(vector<string> &words) {
    sort(words.begin(), words.end());
    auto ret = std::unique(words.begin(), words.end());
    words.erase(ret, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto ret = std::stable_partition(words.begin(), words.end(),
                                     [sz](const string &s) {
                                         return s.size() < sz;
                                     });
    for_each(ret, words.end(),
             [sz](const string &s) {
                 cout << std::quoted(s) << " ";
             });
    cout << endl;
}

void biggies2(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto ret = std::find_if(words.begin(), words.end(),
                            [sz](const string &s) {
                                return s.size() >= sz;
                            });
    for_each(ret, words.end(),
             [sz](const string &s) {
                 cout << std::quoted(s) << " ";
             });
    cout << endl;
}

int main() {
    vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    biggies(words, 3);
    biggies(words, 4);
    biggies2(words, 5);
    biggies2(words, 6);
    return 0;
}
```

**Exercise 10.17:** Rewrite exercise 10.12 from § 10.3.1 (p. 387) to use a lambda in the call to sort instead of the compareIsbn function.

**Exercise 10.18:** Rewrite biggies to use partition instead of find_if. We described the partition algorithm in exercise 10.13 in § 10.3.1 (p. 387).

```c++
void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto ret = std::stable_partition(words.begin(), words.end(),
                                     [sz](const string &s) {
                                         return s.size() < sz;
                                     });
    for_each(ret, words.end(),
             [sz](const string &s) {
                 cout << std::quoted(s) << " ";
             });
    cout << endl;
}
```

**Exercise 10.19:** Rewrite the previous exercise to use stable_partition, which like stable_sort maintains the original element order in the paritioned sequence.

```c++
auto ret = std::stable_partition(words.begin(), words.end(),
                                     [sz](const string &s) {
                                         return s.size() < sz;
                                     });
```

**Exercise 10.20:** The library defines an algorithm named count_if. Like find_if,this function takes a pair of iterators denoting an input range and a predicate that itapplies to each element in the given range. count_if returns a count of how often thepredicate is true. Use count_if to rewrite the portion of our program that countedhow many words are greater than length 6.

```c++
auto count = std::count_if(words.begin(), words.end(),
                               [=](const string &s) {
                                   return s.size() >= sz;
                               });
cout << count << " words is >= " << sz << endl;
```

**Exercise 10.21:** Write a lambda that captures a local int variable and decrements thatvariable until it reaches 0. Once the variable is 0 additional calls should no longerdecrement the variable. The lambda should return a bool that indicates whether the captured variable is 0.

```c++
int i = 3;
auto fun3 = [=]()mutable -> bool {
    if (i == 0) {
        return true;
    }
    --i;
    return false;
};
```

**Exercise 10.22:** Rewrite the program to count words of size 6 or less using functionsin place of the lambdas.

```c++
auto count = std::count_if(words.begin(), words.end(),
                               std::bind(target, _1, sz));
cout << count << " words is >= " << sz << endl;
```

**Exercise 10.23:** How many arguments does bind take?

```c++
// 比原始可调用对象多一个的参数
// bind函数的第一个参数是需要适配的原始可调用对象，其他参数会传递给原始可调用对象。
```

**Exercise 10.24:** Use bind and check_size to find the first element in a vector of ints that has a value greater than the length of a specified string value.

**Exercise 10.25:** In the exercises for § 10.3.2 (p. 392) you wrote a version of biggiesthat uses partition. Rewrite that function to use check_size and bind.

**Exercise 10.26:** Explain the differences among the three kinds of insert iterators.

```c++
// there are 3 insert iterators. 以下三个都是函数，会返回一个插入器
(1) back_inserter： 创建一个使用push_back的迭代器
(2) front_inserter：创建一个使用push_front的迭代器
(3) inserter：创建一个使用insert的迭代器；元素将插入到给定迭代器之前
```

**Exercise 10.27:** In addition to unique (§ 10.2.3, p. 384), the library defines functionnamed unique_copy that takes a third iterator denoting a destination into whichto copy the unique elements. Write a program that uses unique_copy to copy theunique elements from a vector into an initially empty list.

```c++
vector<int> ivec2{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
list<int> ilist2;
std::unique_copy(ivec2.begin(), ivec2.end(), std::inserter(ilist2, ilist2.begin()));
std::for_each(ilist2.begin(), ilist2.end(),
              [](int i) {
                  cout << i << endl;
              });
```

**Exercise 10.28:** Copy a vector that holds the values from 1 to 9 inclusive, into threeother containers. Use an inserter, a back_inserter, and a front_inserter,respectivly to add elements to these containers. Predict how the output sequence variesby the kind of inserter and verify your predictions by running your programs.

```c++
vector<int> ivec2{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
list<int> ilist2;
vector<int> ivec3;
list<int> ilist3;
std::unique_copy(ivec2.begin(), ivec2.end(), std::inserter(ilist2, ilist2.begin()));
std::unique_copy(ivec2.begin(), ivec2.end(), std::front_inserter(ilist3));
std::unique_copy(ivec2.begin(), ivec2.end(), std::back_inserter(ivec3));

std::for_each(ilist2.begin(), ilist2.end(),
              [](int i) {
                  cout << i << endl;
              });
cout << endl;
std::for_each(ilist3.begin(), ilist3.end(),
              [](int i) {
                  cout << i << endl;
              });
cout << endl;
std::for_each(ivec3.begin(), ivec3.end(),
              [](int i) {
                  cout << i << endl;
              });
cout << endl;
```

**Exercise 10.29:** Write a program using stream iterators to read a text file into a vector of strings.

```c++
std::istream_iterator<string> in(std::cin), eof;
    vector<string> words2(in, eof);
    std::for_each(words2.begin(), words2.end(), [](const string &s) { cout << s << " "; });
cout << endl;
```

**Exercise 10.30:** Use stream iterators, sort, and copy to read a sequence of integersfrom the standard input, sort them, and then write them back to the standard output.

```c++
std::istream_iterator<int> in2(std::cin), eof2;
vector<int> nums;
copy(in2, eof2, std::back_inserter(nums));
std::sort(nums.begin(), nums.end());
std::for_each(nums.begin(), nums.end(), [](int i) { cout << i << " "; });
cout << endl;
```

**Exercise 10.31:** Update the program from the previous exercise so that it prints onlythe unique elements. Your program should use unqiue_copy (§ 10.4.1, p. 403).

```c++
unique_copy(in2, eof2, std::back_inserter(nums));
```

**Exercise 10.32:** Rewrite the bookstore problem from § 1.6 (p. 24) using a vector tohold the transactions and various algorithms to do the processing. Use sort withyour compareIsbn function from § 10.3.1 (p. 387) to arrange the transactions in order,and then use find and accumulate to do the sum.

**Exercise 10.33:** Write a program that takes the names of an input file and two output files. The input file should hold integers. Using an `istream_iterator` read the input file. Using `ostream_iterators`, write the odd numbers into the first outputfile. Each value should be followed by a space. Write the even numbers into the secondfile. Each of these values should be placed on a separate line.

**Exercise 10.34: **Use `reverse_iterators` to print a vector in reverse order.

**Exercise 10.35:** Now print the elements in reverse order using ordinary iterators.

**Exercise 10.36:** Use find to find the last element in a list of ints with value 0.

```c++
list<int> ilist4{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 0, 9, 9};
auto rr = std::find(ilist4.crbegin(), ilist4.crend(), 0);
```

**Exercise 10.37:** Given a vector that has ten elements, copy the elements from positions 3 through 7 in reverse order to a list.

```c++
vector<int> ivec4{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
list<int> ilist5;
copy(ivec4.crbegin() + 2, ivec4.crend() - 3, std::inserter(ilist5, ilist5.begin()));
std::for_each(ilist5.begin(), ilist5.end(), [](int i) { cout << i << " "; });
cout << endl;
```

**Exercise 10.38:** List the five iterator categories and the operations that each supports.

```c++
// 输入迭代器：只读，不写；单遍扫描，只能递增
// 输出迭代器：只写，不读；单遍扫描，只能递增
// 前向迭代器：可读写；多遍扫描，只能递增
// 双向迭代器：可读写；多遍扫描，可递增递减
// 随机访问迭代器：可读写；多遍扫描，支持全部迭代器操作
```

**Exercise 10.39:** What kind of iterator does a list have? What about a vector?

```c++
// list的迭代器是双向迭代器（list是双链表结构，forward_list是单链表）
// vector的迭代其实随机访问迭代器
```

**Exercise 10.40:** What kinds of iterators do you think copy requires? What about reverse or unique?

```c++
// copy: 输入+输出迭代器
// reverse: 双向迭代器
// unique: 前向迭代器
```

**Exercise 10.41:** Based only on the algorithm and argument names, describe the operation that the each of the following library algorithms performs:

```c++
replace(beg, end, old_val, new_val); 
replace_if(beg, end, pred, new_val); 
replace_copy(beg, end, dest, old_val, new_val); 
replace_copy_if(beg, end, dest, pred, new_val);

---
// 还是很容易理解的
```

**Exercise 10.42:** Reimplement the program that eliminated duplicate words that we wrote in § 10.2.3 (p. 383) to use a list instead of a vector.

```c++
list<string> word_list = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
word_list.sort();
word_list.unique();
std::for_each(word_list.begin(), word_list.end(), [](const string &i) { cout << i << " "; });
cout << endl;
```

### Notes

- 标准库容器定义的操作集合惊人的小。标准库并未给出每个容器添加大量功能，而是提供了一组算法，这些算法中的大多数都独立于任何特定的容器。这些算法是通用的（<u>generic，或称范型的</u>）：<u>它们可用于不同类型的容器和不同类型的元素。</u>
-  范型算法（generic algorithm）：<u>称它们为“算法”，是因为它们实现了一些经典算法的公共接口，如排序和搜索；称它们是“泛型的”，是因为它们可以用于不同类型的元素和多种容器类型</u>（不仅包括标准库类型，还包括内置的数组类型），还能用于其他类型的序列。
- <u>迭代器令算法不依赖于容器，但算法依赖于元素类型的操作</u>。


- 算法本身不会执行容器的操作，<u>它们只会运行于迭代器之上，执行迭代器的操作</u>。泛型算法运行于迭代器之上而不会执行容器操作的特性带来了一个令人惊讶但非常必要的编程假定：<u>算法永远不会改变底层你容器的大小</u>。算法可能改变容器中保存的元素的值，也可能在容器内移动元素，但<u>永远不会直接添加和删除元素</u>。
- 插入器（inserter）：与普通迭代器只能遍历所绑定的迭代器不同，插入器能做更多的事情。<u>当给这类迭代器赋值时，它们会在底层的容器上执行插入操作</u>。因此，<u>当一个算法操作这样的迭代器时，迭代器可以完成向容器中添加元素的效果，但算法自身永远不会做这样的操作</u>。
- 对于只读取而不改变元素的算法，通常最好使用cbegin()和cend()。但是，如果计划使用算法返回的迭代器来改变元素的值，就需要使用begin()和end()的结果作为参数。
- 可以向一个算法传递任何类别的<u>可调用对象</u>(callable object)。<u>对于一个对象或一个表达式，如果可以对其使用调用运算符，则称它为可调用的。</u>
- 可调用对象：<u>函数、函数指针、重载了函数调用运算符的类、lambda表达式（lambda expression）</u>。
- lambda expression：<u>一个lambda表达式表示一个可调用的代码单元</u>。可以将其理解为一个未命名的内联函数。如果忽略返回类型，lambda根据函数体中的代码推断出返回类型。如果函数体只是一个return语句，返回类型从返回的表达式的类型推断而来。否则，返回类型为void。
- <u>当定义一个lambda时，编译器生成一个与lambda对应的新的（未命名的）类类型</u>。目前可以这样理解：当向一个函数传递一个lambda时，<u>同时定义了一个新类型和该类型的一个对象</u>：传递的参数就是此编译器生成的类类型的未命名对象。类似的，<u>当使用auto定义一个用lambda初始化的变量时，定义了一个从lambda生成的类型的对象</u>。


- 对于只在一两个地方使用的简单操作，lambda表达式是最有用的。如果需要在很多地方使用相同的操作，通常应该定义一个函数，而<u>不是多次编写相同的lambda表达式</u>。
- <u>可以将bind看做一个通用的函数适配器</u>，<u>它接受一个可调用对象，然后生成一个新的可调用对象来“适应”原对象的参数列表</u>。
- <u>占位符</u>：数值n表示生成的可调用对象中参数的位置：`_1`为newCallable的第一个参数，`_2`表示第二个参数。


- 默认情况下，bind的那些不是占位符的参数被**拷贝**到bind返回的可调用对象中。如果对象无法拷贝，需要使用标准库函数ref。
- **ref**：函数ref返回一个对象，包含给定的**引用**，此对象可以拷贝。**cref**则生成一个**保存const引用**的类。


- 除了为每个容器定义的迭代器之外，标准库在头文件iterator中还定义了额外几种迭代器。
  - 插入迭代器（inserter iterator）：这些迭代器绑定到一个容器上，可用来向容器插入元素。
  - 流迭代器（stream iterator）：这些迭代器绑定到输入或输出流上，可用来遍历所关联的IO流。
  - 反向迭代器（reverse iterator)：这些迭代器向后而不是向前移动。除了forward_list之外。
  - 移动迭代器（move iterator）：这些专用的迭代器不是拷贝其中的元素，而是移动它们。


- 反向迭代器的目的是表示元素范围，而这些范围是不对称的，这导致一个重要的结果：当从给一个普通迭代器初始化一个反向迭代器，或是给一个反向迭代器赋值时，结果迭代器与原迭代器指向的并不是相同的元素。


- 对于list和forward_list，应该优先使用成员函数版本的算法而不是通用算法。