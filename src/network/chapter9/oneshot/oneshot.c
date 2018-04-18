//
// Created by xing on 4/8/18.
// epoll oneshot demo

#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libgen.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <errno.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 2014

struct fds {
  int epollfd;
  int sockfd;
};

// fd is non-blocking IO
int SetNonBlocking(int fd) {
  int old_option = fcntl(fd, F_GETFL);
  int new_option = old_option | O_NONBLOCK;
  int ret = fcntl(fd, F_SETFL, new_option);
  assert(ret != -1);
  return old_option;
}

// add to epoll's event queue, for client socket
void Addfd(int epollfd, int fd, bool oneshot) {
  struct epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  if (oneshot) {
    event.events |= EPOLLONESHOT;
  }
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  SetNonBlocking(fd);
}

// reset OneShot
void ResetOneShot(int epollfd, int fd) {
  struct epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
  epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

void *worker(void *arg) {
  int sockfd = ((struct fds *) arg)->sockfd;
  int epollfd = ((struct fds *) arg)->epollfd;

  printf("[%ld] start new thread to receive data on fd: %d\n", syscall(__NR_gettid), sockfd);
  char buf[BUFFER_SIZE];
  while (true) {
    memset(buf, '\0', sizeof(buf));
    long int ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
    if (ret == 0) {
      close(sockfd);
      printf("foreign closed the connection\n");
      break;
    } else if (ret < 0) {
      if (errno == EAGAIN) {
        // done with this socket
        ResetOneShot(epollfd, sockfd);
        printf("read later(possibly with another thread)\n");
        break;
      }
    } else {
      printf("get content: %s\n", buf);
      // processing received data
      sleep(5);
    }
  }
  printf("[%ld] end thread receiving data on fd: %d\n", syscall(__NR_gettid), sockfd);
}

// main function
int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_number\n", basename(argv[1]));
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

  struct epoll_event events[MAX_EVENT_NUMBER];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  Addfd(epollfd, listenfd, false);

  while (true) {
    ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if (ret < 0) {
      printf("epoll failed: %s\n", strerror(errno));
      break;
    }

    for (int i = 0; i < ret; ++i) {
      int sockfd = events[i].data.fd;
      if (sockfd == listenfd) {
        // accetp
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int connfd = accept(listenfd, (struct sockaddr *) &client, &len);
        if (connfd >= 0) {
          Addfd(epollfd, connfd, true);
        }
      } else if (events[i].events & EPOLLIN) {
        // start new thread
        pthread_t thread;
        struct fds for_worker;
        for_worker.epollfd = epollfd;
        for_worker.sockfd = sockfd;

        // will copy arguments?
        pthread_create(&thread, NULL, worker, (void *) &for_worker);
      } else {
        printf("something else happened.\n");
      }
    }
  }
  close(listenfd);
  return 0;
}