//
// Created by xing on 4/4/18.
//

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

class Foo {
public:
  void doit() {
    printf("do it.\n");
  }
  ~Foo() {
    printf("~Foo().\n");
  }
};

int main() {
  Foo foo;
  fork();
  foo.doit();
  return 0;
}