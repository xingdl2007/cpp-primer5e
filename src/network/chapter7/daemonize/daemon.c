//
// Created by xing on 4/7/18.
//

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

bool daemonize() {
  pid_t pid = fork();
  if (pid < 0) {
    return false;
  } else if (pid > 0) {
    // father exit
    exit(0);
  }

  umask(0);
  pid_t sid = setsid();
  if (sid < 0) {
    return false;
  }

  if ((chdir("/")) < 0) {
    return false;
  }

  printf("last msg from child: pid %d,sid %d\n", getpid(), getsid(getpid()));

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  open("/dev/null", O_RDONLY);
  open("/dev/null", O_RDWR);
  open("/dev/null", O_RDWR);

  return true;
}

int main() {
  daemonize();
}
