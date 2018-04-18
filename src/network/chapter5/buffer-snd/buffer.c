//
// Created by xing on 4/3/18.
//

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#define BUFFER_SIZE 5120

int main(int argc, char *argv[]) {
  if (argc <= 3) {
    printf("usage: %s ip_address port_num send_buffer_size\n", basename(argv[0]));
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

  int sendbuf = atoi(argv[3]);
  int len = sizeof(sendbuf);
  setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, len);
  getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *) &len);
  printf("the tcp send buffer size after setting is %d\n", sendbuf);

  // output: 1
  int water;
  getsockopt(sock, SOL_SOCKET, SO_SNDLOWAT, &water, &len);
  printf("tcp send low water is: %d\n", water);

  // output: 1
  getsockopt(sock, SOL_SOCKET, SO_RCVLOWAT, &water, &len);
  printf("tcp receive low water is: %d\n", water);

  if (connect(sock, (struct sockaddr *) &address, sizeof(address)) != -1) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 'a', BUFFER_SIZE);
    send(sock, buffer, BUFFER_SIZE, 0);
  }
  close(sock);
  return 0;
}