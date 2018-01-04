# Chapter 1 Getting Started

**Exercise 1.1:** Review the documentation for your compiler and determine what file naming convention it uses. Compile and run the main program from page 2.

```shell
Linux/MacOS: cc
```

**Exercise 1.2:** Change the program to return -1. A return value of -1 is often treated as an indicator that the program failed. Recompile and rerun your program to see how your system treats a failure indicator from main.

```shell
# get 8 bits errno of last process
Linux/MacOS: echo $? 
```

**Exercise 1.3:** Write a program to print `Hello, World` on the standard output.

```c++
#include <iostream>

int main() {
    std::cout << "Hello world" << std::endl;
}
```

**Exercise 1.4:** Our program used the addition operator, `+`, to add two numbers. Write a program that uses the multiplication operator, `*`, to print the product instead.

```c++
#include <iostream>

int main() {
    // prompt user to enter two numbers
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The mul of " << v1 << " and " << v2
              << " is " << v1 * v2 << std::endl;
    return 0;
}
```

**Exercise 1.5:** We wrote the output in one large statement. Rewrite the program to use a separate statement to print each operand.

```c++
 std::cout << "The sum of";
 std::cout << v1;
 std::cout << " and ";
 std::cout << v2;
 std::cout << " is ";
 std::cout << v1 + v2;
 std::cout << std::endl;
```

**Exercise 1.6:** Explain whether the following program fragment is legal.

```c++
std::cout << "The sum of " << v1; 
			<< " and " << v2;
            << " is " << v1 + v2 << std::endl;
```

If the program is legal, what does it do? If the program is not legal, why not? How would you fix it?

```c++
不合法, line2, line3 中的 << 运算符缺少ostream对象

std::cout << "The sum of " << v1
			<< " and " << v2
            << " is " << v1 + v2 << std::endl;
```

**Exercise 1.7:** Compile a program that has incorrectly nested comments.

```c++
error: expected primary-expression before '/' token * /
```

**Exercise 1.8:** Indicate which, if any, of the following output statements are legal:

```c++
std::cout << "/*";
std::cout << "*/";
std::cout << /* "*/" */;
std::cout << /* "*/" /* "/*" */;
```

After you’ve predicted what will happen, test your answers by compiling a program with each of these statements. Correct any errors you encounter.

```
Line 1: legal
Line 2: legal
Line 3: illegal, trick
Line 4: legal
```

**Exercise 1.9:** Write a program that uses a while to sum the numbers from 50 to 100.

```c++
#include <iostream>

int main() {
    int num = 50, sum = 0;
    while (num <= 100) {
        sum += num++;
    }
    std::cout << sum << std::endl;
    return 0;
}
```

**Exercise 1.10:** In addition to the ++ operator that adds 1 to its operand, there is adecrement operator (--) that subtracts 1. Use the decrement operator to write a while that prints the numbers from ten down to zero.

```c++
void down() {
    int i = 10;
    while (i >= 0) {
        std::cout << i-- << std::endl;
    }
}
```

**Exercise 1.11:** Write a program that prompts the user for two integers. Print each number in the range specified by those two integers.

```c++
#include <iostream>

int main() {
    // prompt user to enter two numbers
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    while (v1 < v2) {
        std::cout << v1++ << std::endl;
    }
    return 0;
}
```

**Exercise 1.12:** What does the following for loop do? What is the final value of sum?

```c++
int sum = 0;
   for (int i = -100; i <= 100; ++i)
		sum += i;
```

```
Answer: sum(-100,100) => 0
```

**Exercise 1.13:** Rewrite the first two exercises from § 1.4.1 (p. 13) using for loops.

```c++
#include <iostream>

int main() {
    int sum = 0;
    for (int i = 50; i <= 100; i++) {
        sum += i;
    }
    std::cout << sum << std::endl;
}

for (int i = 10; i >= 0; i--) {
        std::cout << i << std::endl;
}
```

**Exercise 1.14:** Compare and contrast the loops that used a for with those using a while. Are there advantages or disadvantages to using either form?

```
for: 将循环控制变量的更改聚在一起，方便管理，代码简洁
while: 相比for适用更广，可以表达不便使用for表达的循环
```

**Exercise 1.15:** Write programs that contain the common errors discussed in the box on page 16. Familiarize yourself with the messages the compiler generates.

**Exercise 1.16:** Write your own version of a program that prints the sum of a set of integers read from cin.

```c++
int main() {
    int num = 50, sum = 0;
    while (std::cin >> num) {
        sum += num;
    }
    std::cout << sum << std::endl;

    return 0;
}
```

**Exercise 1.17:** What happens in the program presented in this section if the input values are all equal? What if there are no duplicated values?

```
works well
```

**Exercise 1.18:** Compile and run the program from this section giving it only equal values as input. Run it again giving it values in which no number is repeated.

```
works well
```

**Exercise 1.19:** Revise the program you wrote for the exercises in § 1.4.1 (p. 13) that printed a range of numbers so that it handles input in which the first number is smaller than the second.

```c++
if (v1 > v2) {
        // method 1
        //std::swap(v1, v2);

        // method 2
        v1 = v1 + v2;
        v2 = v1 - v2;
        v1 = v1 - v2;
 }
```

**Exercise 1.20:** http://www.informit.com/title/0321714113 contains a copy of Sales_item.h in the Chapter 1 code directory. Copy that file to your working directory. Use it to write a program that reads a set of book sales transactions, writing each transaction to the standard output.

```c++
#include <iostream>
#include "Sales_item.h"

int main() {
    Sales_item item;
    while (std::cin >> item) {
        std::cout << item << std::endl;
    }
    return 0;
}
```

**Exercise 1.21:** Write a program that reads two Sales_item objects that have the same ISBN and produces their sum.

```c++
#include <iostream>
#include "Sales_item.h"

int main() {
    Sales_item item1, item2;

    std::cin >> item1 >> item2;   //read a pair of transactions
    if (item1.isbn() == item2.isbn()) {
        std::cout << item1 + item2 << std::endl; //print their sum
    }
    return 0;
}
```

**Exercise 1.22:** Write a program that reads several transactions for the same ISBN.Write the sum of all the transactions that were read.

```c++
#include <iostream>
#include "Sales_item.h"

int main() {
    Sales_item item, sum;
    if (std::cin >> sum) {
        while (std::cin >> item) {
            if (sum.isbn() == item.isbn()) {
                sum += item;
            }
        }
        std::cout << sum << std::endl;
    }
    return 0;
}
```

**Exercise 1.23:** Write a program that reads several transactions and counts how many transactions occur for each ISBN.

```c++
#include <iostream>
#include "Sales_item.h"

int main() {
    // currVal is the number we're counting; we'll read new values into val
    Sales_item currVal, val;

    // read first number and ensure that we have data to process
    if (std::cin >> currVal) {
        int cnt = 1;  // store the count for the current value we're processing
        while (std::cin >> val) { // read the remaining numbers
            if (val.isbn() == currVal.isbn())   // if the values are the same
                ++cnt;            // add 1 to cnt
            else { // otherwise, print the count for the previous value
                std::cout << currVal.isbn() << " occurs "
                          << cnt << " times" << std::endl;
                currVal = val;    // remember the new value
                cnt = 1;          // reset the counter
            }
        }// while loop ends here
        // remember to print the count for the last value in the file
        std::cout << currVal.isbn() << " occurs "
                  << cnt << " times" << std::endl;
    }// outermost if statement ends here
    return 0;
}
```

**Exercise 1.24:** Test the previous program by giving multiple transactions representing multiple ISBNs. The records for each ISBN should be grouped together.

```c++
1.6小节中的示例程序的思路就是题目1.23的答案
```

**Exercise 1.25:** Using the Sales_item.h header from the Web site, compile and execute the bookstore program presented in this section.