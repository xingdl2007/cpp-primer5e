//
// Created by xing on 4/3/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  if (argc <= 3) {
    printf("usage: %s ip_address port_number recv_buffer_size\n", basename(argv[0]));
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

  int recvbuf = atoi(argv[3]);
  int len = sizeof(recvbuf);

  setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
  getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, &len);
  printf("the tcp receive buffer size after setting is %d\n", recvbuf);

  int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(sock, 5);
  assert(ret != -1);

  struct sockaddr_in client;
  int client_addrlen = sizeof(client);
  int connfd = accept(sock, (struct sockaddr *) &client, &client_addrlen);
  if (connfd < 0) {
    printf("connection failed, errno: %d\n", errno);
  } else {
    char buffer[BUFFER_SIZE];
    memset(buffer, '\0', BUFFER_SIZE);
    int len;
    while ((len = recv(connfd, buffer, BUFFER_SIZE, 0)) > 0) {
      printf("server receive %d bytes.\n", len);
    }
    close(connfd);
  }
  close(sock);
  return 0;
}