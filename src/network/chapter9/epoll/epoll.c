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
#include <libgen.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

// fd is non-blocking IO
int SetNonBlocking(int fd) {
  int old_option = fcntl(fd, F_GETFL);
  int new_option = old_option | O_NONBLOCK;
  int ret = fcntl(fd, F_SETFL, new_option);
  assert(ret != -1);
  return old_option;
}

// add to epoll's event queue, for client socket
void Addfd(int epollfd, int fd, bool enable_et) {
  struct epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN;
  if (enable_et) {
    event.events |= EPOLLET;
  }
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  SetNonBlocking(fd);
}

// epoll lt-mode
void lt(struct epoll_event *event, int number, int epollfd, int listenfd) {
  char buf[BUFFER_SIZE];
  for (int i = 0; i < number; ++i) {
    int sockfd = event[i].data.fd;

    if (sockfd == listenfd) {
      // new connection from listenfd
      struct sockaddr_in client_address;
      socklen_t client_addrlen = sizeof(client_address);
      int connfd = accept(listenfd, (struct sockaddr *) &client_address, &client_addrlen);
      if (connfd >= 0) {
        // add to epoll's event listening queue
        Addfd(epollfd, connfd, false);
      }
    } else if (event[i].events & EPOLLIN) {
      // readable from conn
      printf("lt-mode: event trigger once\n");
      memset(buf, '\0', sizeof(buf));
      long int ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
      if (ret <= 0) {
        // TODO: no remove?
        close(sockfd);
      }
      printf("lt-mode: get %ld bytes of content: %s\n", ret, buf);
    } else {
      printf("lt-mode: something else happened\n");
    }
  }
}

// epoll et-mode
void et(struct epoll_event *event, int number, int epollfd, int listenfd) {
  char buf[BUFFER_SIZE];
  for (int i = 0; i < number; ++i) {
    int sockfd = event[i].data.fd;
    if (sockfd == listenfd) {
      // new connection from listenfd
      struct sockaddr_in client_address;
      socklen_t client_addrlen = sizeof(client_address);
      int connfd = accept(listenfd, (struct sockaddr *) &client_address, &client_addrlen);
      if (connfd >= 0) {
        // add to epoll's event listening queue
        Addfd(epollfd, connfd, true);
      }
    } else if (event[i].events & EPOLLIN) {
      printf("et-mode: event trigger once\n");
      while (true) {
        memset(buf, '\0', sizeof(buf));
        long int ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
        if (ret < 0) {
          if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("et-mode[%d]: reader later\n\n", sockfd);
            break;
          }
        } else if (ret == 0) {
          close(sockfd);
          continue;
        } else {
          printf("et-mode[%d]: got %ld bytes of content: %s\n", sockfd, ret, buf);
        }
      }
    } else {
      printf("et-mode[%d]: something else happened\n", sockfd);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_number enable_et\n", basename(argv[0]));
    return 1;
  }
  const char *ip = argv[1];
  int port = atoi(argv[2]);
  int enable_et = atoi(argv[3]);

  int ret = 0;
  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int listenfd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  assert(listenfd >= 0);

  int reuse = 1;
  ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  assert(ret != -1);

  ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(listenfd, 5);
  assert(ret != -1);

  struct epoll_event events[MAX_EVENT_NUMBER];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  Addfd(epollfd, listenfd, true);  // enable non-blocking on listen socket

  while (true) {
    int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1); // wait forever
    if (ret < 0) {
      printf("epoll failed: %s\n", strerror(errno));
      break;
    }
    if (enable_et > 0) {
      et(events, ret, epollfd, listenfd);
    } else {
      lt(events, ret, epollfd, listenfd);
    }
  }
  close(listenfd);
  return 0;
}
