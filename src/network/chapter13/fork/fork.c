//
// Created by xing on 4/4/18.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {
    printf("child: %d\n", getpid());
  } else {
    sleep(1);
    printf("parent: %d\n", getpid());
  }
  return 0;
}