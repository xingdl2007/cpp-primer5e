#include <stdio.h>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <chrono>
#include <map>

#define BINARY_OP(op) #op
#define CONCAT(a, b) a##b

#define Barrier() __asm__ __volatile__("" :: \
                                           : "memory");

using namespace std;

void AppendEscapedStringTo(std::string *str, const char *value)
{
  for (size_t i = 0; i < 5; i++)
  {
    char c = value[i];
    if (c >= ' ' && c <= '~')
    {
      str->push_back(c);
    }
    else
    {
      char buf[10];
      snprintf(buf, sizeof(buf), "\\x%02x",
               static_cast<unsigned int>(c) & 0xff);
      str->append(buf);
    }
  }
}

int main()
{
  int ab = 0;
  cout << BINARY_OP(==) << endl;
  cout << CONCAT(a, b) << endl;
  Barrier();

  std::string test;
  char value[] = {0x1, 0x2, 0xf, 0xf, 0x8};
  AppendEscapedStringTo(&test, value);
  cout << test << endl;
  {
    int *a = new int(42);

    // why another indirect layer?
    std::shared_ptr<int *> ptr(new int *(a));
    cout << *ptr << endl;
  }

  std::stack<std::unique_ptr<int>> istk;
  std::unique_ptr<int> ua(new int(4));
  std::unique_ptr<int> ub(new int(100));

  istk.push(std::move(ua));
  istk.push(std::move(ub));

  ua = std::move(istk.top());
  istk.pop();
  ub = std::move(istk.top());
  istk.pop();

  std::unique_ptr<int> uc(std::move(ua));
  std::cout << *uc << " " << *ub << std::endl;

  // 1, 8, 8
  std::cout << sizeof(std::chrono::system_clock) << std::endl;
  std::cout << sizeof(std::chrono::system_clock::time_point) << std::endl;
  std::cout << sizeof(std::chrono::system_clock::duration) << std::endl;

  // ratio<1, 1000>
  std::chrono::milliseconds::period p;
  std::cout << p.num << " " << p.den << std::endl;

  std::cout << sizeof(struct timeval) << std::endl;
  return 0;
}
