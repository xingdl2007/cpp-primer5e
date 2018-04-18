//
// Created by xing on 4/9/18.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>

#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "timer_wheel.h"

#define FD_LIMIT 10
#define MAX_EVENT_NUMBER 32
#define TIMESLOT 2

static int pipefd[2];
static TimerWheel timer_wheel;
static int epollfd = -1;

int SetNonBlocking(int fd) {
  int old_option = fcntl(fd, F_GETFL);
  int new_option = old_option | O_NONBLOCK;
  fcntl(fd, F_SETFL, new_option);
  return old_option;
}

// best practice
void Addfd(int epollfd, int fd) {
  struct epoll_event event;
  event.data.fd = fd;
  event.events = EPOLLIN | EPOLLET;
  epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
  SetNonBlocking(fd);
}

void SigHandler(int sig) {
  printf("SigHandler\n");
  int save_errno = errno;
  int msg = sig; // works on little endian platform
  send(pipefd[1], (char *) &msg, 1, 0);
  errno = save_errno;
}

void AddSig(int sig) {
  struct sigaction sa;
  bzero(&sa, sizeof(sa));
  sa.sa_handler = SigHandler;
  sa.sa_flags |= SA_RESTART;
  sigfillset(&sa.sa_mask);    // why all masked?
  sigaction(sig, &sa, NULL);

  // for debug
  bzero(&sa, sizeof(sa));
  // get current signal mask after setting
  sigprocmask(SIG_BLOCK, NULL, &sa.sa_mask);
  if (sigismember(&sa.sa_mask, sig)) {
    printf("Oops: %d is masked?\n", sig);
  } else {
    printf("OK\n");
  }
}

// timer task processing
void timeout_handler() {
  timer_wheel.tick();
  // 5 second
  alarm(TIMESLOT);
}

void callback_func(client_data *data) {
  assert(data);
  // delete client connection from epoll event table
  epoll_ctl(epollfd, EPOLL_CTL_DEL, data->sockfd, 0);
  close(data->sockfd);
  printf("close client %d\n", data->sockfd);
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

  int listenfd = socket(PF_INET, SOCK_STREAM, 0);
  assert(listenfd >= 0);

  long int ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(listenfd, 5);
  assert(ret != -1);

  struct epoll_event events[MAX_EVENT_NUMBER];
  epollfd = epoll_create(5);
  assert(epollfd != -1);
  Addfd(epollfd, listenfd);

  ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
  assert(ret != -1);
  SetNonBlocking(pipefd[1]);
  Addfd(epollfd, pipefd[0]);

  AddSig(SIGALRM);
  AddSig(SIGTERM);
  bool stop_server = false;

  // pre-allocated
  auto *user_data = new client_data[FD_LIMIT];
  bool timeout = false;   // just a flag, some connection is timeout
  alarm(TIMESLOT);        // start timer, one shot

  while (!stop_server) {
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if (number < 0 && errno != EINTR) {
      printf("epoll failed: %s\n", strerror(errno));
      break;
    }
    for (int i = 0; i < number; ++i) {
      int sockfd = events[i].data.fd;
      if (sockfd == listenfd) {
        struct sockaddr_in client{};
        socklen_t len = sizeof(client);
        int connfd = accept(listenfd, (struct sockaddr *) &client, &len);
        if (connfd >= 0) {
          Addfd(epollfd, connfd);

          user_data[connfd].address = client;
          user_data[connfd].sockfd = connfd;

          auto *timer = timer_wheel.add_timer(3 * TIMESLOT);
          timer->cb_func = callback_func;
          timer->user_data = &user_data[connfd];
          user_data[connfd].timer = timer;
        }
      } else if (sockfd == pipefd[0] && events[i].events & EPOLLIN) {
        char signals[1024];
        ret = recv(pipefd[0], signals, sizeof(signals), 0);
        if (ret == -1 || ret == 0) {
          continue;
        } else {
          for (long int j = 0; j < ret; ++j) {
            switch (signals[j]) {
            case SIGALRM: timeout = true;
              break;
            case SIGTERM:
            case SIGINT:
            case SIGQUIT:
            default:stop_server = true;
              break;
            }
          }
        }
      } else if (events[i].events & EPOLLIN) {
        memset(user_data[sockfd].buf, '\0', BUFFER_SIZE);
        ret = recv(sockfd, user_data[sockfd].buf, BUFFER_SIZE - 1, 0);
        printf("get %ld bytes of client data %s from %d\n",
               ret, user_data[sockfd].buf, sockfd);
        // active connection
        auto *timer = user_data[sockfd].timer;
        if (ret <= 0) {
          // close connection
          callback_func(&user_data[sockfd]);
          if (timer) {
            timer_wheel.del_timer(timer);
          }
        } else {
          if (timer) {
            timer_wheel.del_timer(timer);
            printf("allocate new timer replace the old one");
            auto *new_timer = timer_wheel.add_timer(3 * TIMESLOT);
            user_data[sockfd].timer = new_timer;
          }
        }
      }
    }
    // some connection is timeout
    if (timeout) {
      timeout_handler();
      timeout = false;
    }
  }
  close(listenfd);
  close(pipefd[1]);
  close(pipefd[0]);
  delete[]user_data;
  return 0;
}
