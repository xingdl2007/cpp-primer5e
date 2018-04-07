//
// Created by xing on 4/7/18.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  if (argc <= 3) {
    printf("usage: %s ip_address port_num filename\n", basename(argv[0]));
    return 1;
  }

  const char *ip = argv[1];
  int port = atoi(argv[2]);
  const char *file_name = argv[3];

  int filefd = open(file_name, O_RDONLY);
  assert(filefd > 0);
  struct stat stat_buf;
  fstat(filefd, &stat_buf);

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
    sendfile(connfd, filefd, 0, stat_buf.st_size);
    close(connfd);
  }
  close(sock);
  return 0;
}
