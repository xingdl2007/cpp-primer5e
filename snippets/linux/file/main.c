#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd = open("output.txt", O_CREAT | O_WRONLY | O_SYNC | O_DIRECT, 0666);
  pid_t pid = getpid();
  printf("%d\n", pid);
  char data[100];
  memset(data, 0, sizeof(data));
  int n = sprintf(data, "%d", pid);
  data[n] = '\n';
  write(fd, "a: ", 2);
  write(fd, data, n + 1);
  sleep(1);
  write(fd, "b: ", 2);
  write(fd, data, n + 1);
  write(fd, "c: ", 2);
  write(fd, data, n + 1);
  sleep(1);
  write(fd, "d: ", 2);
  write(fd, data, n + 1);
  sleep(1);
  write(fd, "e: ", 2);
  write(fd, data, n + 1);
  sleep(1);
  write(fd, "f: ", 2);
  write(fd, data, n + 1);
}
