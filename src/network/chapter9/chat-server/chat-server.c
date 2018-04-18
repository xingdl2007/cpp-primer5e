//
// Created by xing on 4/8/18.
// chat server, demo poll usage

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <libgen.h>
#include <stdbool.h>
#include <sys/poll.h>

#define USER_LIMIT  2   // limit possible user cnt
#define BUFFER_SIZE 64
#define FD_LIMIT    10  // indexed by connfd

struct client_data {
  struct sockaddr_in address;
  char *write_buf;
  char buf[BUFFER_SIZE];
};

int SetNonBlocking(int fd) {
  int old_option = fcntl(fd, F_GETFL);
  int new_option = old_option | O_NONBLOCK;
  int ret = fcntl(fd, F_SETFL, new_option);
  assert(ret != -1);
  return old_option;
}

// store all users' info
static struct client_data users[FD_LIMIT];
static struct pollfd fds[USER_LIMIT + 1];
static int user_count = 0;

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

  int ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
  assert(ret != -1);

  ret = listen(listenfd, USER_LIMIT);
  assert(ret != -1);

  for (int i = 1; i <= USER_LIMIT; ++i) {
    fds[i].fd = -1;
    fds[i].events = 0;
  }
  fds[0].fd = listenfd;
  fds[0].events = POLLIN | POLLERR;
  fds[0].revents = 0;

  while (true) {
    ret = poll(fds, user_count + 1, -1);
    if (ret < 0) {
      printf("poll failed: %s\n", strerror(errno));
      break;
    }

    // +1 for listening socket
    for (int i = 0; i < user_count + 1; ++i) {
      if (fds[i].fd == listenfd && fds[i].revents & POLLIN) {
        // new connection
        struct sockaddr_in client_address;
        socklen_t addr_len = sizeof(client_address);
        int connfd = accept(listenfd, (struct sockaddr *) &client_address, &addr_len);
        if (connfd < 0) {
          printf("accept error: %s\n", strerror(errno));
          continue;
        }
        if (user_count >= USER_LIMIT) {
          const char *msg = "too many user\n";
          printf("%s", msg);
          send(connfd, msg, strlen(msg), 0);
          close(connfd);
          continue;
        }
        user_count++;
        // indexed user with connfd, which may not start from 0
        users[connfd].address = client_address;
        SetNonBlocking(connfd);

        fds[user_count].fd = connfd;
        fds[user_count].events = POLLIN | POLLERR | POLLRDHUP;
        fds[user_count].revents = 0;
        printf("comes a new user, now have %d users\n", user_count);
      } else if (fds[i].revents & POLLERR) {
        // error ??
        printf("get an error from %d\n", fds[i].fd);
        char errors[BUFFER_SIZE];
        memset(errors, '\0', BUFFER_SIZE);
        socklen_t length = sizeof(errors);

        // get the error and continue
        if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length)) {
          printf("get socket option failed: %s\n", strerror(errno));
        }
        continue;
      } else if (fds[i].revents & POLLRDHUP) {
        // client close connection
        users[fds[i].fd] = users[fds[user_count].fd];
        close(fds[i].fd);
        fds[i] = fds[user_count];
        --i;
        --user_count;
        printf("a client left\n");
      } else if (fds[i].revents & POLLIN) {
        // readable
        int connfd = fds[i].fd;
        memset(users[connfd].buf, '\0', BUFFER_SIZE);
        ret = recv(connfd, users[connfd].buf, BUFFER_SIZE - 1, 0);
        printf("get %d bytes from client %d\n", ret, connfd);
        if (ret <= 0) {
          close(connfd);
          users[connfd] = users[fds[user_count].fd];
          fds[i] = fds[user_count];
          --i;
          --user_count;
        } else {
          for (int j = 1; j <= user_count; ++j) {
            if (fds[j].fd == connfd) {
              continue;
            }
            fds[j].events &= ~POLLIN;  // clear POLLIN
            fds[j].events |= POLLOUT;
            users[fds[j].fd].write_buf = users[connfd].buf;
          }
        }

      } else if (fds[i].revents & POLLOUT) {
        // writable
        int connfd = fds[i].fd;
        if (!users[connfd].write_buf) {
          continue;
        }
        ret = send(connfd, users[connfd].write_buf, strlen(users[connfd].write_buf), 0);
        users[connfd].write_buf = NULL;
        fds[i].events &= ~POLLOUT; // clear POLLOUT
        fds[i].events |= POLLIN;
      }
    }
  }
  close(listenfd);
  return 0;
}
