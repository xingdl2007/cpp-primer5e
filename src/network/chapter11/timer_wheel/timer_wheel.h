//
// Created by xing on 4/9/18.
//

#ifndef PROJECT_TIMER_WHEEL_H
#define PROJECT_TIMER_WHEEL_H

#include <time.h>
#include <netinet/in.h>
#include <stdio.h>

#define BUFFER_SIZE 64
class Timer;

struct client_data {
  sockaddr_in address;
  int sockfd;
  char buf[BUFFER_SIZE];
  Timer *timer;
};

struct Timer {
  Timer(int r, int s) : rotation(r), time_slot(s) {}
  int rotation;
  int time_slot;

  // callback
  void (*cb_func)(client_data *);
  client_data *user_data;
  Timer *prev = nullptr, *next = nullptr;
};

// use a kind of Wheel to manage timers
class TimerWheel {
public:
  TimerWheel();
  ~TimerWheel();

  Timer *add_timer(int timeout);
  void del_timer(Timer *timer);
  void tick();

private:
  static const int N = 60;
  static const int SI = 1;
  Timer *slots[N];
  int cur_slot;
};

#endif //PROJECT_TIMER_WHEEL_H
