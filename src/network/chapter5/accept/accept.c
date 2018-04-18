//
// Created by xing on 4/3/18.
//

#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[0]));
    return 1;
  }

  const char *ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in address;
  bzero(&address, sizeof(struct sockaddr_in));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);
  int reuse = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

  int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(sock, 5);
  assert(ret != -1);

  // sleep 20s
  sleep(20);

  struct sockaddr_in client;
  socklen_t client_addrlength = sizeof(client);
  int connfd = accept(sock, (struct sockaddr *) &client, &client_addrlength);
  if (connfd < 0) {
    printf("error is: %d\n", errno);
  } else {
    printf("connected with ip: %s and port: %d\n", inet_ntoa(client.sin_addr),
           ntohs(client.sin_port));
    close(connfd);
  }
  return 0;
}