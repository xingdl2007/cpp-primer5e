//
// Created by xing on 4/9/18.
//

#ifndef PROJECT_LOCK_H
#define PROJECT_LOCK_H

#include <pthread.h>
#include <semaphore.h>
#include <exception>

class SEM {
public:
  SEM() {
    if (sem_init(&sem, 0, 0) == 0) {
      throw std::exception();
    }
  }
  ~SEM() {
    sem_destroy(&sem);
  }
  bool wait() {
    return sem_wait(&sem) == 0;
  }
  bool post() {
    return sem_post(&sem) == 0;
  }
private:
  sem_t sem;
};

class Mutex {
public:
  Mutex() {
    if (pthread_mutex_init(&mutex, nullptr) != 0) {
      throw std::exception();
    }
  }
  ~Mutex() {
    pthread_mutex_destroy(&mutex);
  }
  bool lock() {
    return pthread_mutex_lock(&mutex) == 0;
  }
  bool unlock() {
    return pthread_mutex_unlock(&mutex) == 0;
  }
private:
  pthread_mutex_t mutex;
};

class Cond {
public:
  Cond() {
    if (pthread_mutex_init(&mutex, nullptr) != 0) {
      throw std::exception();
    }
    if (pthread_cond_init(&cond, nullptr) != 0) {
      pthread_mutex_destroy(&mutex);
      throw std::exception();
    }
  }
  ~Cond() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
  }
  bool signal() {
    // which no need to hold the mutex
    return pthread_cond_signal(&cond) == 0;
  }
  bool wait() {
    int ret = 0;
    pthread_mutex_lock(&mutex);
    ret = pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
    return ret == 0;
  }
private:
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

#endif //PROJECT_LOCK_H
