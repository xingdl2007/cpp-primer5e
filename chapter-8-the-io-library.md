# Chapter 8 The IO Library

**Exercise 8.1:** Write a function that takes and returns an `istream&`. The function should read the stream until it hits end-of-file. The function should print what it reads to the standard output. Reset the stream so that it is valid before returning the stream.

```c++
std::istream &exercise81(std::istream &is) {
    string data;
    while (is >> data) {
        cout << data;
    }
    is.clear();
    assert(is.good());
    return is;
}
```

**Exercise 8.2:** Test your function by calling it, passing `cin` as an argument.

**Exercise 8.3:** What causes the following while to terminate?

```c++
while (cin >> i)  /* ... */
---
// CTRL+D/CTRL+C，end-of-file或者signal，或者读入非i类型的数据，导致流出错，循环终止。
```

**Exercise 8.4:** Write a function to open a file for input and read its contents into avector of strings, storing each line as a separate element in the vector.

```c++
#include <iostream>
#include <fstream>
#include <vector>
using std::cerr; using std::cout; using std::endl;
using std::ifstream;
using std::string; using std::vector; using std::getline;

int main(int argc, char *argv[]) {
    vector<string> content;
    ifstream input(argv[1]);
    string line;
    while (getline(input, line)) {
        content.push_back(line);
    }
    // cout
    for (const auto &l:content) {
        cout << l << endl;
    }
    return 0;
}
```

**Exercise 8.5:** Rewrite the previous program to store each word in a separate element.

```c++
#include <iostream>
#include <fstream>
#include <vector>
using std::cerr; using std::cout; using std::endl;
using std::ifstream;
using std::string; using std::vector; using std::getline;

int main(int argc, char *argv[]) {
    vector<string> content;
    ifstream input(argv[1]);
    string word;
    while (input >> word) {
        content.push_back(word);
    }

    // cout
    for (const auto &w:content) {
        cout << w << endl;
    }
    return 0;
}
```

**Exercise 8.6:** Rewrite the bookstore program from § 7.1.1 (p. 256) to read its transac-tions from a file. Pass the name of the file as an argument to main (§ 6.2.5, p. 218).

```c++
#include "Sales_data.h"
#include <fstream>

using std::cerr; using std::cin; using std::cout; using std::endl;
using std::ifstream; using std::ofstream;

int main(int argc, char *argv[]) {
    Sales_data data1, data2;
    ifstream in(argv[1]);
    if (read(in, data1) && read(in, data2)) {  // read the transactions
        if (data1.isbn() == data2.isbn()) {      // check isbns
            Sales_data sum = add(data1, data2);  // add the transactions
            print(cout, sum);                    // print the results
            cout << endl;                        // followed by a newline
        }
    } else
        cerr << "Input failed!" << endl;

    return 0;
}
```

**Exercise 8.7:** Revise the bookstore program from the previous section to write its out-put to a file. Pass the name of that file as a second argument to main.

```c++
#include "Sales_data.h"
#include <fstream>

using std::cerr; using std::cin; using std::cout; using std::endl;
using std::ifstream; using std::ofstream;

int main(int argc, char *argv[]) {
    Sales_data data1, data2;
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    if (read(in, data1) && read(in, data2)) {  // read the transactions
        if (data1.isbn() == data2.isbn()) {      // check isbns
            Sales_data sum = add(data1, data2);  // add the transactions
            print(out, sum);                    // print the results
            out << endl;                        // followed by a newline
        }
    } else
        cerr << "Input failed!" << endl;

    return 0;
}
```

**Exercise 8.8:** Revise the program from the previous exercise to append its output to its given file. Run the program on the same output file at least twice to ensure that the data are preserved.

```c++
ofstream out(argv[2], ofstream::app);
```

**Exercise 8.9:** Use the function you wrote for the first exercise in § 8.1.2 (p. 314) to print the contents of an `istringstream` object.

```c++
cout << "exercise 8.9: " << endl;
istringstream test("hello world!!\n");
exercise81(test);
```

**Exercise 8.10:** Write a program to store each line from a file in a `vector<string>`. Now use an `istringstream` to read each element from the vector a word at a time.

```c++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::cin; using std::cout; using std::cerr;
using std::istream; using std::ostream; using std::endl;
using std::ostringstream; using std::istringstream;
using std::vector; using std::string;
using std::ifstream;

int main(int argc, char *argv[]) {
    vector<string> content;
    string line;
    // read from file
    ifstream is(argv[1]);
    while (std::getline(is, line)) {
        content.push_back(line);
    }

    // read from vector
    string word;
    for (const auto &l :content) {
        istringstream ss(l);
        while (ss >> word) {
            cout << word << " ";
        }
        cout << '\n';
    }
    return 0;
}
```

**Exercise 8.11:** The program in this section defined its `istringstream` object inside the outer while loop. What changes would you need to make if record were defined outside that loop? Rewrite the program, moving the definition of record outside the while, and see whether you thought of all the changes that are needed.

```c++
vector<PersonInfo> getData(istream &is) {
    // will hold a line and word from input, respectively
    string line, word;

    // will hold all the records from the input
    vector<PersonInfo> people;
    istringstream record;
    // read the input a line at a time until end-of-file (or other error)
    while (getline(is, line)) {
        PersonInfo info;            // object to hold this record's data
        record.str(line);           // bind record to the line we just read
        record >> info.name;        // read the name
        while (record >> word)      // read the phone numbers
            info.phones.push_back(word);  // and store them
        people.push_back(info); // append this record to people
        record.clear();
    }
    return people;
}
// 需要将流的状态复位，因为上次循环达到了EOF状态
```

**Exercise 8.12:** Why didn’t we use in-class initializers in `PersonInfo`?

```c++
// 因为数据总是需要从外部读入，没有必要。
```

**Exercise 8.13:** Rewrite the phone number program from this section to read from a named file rather than from `cin`.

```c++
int main(int argc, char *argv[]) {
    std::ifstream is(argv[1]);
    std::ofstream os(argv[2]);
    process(os, getData(is));
    return 0;
}
```

**Exercise 8.14:** Why did we declare entry and nums as `const auto &`?

```c++
// 因为在处理过程中没有修改entry和nums，所以应该声明为const引用
```

### Notes

- IO对象无拷贝或赋值