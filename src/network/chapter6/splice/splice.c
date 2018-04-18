//
// Created by xing on 4/7/18.
//

#define _GNU_SOURCE

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_num\n", basename(argv[0]));
    return 1;
  }

  const char *ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);

  int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
  if (ret < 0) {
    printf("errno is: %s\n", strerror(errno));
    assert(ret != -1);
  }

  ret = listen(sock, 5);
  assert(ret != -1);

  struct sockaddr_in client;
  int client_addrlen = sizeof(client);
  int connfd = accept(sock, (struct sockaddr *) &client, &client_addrlen);
  if (connfd < 0) {
    printf("errno is: %d\n", errno);
  } else {
    int pipefd[2];
    ret = pipe(pipefd);
    assert(ret != -1);
    ret = splice(connfd, 0, pipefd[1], 0, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
    assert(ret != -1);
    ret = splice(pipefd[0], 0, connfd, 0, 32768, SPLICE_F_MOVE | SPLICE_F_MORE);
    assert(ret != -1);
    close(connfd);
  }
  close(sock);
  return 0;
}
