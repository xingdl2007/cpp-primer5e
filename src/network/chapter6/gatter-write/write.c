//
// Created by xing on 4/7/18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024

static const char *status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char *argv[]) {
  if (argc <= 3) {
    printf("usage: %s ip_address port_num filename\n", basename(argv[0]));
    return 1;
  }

  const char *ip = argv[1];
  int port = atoi(argv[2]);
  const char *file_name = argv[3];

  struct sockaddr_in address;
  bzero(&address, sizeof(address));
  address.sin_family = AF_INET;
  inet_aton(ip, &address.sin_addr);
  address.sin_port = htons(port);

  int sock = socket(PF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);

  int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
  if (ret < 0) {
    printf("errno is: %s\n", strerror(errno));
    assert(ret != -1);
  }

  ret = listen(sock, 5);
  assert(ret != -1);

  struct sockaddr_in client;
  int client_addrlen = sizeof(client);
  int connfd = accept(sock, (struct sockaddr *) &client, &client_addrlen);
  if (connfd < 0) {
    printf("errno is: %d\n", errno);
  } else {
    char header_buf[BUFFER_SIZE];
    memset(header_buf, '\0', BUFFER_SIZE);

    char *file_buf = 0;
    struct stat file_stat;
    bool valid = true;
    int len = 0;

    // file does not exist
    if (stat(file_name, &file_stat) < 0) {
      valid = false;
    } else {
      // directory?
      if (S_ISDIR(file_stat.st_mode)) {
        valid = false;
      } else if (file_stat.st_mode & S_IROTH) {
        int fd = open(file_name, O_RDONLY);
        file_buf = malloc(file_stat.st_size + 1);
        memset(file_buf, '\0', file_stat.st_size + 1);
        if (read(fd, file_buf, file_stat.st_size) < 0) {
          valid = false;
        }
      } else {
        valid = false;
      }
    }

    if (valid && file_buf) {
      ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n",
                     "HTTP/1.1", status_line[0]);
      len += ret;
      ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len,
                     "Content-Length: %ld\r\n", file_stat.st_size);

      len += ret;
      // blank line
      ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");

      struct iovec iv[2];
      iv[0].iov_base = header_buf;
      iv[0].iov_len = strlen(header_buf);

      iv[1].iov_base = file_buf;
      iv[1].iov_len = file_stat.st_size;
      ret = writev(connfd, iv, 2);
    } else {
      ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n",
                     "HTTP/1.1", status_line[1]);
      len += ret;
      ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");
      send(connfd, header_buf, strlen(header_buf), 0);
    }
    close(connfd);
    if (file_buf) {
      free(file_buf);
    }
  }
  close(sock);
  return 0;
}
