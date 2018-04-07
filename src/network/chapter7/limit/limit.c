//
// Created by xing on 4/7/18.
//

#include <sys/resource.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
  struct rlimit limit;
  bzero(&limit, sizeof(limit));
  int ret = getrlimit(RLIMIT_CPU, &limit);
  assert(ret != -1);
  printf("CPU soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_AS, &limit);
  assert(ret != -1);
  printf("AS soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_CORE, &limit);
  assert(ret != -1);
  printf("Core soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_DATA, &limit);
  assert(ret != -1);
  printf("Data soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_FSIZE, &limit);
  assert(ret != -1);
  printf("FSIZE soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_NOFILE, &limit);
  assert(ret != -1);
  printf("NOFILE soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_NPROC, &limit);
  assert(ret != -1);
  printf("NPROC soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_SIGPENDING, &limit);
  assert(ret != -1);
  printf("Sigpending soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);

  ret = getrlimit(RLIMIT_STACK, &limit);
  assert(ret != -1);
  printf("Stack soft: %ld, hard: %ld\n", limit.rlim_cur, limit.rlim_max);   // -1, -1
  return 0;
}
