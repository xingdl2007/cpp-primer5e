//
// Created by xing on 4/4/18.
//

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void sig_handler(int sig) {
  pid_t pid;
  int stat;
  if ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
    printf("child process exit: %d\n", stat);
  }
}

int main() {
  signal(SIGCHLD, sig_handler);
  pid_t pid = fork();

  if (pid == 0) {
    printf("child: %d\n", getpid());
  } else {
    sleep(1);
    printf("parent: %d\n", getpid());
  }
  return 0;
}