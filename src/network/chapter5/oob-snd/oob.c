//
// Created by xing on 4/3/18.
//
#include <stdio.h>
#include <libgen.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_num\n", basename(argv[0]));
  }
  const char *ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(sockfd >= 0);
  if (connect(sockfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
    printf("connection failed.\n");
  } else {
    const char *oob_data = "abc";
    const char *normal_data = "123";
    send(sockfd, normal_data, strlen(normal_data), 0);
    send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
    send(sockfd, normal_data, strlen(normal_data), 0);
  }
  close(sockfd);
  return 0;
}