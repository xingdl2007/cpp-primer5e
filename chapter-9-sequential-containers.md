# Chapter 9 Sequential Containers

**Exercise 9.1:** Which is the most appropriate—a vector, a deque, or a list—for the following program tasks? Explain the rationale for your choice. If there is no reason to prefer one or another container, explain why not.

(a) Read a fixed number of words, inserting them in the container alphabetically as they are entered. We’ll see in the next chapter that associative containers are bettersuited to this problem.

(b) Read an unknown number of words. Always insert new words at the back.Remove the next value from the front.

(c) Read an unknown number of integers from a file. Sort the numbers and thenprint them to standard output.

```c++
// map最合适；map是按照key排序的。替代方案是vector然后sort。
// deque最合适。总是在两端插入和删除。
// map最合适。替代方案还是vector然后sort。
```

**Exercise 9.2:** Define a list that holds elements that are deques that hold ints.

**Exercise 9.3:** What are the constraints on the iterators that form iterator ranges?

```c++
// 必须指向同一个容器的元素，或者最后一个元素之后的位置
// 反复递增begin可以到达end
// 有效范围是[begin,end)，左闭合区间
```

**Exercise 9.4:** Write a function that takes a pair of iterators to a vector<int> and anint value. Look for that value in the range and return a bool indicating whether it was found.

**Exercise 9.5:** Rewrite the previous program to return an iterator to the requested element. Note that the program must handle the case where the element is not found.

```c++
typedef vector<int>::iterator iter;

iter find(iter b, iter e, int v) {
    while (b != e) {
        if (*b == v) {
            return b;
        }
        b++;
    }
    return e;
}
// 如果没有找到，返回迭代器范围e
```

**Exercise 9.6:** What is wrong with the following program? How might you correct it?

```c++
list<int> lst1;
list<int>::iterator iter1 = lst1.begin(),
					iter2 = lst1.end(); 
while (iter1 < iter2) /* ... */
  
---
list迭代器不支持关系运算符
while (iter1 != iter2) /* ... */
```

**Exercise 9.7:** What type should be used as the index into a vector of ints?

```c++
vector<int>::size_type类型，作为下标
```

**Exercise 9.8:** What type should be used to read elements in a list of strings? To write them?

```c++
list<string>::const_iterator
list<string>::iterator
```

**Exercise 9.9:** What is the difference between the begin and cbegin functions?

```c++
// 如果容器不是const的，begin返回iterator类型，cbegin返回const_iterator类型。
// 如果容器是const的，两者返回的都是const_iterator类型。
```

**Exercise 9.10:** What are the types of the following four objects?

```c++
vector<int> v1;
const vector<int> v2;
auto it1 = v1.begin(), it2 = v2.begin(); 
auto it3 = v1.cbegin(), it4 = v2.cbegin();

---
it1: vector<int>::iterator
it2: vector<int>::const_iterator
it3: vector<int>::const_iterator
it4: vector<int>::const_iterator
```

**Exercise 9.11:** Show an example of each of the six ways to create and initialize avector. Explain what values each vector contains.

```c++
vector<int> ivec;
vector<int> ivec{1,2,3};
vector<int> ivec = {1,2,3};
vector<int> ivec(ivec2);
vector<int> ivec(10,1);
vector<int> ivec(10);
```

**Exercise 9.12:** Explain the differences between the constructor that takes a containerto copy and the constructor that takes two iterators.

```c++
// 这个不同还是有些微妙的
// 接受另外一个容器时，要求容器的类型和元素类型一致
// 接受一对迭代器版本的构造函数，要求元素类型可以转换为目标元素类型即可。
```

**Exercise 9.13:** How would you initialize a `vector<double>` from a `list<int>`? From a `vector<int>`? Write code to check your answers.

```c++
vector<int> ivec = {1, 2, 3, 5, 8};
list<int> ilist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
vector<double> dvec(ilist.begin(), ilist.end());
vector<double> dvec2(ivec.begin(), ivec.end());
```

**Exercise 9.14:** Write a program to assign the elements from a list of char* pointers to C-style character strings to a vector of strings.

```c++
list<const char *> clist = {"hello", "world"};
vector<string> svec(clist.begin(), clist.end());
```

**Exercise 9.15:** Write a program to determine whether two `vector<int>`s are equal.

```c++
ivec == ivec2
```

**Exercise 9.16:** Repeat the previous program, but compare elements in a `list<int>` to a `vector<int>`.

```c++
vector<int> copy(list.begin(),list.end());
copy == ivec2
```

**Exercise 9.17:** Assuming c1 and c2 are containers, what (if any) constraints does the following usage place on the types of c1 and c2?

```c++
if (c1 < c2)
  
---
// 限制就是容器的类型和元素的类型必须一致；而且元素的类型定义了<运算符。
```

**Exercise 9.18:** Write a program to read a sequence of strings from the standard inputinto a deque. Use iterators to write a loop to print the elements in the deque.

```c++
// push_back() for deque
```

**Exercise 9.19:** Rewrite the program from the previous exercise to use a list. List thechanges you needed to make.

```c++
// push_front() for list
```

**Exercise 9.20:** Write a program to copy elements from a `list<int>` into two deques.The even-valued elements should go into one deque and the odd ones into the other.

```c++
list<int> ilist = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
deque<int> idq1, idq2;
for (auto i:ilist) {
    if (i % 2) {
        idq1.push_back(i);
    } else {
        idq2.push_back(i);
    }
}
cout << ilist.size() << " " << idq1.size() << " " << idq2.size() << endl;
```

**Exercise 9.21:** Explain how the loop from page 345 that used the return from insertto add elements to a list would work if we inserted into a vector instead.

```c++
// 效果还是push_front，不过对于vector来说，会比较耗时，因为每次插入新的元素，都需要将所有先有的元素向后移动一位。
```

**Exercise 9.22:** Assuming iv is a vector of ints, what is wrong with the following program? How might you correct the problem(s)?

```c++
vector<int>::iterator iter = iv.begin(),
					  mid = iv.begin() + iv.size()/2;
   while (iter != mid)
       if (*iter == some_val)
           iv.insert(iter, 2 * some_val);

---
// 首先是个死循环
// 不知道这个程序的意图是干啥
  
int some_val = 2;
vector<int>::iterator iter = ivec.begin();
while (iter != ivec.begin() + ivec.size() / 2) {
    if (*iter == some_val) {
        iter = ivec.insert(iter, 2 * some_val);
        iter += 2;
    } else {
        ++iter;
    }
}
```

**Exercise 9.23:** In the first program in this section on page 346, what would the valuesof val, val2, val3, and val4 be if c.size() is 1?

**Exercise 9.24:** Write a program that fetches the first element in a vector using at,the subscript operator, front, and begin. Test your program on an empty vector.

```c++
vector<int> evec;
// out-of-range exception
cout << evec.at(0);

// segmentation fault
cout << evec[0];

// segmentation fault
cout << evec.front();

// segmentation faule
cout << evec.back();
```

**Exercise 9.25:** In the program on page 349 that erased a range of elements, what hap-pens if elem1 and elem2 are equal? What if elem2 or both elem1 and elem2 are theoff-the-end iterator?

**Exercise 9.26:** Using the following definition of ia, copy ia into a vector and into alist. Use the single-iterator form of erase to remove the elements with odd valuesfrom your list and the even values from your vector.

```c++
int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
```

**Exercise 9.27:** Write a program to find and remove the odd-valued elements in aforward_list<int>.

**Exercise 9.28:** Write a function that takes a `forward_list<string>` and two additional string arguments. The function should find the first string and insert thesecond immediately following the first. If the first string is not found, then insert thesecond string at the end of the list.

```c++
void insert_after(forward_list<string> &flist, string s1, string s2) {
    auto pre = flist.before_begin(), curr = flist.begin();
    while (curr != flist.end()) {
        if (*curr == s1) {
            flist.insert_after(curr, s2);
            return;
        } else {
            pre = curr;
            ++curr;
        }
    }
    flist.insert_after(pre, s2);
}
```

**Exercise 9.29:** Given that vec holds 25 elements, what does `vec.resize(100)` do? What if we next wrote `vec.resize(10)`?

```c++
// resize()对vector的行为和list不同
// 如果resize的大小超过了当前的容量，则会分配空间直到resize参数指定的大小，此时空间用满。
// 然后如果下次resize的参数小于容量，则容量不变。
// 每次resize之后，vector的size总是等于resize的参数的。
```

**Exercise 9.30:** What, if any, restrictions does using the version of resize that takes asingle argument place on the element type?

```c++
// 因为resize可能超过原来容器的大小，需要对新增的元素进行值初始化。
// 对于接受单个参数的resize版本，要求元素类型定义默认构造函数。
```

**Exercise 9.31:** The program on page 354 to remove even-valued elements and dupli-cate odd ones will not work on a list or forward_list. Why? Revise the programso that it works on these types as well.

```c++
iter += 2;
---
++iter;
++iter;
```

**Exercise 9.32:** In the program onpage 354 would it be legal to write the call to insertas follows? If not, why not?

```c++
iter = vi.insert(iter, *iter++);
---
// 依赖求值顺序，行为未定义
```

**Exercise 9.33:** In the final example in this section what would happen if we did notassign the result of insert to begin? Write a program that omits this assignment tosee if your expectation was correct.

```c++
// 可能导致死循环，segmentation fault等
// 取决于是否会在insert期间重新分配空间，如果capacity足够，会正确执行结束。
```

**Exercise 9.34:** Assuming vi is a container of ints that includes even and odd values,predict the behavior of the following loop. After you’ve analyzed this loop, write aprogram to test whether your expectations were correct.

```c++
iter = vi.begin();
while (iter != vi.end())
	if (*iter % 2)
		iter = vi.insert(iter, *iter);
	++iter;

---
// 错误百出，死循环。
```

**Exercise 9.35:** Explain the difference between a vector’s capacity and its size.

```c++
// size: 当前容器中存放的元素个数
// capacity: 在不重新分配内存的情况下，最多可以放的元素个数
```

**Exercise 9.36:** Can a container have a capacity less than its size?

```c++
// 不可能
```

**Exercise 9.37:** Why don’t list or array have a capacity member?

```c++
// list: 每次添加元素都需要分配内存，不会预留
// array: 固定长度
```

**Exercise 9.38:** Write a program to explore how vectors grow in the library you use.

```c++
// double的内存分配策略
```

**Exercise 9.39:** Explain what the following program fragment does:

```c++
vector<string> svec;
svec.reserve(1024);
string word;
while (cin >> word)
	svec.push_back(word); 
svec.resize(svec.size()+svec.size()/2);

---
// 首先预留1024的空间, 然后从标准输入读入string，存入容器
// 将容器的大小设置约为size的1.5倍，多出的部分值初始化为空字符串
```

**Exercise 9.40:** If the program in the previous exercise reads 256 words, what is its likely capacity after it is resized? What if it reads 512? 1,000? 1,048?

```c++
256: 1024
1000: 1500
1048: 2048
```

**Exercise 9.41:** Write a program that initializes a string from a `vector<char>`.

```c++
vector<char> cvec = {'h', 'e', 'l', 'l', 'o'};
string str(cvec.begin(), cvec.end());
```

**Exercise 9.42:** Given that you want to read a character at a time into a string, andyou know that you need to read at least 100 characters, how might you improve the performance of your program?

```c++
// 先放到长度为100的array中，然后从array中构造string
```

**Exercise 9.43:** Write a function that takes three strings, s, oldVal, and newVal.Using iterators, and the insert and erase functions replace all instances of oldValthat appear in s by newVal. Test your function by using it to replace common abbre-viations, such as “tho” by ”though” and ”thru” by “through”.

```c++
void replace(string &s, const string &o, const string &n) {
    for (string::size_type pos = 0; (pos = s.find(o, pos)) != string::npos;) {
        s.replace(pos, o.size(), n);
        pos += n.size();
    }
}
```

**Exercise 9.44:** Rewrite the previous function using an index and replace.

**Exercise 9.45:** Write a funtion that takes a string representing a name and two otherstrings representing a prefix, such as “Mr.” or “Ms.” and a suffix, such as “Jr.” or“III”. Using iterators and the insert and append functions, generate and return anew string with the suffix and prefix added to the given name.

**Exercise 9.46:** Rewrite the previous exercise using a position and length to managethe strings. This time use only the insert function.

**Exercise 9.47:** Write a program that finds each numeric character and then each alpha-betic character in the string "ab2c3d7R4E6". Write two versions of the program.The first should use find_first_of, and the second find_first_not_of.

```c++
string data = "ab2c3d7R4E6";
for (string::size_type pos = 0;
     (pos = data.find_first_of("0123456789", pos)) != string::npos;) {
    cout << pos++ << endl;
}
cout << data << endl;
for (string::size_type pos = 0;
     (pos = data.find_first_not_of("0123456789", pos)) != string::npos;) {
    cout << pos++ << endl;
}
```

**Exercise 9.48:** Given the definitions of name and numbers on page 365, what doesnumbers.find(name) return?

```c++
string::npos
```

**Exercise 9.49:** A letter has an ascender if, as with d or f, part of the letter extendsabove the middle of the line. A letter has a descender if, as with p or g, part of theletter extends below the line. Write a program that reads a file containing words andreports the longest word that contains neither ascenders nor descenders.

**Exercise 9.50:** Write a program to process a `vector<string>`s whose elements rep-resent integral values. Produce the sum of all the elements in that vector. Changethe program so that it sums of strings that represent floating-point values.

```c++
vector<string> nvec = {"1", "2", "3", "4"};
int sum = 0;
for (const auto &n :nvec) {
    sum += std::stoi(n);
}
cout << sum << endl;
```

**Exercise 9.51:** Write a class that has three unsigned members representing year,month, and day. Write a constructor that takes a string representing a date. Your constructor should handle a variety of date formats, such as January 1, 1900, 1/1/1900, Jan 1, 1900, and so on.

**Exercise 9.52:** Use a stack to process parenthesized expressions. When you see an open parenthesis, note that it was seen. When you see a close parenthesis after an open parenthesis, pop elements down to and including the open parenthesis off the stack. push a value onto the stack to indicate that a parenthesized expression was replaced.

### Notes

- 一个容器就是一些特定类型对象的集合。
- 顺序容器（sequential container）为程序员提供了控制<u>元素存储和访问顺序</u>的能力。<u>这种顺序不依赖元素的值</u>，而是<u>与元素加入容器时的位置</u>相对应。
- forward_list和array是新C++标准增加的类型。
- <u>forward_list的设计目标是达到与最好的手写的单向链表数据结构相当的性能。</u>因此，forward_list没有size操作，因为保存或计算其大小就会比手写链表多出额外的开销。对于其他容器而言，size保证是一个快速的常量时间的操作。
- <u>新标准库的容器比旧版本快的多</u>。新标准库容器的性能几乎肯定与最精心优化过的同类数据结构一样好（通常会更好）。<u>现代C++程序应该使用标准库容器，而不是更原始的数据结构</u>。
- <u>通常使用vector是最好的选择，除非有很好的理由选择其他容器</u>。
- 如果程序既需要随机访问元素，又需要在容器中间位置插入元素，那该怎么办？<u>答案取决于在list或forward_list中访问元素与vector或deque中插入/删除火元素的相对性能</u>。一般来说，应用中占主导地位的操作（访问的操作更多还是插入/删除更多）决定了容器类型的选择。
- <u>迭代器范围的概念是标准库的基础</u>。
- 对<u>构成范围</u>的迭代器的要求是：如果满足如下条件，<u>两个迭代器begin和end构成一个迭代器范围</u>：
  - 它们指向同一个容器中的元素，或者是容器最后一个元素之后的位置，且
  - 可以通过反复递增begin来达到end。换句话说，end不在begin之前。
  - (<u>编译器不会强制这些要求，确保程序符合这些约定是程序员的责任</u>)
  - 这种元素范围称为**左闭合区间(left-inclusive interval)**，其标准数学描述为[begin, end)。


- <u>当不需要写访问时，应使用cbegin和cend</u>。


- 当将一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型都必须相同。
- <u>只有顺序容器（不包括array）的构造函数才接受大小参数，关联容器并不支持</u>。
- <u>虽然不能对内置数组类型进行拷贝或对象赋值操作，但array并无此限制</u>。


- <u>赋值相关运算会导致指向左边容器内部的迭代器、引用和指针失效。而swap操作将容器内容交换不会导致指向容器的迭代器、引用和指针失效</u>（容器类型为array和string的情况除外，string类型swap之后，迭代器总会失效；array没有定义assign函数）。
- <u>除array外，swap不对任何元素进行拷贝、删除或插入操作，因此可以保证在常数时间内完成</u>。元素不会被移动的事实意味着，除string外，指向容器的迭代器、引用和指针在swap操作之后都不会失效。
- swap两个array会真正交换它们的元素。因此，<u>交换两个array所需的时间与array中元素的数目成正比</u>。


- 当使用迭代器时，最小化要求迭代器必须保持有效的程序片段是一个好方法。由于向迭代器添加元素和从迭代器删除元素的代码可能会使迭代器失效，因此必须保证每次改变容器的操作之后都正确地重新定位迭代器。这个建议对vector、string和deque尤为重要。

