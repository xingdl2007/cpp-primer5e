//
// Created by xing on 4/9/18.
//

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>
#include <libgen.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int timeout_connection(const char *ip, int port, int time) {
  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int sockfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(sockfd >= 0);

  struct timeval timeout;
  timeout.tv_sec = time;  // second
  timeout.tv_usec = 0;    // microsecond

  int ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
  assert(ret != -1);

  ret = connect(sockfd, (struct sockaddr *) &address, sizeof(address));
  if (ret < 0) {
    if (errno == EINPROGRESS) {
      printf("connecting timeout, process timeout logic\n");
      return -1;
    }
    printf("error occur when connecting to server: %s\n", strerror(errno));
    return -1;
  }
  return sockfd;
}

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[0]));
    return 1;
  }
  const char *ip = argv[1];
  int port = atoi(argv[2]);

  // 1 second
  int sockfd = timeout_connection(ip, port, 1);
  if (sockfd < 0) {
    return 1;
  }
  close(sockfd);
  return 0;
}