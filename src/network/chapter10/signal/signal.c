//
// Created by xing on 4/8/18.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>

#define MAX_EVENT_NUMBER 1024
static int pipefd[2];

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

int main(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("usage: %s ip_address port_num\n", basename(argv[0]));
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

  int ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(listenfd, 5);
  assert(ret != -1);

  // epoll related
  struct epoll_event events[MAX_EVENT_NUMBER];
  int epollfd = epoll_create(5);
  assert(epollfd != -1);
  Addfd(epollfd, listenfd);

  // create bi-direction pipe
  ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
  assert(ret != -1);
  SetNonBlocking(pipefd[1]);
  Addfd(epollfd, pipefd[0]);

  // sig related
  AddSig(SIGHUP);
  AddSig(SIGCHLD);
  AddSig(SIGTERM);
  AddSig(SIGINT);
  AddSig(SIGQUIT);
  bool stop_server = false;

  while (!stop_server) {
    int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
    if (number < 0 && errno != EINTR) {
      printf("epoll failed: %s\n", strerror(errno));
      break;
    }
    printf("%d events.\n", number);
    for (int i = 0; i < number; ++i) {
      int sockfd = events[i].data.fd;
      if (sockfd == listenfd) {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int connfd = accept(listenfd, (struct sockaddr *) &client, &len);
        if (connfd > 0) {
          Addfd(epollfd, connfd);
        }
      } else if (sockfd == pipefd[0] && events[i].events & EPOLLIN) {
        printf("signal hit\n");
        int sig;
        char signals[1024];
        ret = recv(pipefd[0], signals, sizeof(signals), 0);
        if (ret == -1 || ret == 0) {
          continue;
        } else {
          for (int i = 0; i < ret; ++i) {
            switch (signals[i]) {
            case SIGCHLD:
            case SIGHUP:continue;
            case SIGTERM:
            case SIGINT:
            case SIGQUIT:
            default:stop_server = true;
              break;
            }
          }
        }
      } else {
        // ignore normal data
        char *buf = "hello? byte!\n";
        send(sockfd, buf, strlen(buf), 0);
      }
    }
  }
  printf("close fds\n");
  close(listenfd);
  close(pipefd[1]);
  close(pipefd[0]);
  return 0;
}