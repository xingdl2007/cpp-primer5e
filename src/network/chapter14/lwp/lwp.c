//
// Created by xing on 4/9/18.
//

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

pthread_mutex_t mutex;

void *another(void *arg) {
  printf("in child process, lock the mutex\n");
  pthread_mutex_lock(&mutex);
  sleep(5);
  pthread_mutex_unlock(&mutex);
}

void prepare() {
  pthread_mutex_lock(&mutex);
}
void infork() {
  pthread_mutex_unlock(&mutex);
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_t id;
  pthread_create(&id, NULL, another, NULL);
  sleep(1);

  // interesting
  pthread_atfork(prepare, infork, infork);
  int pid = fork();
  if (pid < 0) {
    pthread_join(id, NULL);
    pthread_mutex_destroy(&mutex);
    return 1;
  } else if (pid == 0) {
    // in child
    printf("I am in the child, want to get the lock\n");
    pthread_mutex_lock(&mutex);
    printf("I can not run to here, oop...(if not call pthread_atfork())\n");
    pthread_mutex_destroy(&mutex);
    exit(0);
  } else {
    wait(NULL);
  }
  pthread_join(id, NULL);
  pthread_mutex_destroy(&mutex);
  return 0;
}
