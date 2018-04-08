//
// Created by xing on 4/8/18.
//

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <libgen.h>
#include <fcntl.h>
#include <assert.h>

#define BUFFER_SIZE 64

// chat client, demo with poll
int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[0]));
    return 1;
  }
  const char *ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in server;
  bzero(&server, sizeof(server));
  server.sin_family = AF_INET;
  inet_aton(ip, &server.sin_addr);
  server.sin_port = htons(port);

  int connfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(connfd > 0);

  int ret = connect(connfd, (struct sockaddr *) &server, sizeof(server));
  assert(ret != -1);

  struct pollfd event[2];
  // for input
  event[0].fd = STDIN_FILENO;
  event[0].events = POLLIN;
  event[0].revents = 0;

  // for chat, why no POLLOUT?
  event[1].fd = connfd;
  event[1].events = POLLIN | POLLRDHUP;
  event[1].revents = 0;

  char read_buf[BUFFER_SIZE];
  int pipefd[2];
  ret = pipe(pipefd);
  assert(ret != -1);

  while (true) {
    ret = poll(event, 2, -1);
    if (ret < 0) {
      printf("poll error: %s\n", strerror(errno));
      break;
    }

    // chat
    if (event[1].revents & POLLRDHUP) {
      char error[BUFFER_SIZE];
      int ret = recv(connfd, error, BUFFER_SIZE - 1, 0);
      if (ret > 0) {
        printf("%s", error);
      }
      printf("Server closed the connection\n");
      break;
    } else if (event[1].revents & POLLIN) {
      memset(read_buf, '\0', sizeof(read_buf));
      recv(connfd, read_buf, sizeof(read_buf) - 1, 0);
      printf("%s", read_buf);
    }

    // user input
    if (event[0].revents & POLLIN) {
      splice(event[0].fd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE);
      splice(pipefd[0], NULL, connfd, NULL, 32768, SPLICE_F_MORE);
    }
  }
  close(connfd);
  return 0;
}
