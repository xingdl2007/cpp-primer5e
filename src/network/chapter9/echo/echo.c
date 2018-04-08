//
// Created by xing on 4/8/18.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <libgen.h>
#include <strings.h>
#include <errno.h>
#include <memory.h>

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE  512
#define UDP_BUFFER_SIZE  1024

int SetNonBlocking(int fd) {
  int old_option = fcntl(fd, F_GETFL);
  int new_option = old_option | O_NONBLOCK;
  int ret = fcntl(fd, F_SETFL, new_option);
  assert(ret != -1);
  return old_option;
}

void Addfd(int epollfd, int fd) {
  struct epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  SetNonBlocking(fd);
}

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[0]));
    return 1;
  }
  const char *ip = argv[1];
  int port = atoi(argv[2]);

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  // TCP socket
  int listenfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(listenfd >= 0);

  int ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(listenfd, 5);
  assert(ret != -1);

  // UDP socket
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int udpfd = socket(PF_INET, SOCK_DGRAM, 0);
  assert(udpfd >= 0);

  ret = bind(udpfd, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  // register
  struct epoll_event events[MAX_EVENT_NUMBER];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  Addfd(epollfd, listenfd);
  Addfd(epollfd, udpfd);

  while (true) {
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if (number < 0) {
      printf("epoll failed: %s\n", strerror(errno));
      break;
    }

    for (int i = 0; i < number; ++i) {
      if (events[i].data.fd == listenfd) {
        struct sockaddr_in client;
        socklen_t addr_len = sizeof(client);
        int connfd = accept(listenfd, (struct sockaddr *) &client, &addr_len);
        if (connfd < 0) {
          continue;
        }
        Addfd(epollfd, connfd);
      } else if (events[i].data.fd == udpfd) {
        // UDP echo
        printf("UDP echo service\n");
        char buf[UDP_BUFFER_SIZE];
        memset(buf, '\0', UDP_BUFFER_SIZE);
        struct sockaddr_in client;
        socklen_t addr_len = sizeof(client);
        ret = recvfrom(udpfd, buf, UDP_BUFFER_SIZE - 1, 0, (struct sockaddr *) &client, &addr_len);
        if (ret > 0) {
          sendto(udpfd, buf, ret, 0, (struct sockaddr *) &client, addr_len);
        }
      } else if (events[i].events & EPOLLIN) {
        // TCP echo
        int sockfd = events[i].data.fd;
        printf("TCP echo service\n");
        while (true) {
          char buf[TCP_BUFFER_SIZE];
          memset(buf, '\0', TCP_BUFFER_SIZE);
          int ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
          if (ret == 0) {
            close(sockfd);
          } else if (ret < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
              continue;
            }
            close(sockfd);
            break;
          } else {
            // echo
            send(sockfd, buf, ret, 0);
          }
        }
      }
    }

  }
  close(udpfd);
  close(listenfd);
  return 0;
}