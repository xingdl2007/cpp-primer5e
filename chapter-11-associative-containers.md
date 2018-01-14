# Chapter 11 Associative Containers

**Exercise 11.1:** Describe the differences between a map and a vector.

```c++
// map是关联容器，根据关键字的顺序来进行元素的存储和访问，和插入顺序无关。
// vector是顺序容器，根据元素插入顺序来存放和访问，根据在容器中的位置进行访问。
```

**Exercise 11.2:** Give an example of when each of list, vector, deque, map, and set might be most useful.

**Exercise 11.3:** Write your own version of the word-counting program.

**Exercise 11.4:** Extend your program to ignore case and punctuation. For example,“example.” “example,” and “Example” should all increment the same counter.

```c++
// truncate punctuation
string truncate(const string &word) {
    auto it = std::find_if(word.cbegin(), word.cend(),
                           [](const char c) {
                               return std::ispunct(c);
                           });
    auto count = it - word.cbegin();
    return word.substr(0, count);
}

void to_lower(string &word) {
    for (auto &c :word) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
    }
}
```

**Exercise 11.5:** Explain the difference between a map and a set. When might you use one or the other?

```c++
// key-value: 需要存value用map，不需要用set。
```

**Exercise 11.6:** Explain the difference between a set and a list. When might you use one or the other?

```c++
// 查找
```

**Exercise 11.7:** Define a map for which the key is the family’s last name and the valueis a vector of the children’s names. Write code to add new families and to add newchildren to an existing family.

**Exercise 11.8:** Write a program that stores the excluded words in a vector instead of in a set. What are the advantages to using a set?	

**Exercise 11.9:** Define a map that associates words with a list of line numbers onwhich the word might occur.

```c++
std::map<string,std::list<int>> words;
```

**Exercise 11.10:** Could we define a map from `vector<int>::iterator` to `int` ?What about from `list<int>::iterator` to `int`? In each case, if not, why not?

```c++
// 99页列出了vector,deque,array,string迭代器额外支持的运算，其中包含比较运算，特别的包含<运算
// 而list的迭代器仅支持标准运算，不支持比较运算

// 所以可以定义vector<int>::iterator到int的map，而不能定义list<int>::iterator到int的map
```

**Exercise 11.11:** Redefine bookstore without using decltype.

```c++
multiset<Sales_data, bool (*)(const Sales_data &, const Sales_data &)> 	bookstore4(compareIsbn);
```

**Exercise 11.12:** Write a program to read a sequence of strings and ints, storing eachinto a pair. Store the pairs in a vector.

**Exercise 11.13:** There are at least three ways to create the pairs in the program forthe previous exercise. Write three versions of that program, creating the pairs in eachway. Explain which form you think is easiest to write and understand, and why.

**Exercise 11.14:** Extend the map of children to their family name that you wrote for theexercises in § 11.2.1 (p. 424) by having the vector store a pair that holds a child’sname and birthday.

**Exercise 11.15:** What are the mapped_type, key_type, and value_type of a map from `int` to `vector<int>`?

```c++
// key_type: int
// mapped_type: vector<int>
// value_type: pair<const int, vector<int>>
```

**Exercise 11.16:** Using a map iterator write an expression that assigns a value to anelement.

```c++
map_it->second = value;
```

**Exercise 11.17:** Assuming c is a multiset of strings and v is a vector of strings, explain the following calls. Indicate whether each call is legal:

```c++
(a) copy(v.begin(), v.end(), inserter(c, c.end())); 
(b) copy(v.begin(), v.end(), back_inserter(c)); 
(c) copy(c.begin(), c.end(), inserter(v, v.end())); 
(d) copy(c.begin(), c.end(), back_inserter(v));

---
(a) legal
(b) illegal, multiset没有push_back成员
(c) legal
(d) legal
```

**Exercise 11.18:** Write the type of map_it from the loop on page 430 without usingauto or decltype.

```c++
std::map<std::string,int>::const_iterator map_it = word_count.cbegin();
```

**Exercise 11.19:** Define a variable that you initialize by calling begin() on themultiset named bookstore from § 11.2.2 (p. 425). Write the variable’s type withoutusing auto or decltype.

```c++
multiset<Sales_data, bool (*)(const Sales_data&,const Sales_data&)>::iterator it = 
bookstore.begin();
```

**Exercise 11.20:** Rewrite the word-counting program from § 11.1 (p. 421) to use insert instead of subscripting. Which program do you think is easier to write and read? Explain your reasoning.

```c++
// subscriping
```

**Exercise 11.21:** Assuming word_count is a map from string to size_t and wordis a string, explain the following loop:

```c++
while (cin >> word)
	++word_count.insert({word, 0}).first->second;

---
// 无论插入是否成功，都将word对应的计数器加1；insert的语义总是返回一个可用的迭代器，指向尝试插入的元素
```

**Exercise 11.22:** Given a `map<string, vector<int>>`, write the types used as anargument and as the return value for the version of insert that inserts one element.

```c++
pari<map<string,vector<int>>::iteraotr,bool> ret = c.insert({str,ivec});
```

**Exercise 11.23:** Rewrite the map that stored vectors of children’s names with a keythat is the family last name for the exercises in § 11.2.1 (p. 424) to use a multimap.

**Exercise 11.24:** What does the following program do?

```c++
map<int, int> m;
m[0] = 1;

---
// 如果m中包含元素0，则为赋值；否则插入一个key-value对。
```

**Exercise 11.25:** Contrast the following program with the one in the previous exercise

```c++
vector<int> v;
v[0] = 1;

---
// 尝试为第0个元素赋值，由于v是空的，行为未定义。
```

**Exercise 11.26:** What type can be used to subscript a map? What type does the subscript operator return? Give a concrete example—that is, define a map and then write the types that can be used to subscript the map and the type that would be returned from the subscript operator.

```c++
// key_type或者可以转换为key_type的类型作为map的下标操作的类型
// map<string,int> m;
// map["Anna"] = 1;
// 下标操作返回的类型是mapped_type &，即mapped_type的引用；
```

**Exercise 11.27:** What kinds of problems would you use count to solve? When mightyou use find instead?

```c++
// 仅仅想知道给定元素是否在容器中时，使用count
// 如果不仅想知道给定元素是否在容器中，而且需要对其操作时，使用find(因为find会返回一个迭代器)。

// 对于不允许重复关键字的容器，可能使用find和count没什么区别。但对于允许重复关键字的容器，count还会做更多的工作：如果元素在容器中，它还会统计有多少个元素有相同的关键字。如果不需要技术，最好使用find。
```

**Exercise 11.28:** Define and initialize a variable to hold the result of calling find on a map from string to vector of int.

```c++
map<string,vector<int>>::iterator res;
```

**Exercise 11.29:** What do upper_bound, lower_bound, and equal_range return when you pass them a key that is not in the container?

```c++
// upper_bound: 返回一个迭代器，指向第一个关键字大于key的元素
// lower_bound: 返回一个迭代器，指向第一个关键字不小于key的元素

// 如果给定key不在multimap中，lower_bound 和 upper_bound返回相等的迭代器，指向一个不影响排序的关键字插入位置。

// equal_range: 返回一个迭代器pair，pair<lower_bound(),upper_bound()>，如果给定key不在容器中，两个迭代器都指向关键字可以插入的位置。

// 这个时候则可以使用带提示迭代器的insert版本，插入新的元素。
```

**Exercise 11.30:** Explain the meaning of the operand `pos.first->second` used inthe output expression of the final program in this section.

```c++
// pos.first: pos是一个pair，first是一个迭代器
// pos.first->second: 迭代器指向一个pair<const string, string>，打印出value的值。
```

**Exercise 11.31:** Write a program that defines a multimap of authors and their works.Use find to find an element in the multimap and erase that element. Be sure yourprogram works correctly if the element you look for is not in the map.

```c++
// erase
cout << endl;
string erase_item("Alain de Botton"); // author we'll look for
string title1 = "Art of Travel";
string title2 = "On Love";
for (auto pos = authors.equal_range(search_item); pos.first != pos.second;) {
    if (pos.first->second == title1 || pos.first->second == title2) {
        pos.first = authors.erase(pos.first);
    } else {
        ++pos.first;
    }
}
```

**Exercise 11.32:** Using the multimap from the previous exercise, write a program toprint the list of authors and their works alphabetically.

**Exercise 11.33:** Implement your own version of the word-transformation program.

**Exercise 11.34:** What would happen if we used the subscript operator instead of find in the transform function?

**Exercise 11.35:** In buildMap, what effect, if any, would there be from rewriting `trans_map[key] = value.substr(1);` as `trans_map.insert({key, value.substr(1)})` ?

```c++
// 下表操作隐含的意义是，后面的规则会覆盖前面的规则
// 如果改为insert操作，则后面的规则不会覆盖之前的规则
```

**Exercise 11.36:** Our program does no checking on the validity of either input file. In particular, it assumes that the rules in the transformation file are all sensible. What would happen if a line in that file has a key, one space, and then the end of the line? Predict the behavior and then check it against your version of the program.

```c++
// runtime error
```

**Exercise 11.37:** What are the advantages of an unordered container as compared to the ordered version of that container? What are the advantages of the ordered version?

```c++
// 如果关键字类型固有就是无序的，或者性能测试发现问题可以用哈希技术解决，就可以使用无序容器

// 优势是不需要维护序；理论上哈希技术可以获得更好的平均性能。
```

**Exercise 11.38:** Rewrite the word-counting (§ 11.1, p. 421) and word-transformation(§ 11.3.6, p. 440) programs to use an unordered_map.

### Notes

- <u>关联容器和顺序容器有着根本的不同</u>：关联容器中的元素是按照<u>关键字来保存和访问</u>的。与之相对，顺序容器中的元素是按它们<u>在容器中的位置来顺序</u>保存和访问的。
- 传递给排序算法的<u>可调用对象</u>必须满足与关联容器中关键字一样的类型要求。所提供的操作必须在关键字类型上定义一个<u>严格弱序（strick weak ordering）</u>。可以将严格弱序看做<u>“小于等于”</u>，它必须具备如下基本性质：
  - 两个关键字不能同时“小于等于”对方；如果k1“小于等于”k2，那么k2决不能“小于等于”k1。
  - 如果k1“小于等于”k2，且k2“小于等于”k3，那么k1必须“小于等于”k3。
  - 如果存在两个关键字，任何一个都不“小于等于”另一个，那么我们称这两个关键字是“等价的”。如果k1“等价于”k2，且k2“等价于”k3，那么k1必须“等价于”k3。如果两个关键字是等价的，那么容器将它们视作相等来处理。
  - <u>思考：为什么是“小于等于”，而不是“小于”？ 严格弱序应该是“小于”才对！？</u>应该将小于和等于分开。
- 在实际编程中，如果一个类型定义了<u>行为正常的 < 运算符</u>，则它可以用作关键字类型。
- set类型不支持下标，因为<u>set中没有与关键字相关联的“值”</u>。同时，<u>也不能对一个multimap或一个unordered_multimap进行下标操作，因为这些容器中可能有多个值与一个关键字关联。</u>
- <u>无序关联容器</u>：不使用比较运算符来组织元素，而是使用<u>一个哈希函数和关键字类型的==运算符</u>。<u>在关键字类型的元素没有明显的序关系的情况下，无序容器是非常有用的。在某些应用中，维护的序代价非常高昂，此时无需容器也很有用。</u>