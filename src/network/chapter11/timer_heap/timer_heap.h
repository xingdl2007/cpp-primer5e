//
// Created by xing on 4/9/18.
//
#ifndef PROJECT_TIMER_HEAP_H
#define PROJECT_TIMER_HEAP_H

#include <iostream>
#include <set>

#include <netinet/in.h>
#include <time.h>
#include <memory>

#define BUFFER_SIZE 64

class Timer;
struct client_data {
  struct sockaddr_in address;
  int sockfd;
  char buf[BUFFER_SIZE];
  std::shared_ptr<Timer> timer;
};

struct Timer {
  Timer(int delay) {
    expire = time(nullptr) + delay;
  }
  time_t expire;
  void (*cb_func)(client_data *);
  client_data *user_data;
};

bool operator<(Timer const &lhs, Timer const &rhs) {
  return lhs.expire < rhs.expire;
}

class TimerHeap {
public:
  // maintain sorted order
  void add_timer(std::shared_ptr<Timer> timer) {
    container.insert(timer);
  }

  void del_timer(std::shared_ptr<Timer> timer) {
    if (container.count(timer)) {
      container.erase(timer);
    } else {
      printf("del_timer(): try to delete non exist timer\n");
    }
  }

  void tick() {
    time_t cur = time(nullptr);
    for (auto it = container.begin(); it != container.end();) {
      if ((*it)->expire <= cur) {
        auto timer = *it;
        timer->cb_func(timer->user_data);
        it = container.erase(it);
      } else {
        break;
      }
    }
  }
private:
  std::multiset<std::shared_ptr<Timer>> container;
};

#endif //PROJECT_TIMER_HEAP_H
