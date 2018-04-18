//
// Created by xing on 4/9/18.
//

#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

#include <netinet/in.h>
#include <ctime>

#define BUFFER_SIZE 64

class util_timer;
struct client_data {
  struct sockaddr_in address;
  int sockfd;
  char buf[BUFFER_SIZE];
  util_timer *timer;     // interesting
};

struct util_timer {
  util_timer() : prev(nullptr), next(nullptr) {}

  // expire time, absolute time, second
  time_t expire;

  // callback function
  void (*cb_func)(client_data *);
  client_data *user_data;

  util_timer *prev;
  util_timer *next;
};

class SortedTimerList {
public:
  SortedTimerList() = default;

  // disable copy
  SortedTimerList(SortedTimerList const &) = delete;
  SortedTimerList &operator=(SortedTimerList const &) = delete;

  ~SortedTimerList() {
    util_timer *tmp = head;
    while (tmp) {
      head = tmp->next;
      delete tmp;
      tmp = head;
    }
  }

  // maintain sorted order
  void add_timer(util_timer *timer);
  void adjust_timer(util_timer *timer);
  void del_timer(util_timer *timer);
  void tick();

private:
  // helper function
  void add_timer(util_timer *timer, util_timer *lst_head);

  util_timer *head{nullptr};
  util_timer *tail{nullptr};
};

#endif //PROJECT_TIMER_H
