//
// Created by xing on 4/8/18.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/select.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_num\n", basename(argv[0]));
    return 1;
  }
  const char *ip = argv[1];
  int port = atoi(argv[2]);
  int ret = 0;

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int listenfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(listenfd >= 0);
  ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(listenfd, 5);
  assert(ret != -1);

  struct sockaddr_in client_address;
  socklen_t client_addrlength = sizeof(client_address);
  int connfd = accept(listenfd, (struct sockaddr *) &client_address, &client_addrlength);
  if (connfd < 0) {
    printf("error: %s\n", strerror(errno));
    return -1;
  }

  char buf[1024];
  fd_set read_fds, exception_fds;
  while (true) {
    memset(buf, '\0', sizeof(buf));
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);
    FD_SET(connfd, &read_fds);
    FD_SET(connfd, &exception_fds);

    // wait until data comes
    ret = select(connfd + 1, &read_fds, NULL, &exception_fds, NULL);
    if (ret < 0) {
      printf("select error: %s\n", strerror(errno));
      break;
    }
    if (FD_ISSET(connfd, &read_fds)) {
      // normal data
      ret = recv(connfd, buf, sizeof(buf) - 1, 0);
      if (ret <= 0) {
        break;
      }
      printf("get %d bytes of normal data: %s\n", ret, buf);
    } else if (FD_ISSET(connfd, &exception_fds)) {
      // out-of-bound data
      ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
      if (ret <= 0) {
        break;
      }
      printf("get %d bytes of oob data: %s\n", ret, buf);
    }
  }
  close(connfd);
  close(listenfd);
  return 0;
}
