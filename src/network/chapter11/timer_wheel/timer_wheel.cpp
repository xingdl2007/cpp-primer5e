//
// Created by xing on 4/9/18.
//
#include "timer_wheel.h"

TimerWheel::TimerWheel() : cur_slot(0) {
  for (int i = 0; i < N; ++i) {
    slots[i] = nullptr;
  }
}

TimerWheel::~TimerWheel() {
  for (int i = 0; i < N; ++i) {
    Timer *head = slots[i];
    while (head) {
      slots[i] = head->next;
      delete head;
      head = slots[i];
    }
  }
}

// relative time
Timer *TimerWheel::add_timer(int timeout) {
  if (timeout <= 0) {
    return nullptr;
  }
  int ticks = 0;
  if (timeout < SI) {
    ticks = 1;
  } else {
    ticks = timeout / SI;
  }
  int rotation = ticks / N;
  int ts = (cur_slot + ticks % N) % N;
  Timer *timer = new Timer(rotation, ts);

  if (!slots[ts]) {
    printf("add timer, rotation is %d, ts is %d, cur_slot is %d\n",
           rotation, ts, cur_slot);
    slots[ts] = timer;
  } else {
    timer->next = slots[ts];
    slots[ts]->prev = timer;
    slots[ts] = timer;
  }
  return timer;
}

// old style
void TimerWheel::del_timer(Timer *timer) {
  if (timer == nullptr) {
    return;
  }
  int ts = timer->time_slot;
  if (timer == slots[ts]) {
    slots[ts] = slots[ts]->next;
    if (slots[ts]) {
      slots[ts]->prev = nullptr;
    }
  } else {
    timer->prev->next = timer->next;
    if (timer->next)
      timer->next->prev = timer->prev;
  }
  delete timer;
}

void TimerWheel::tick() {
  Timer *tmp = slots[cur_slot];
  printf("current slot is %d\n", cur_slot);
  while (tmp) {
    printf("tick the timer once\n");
    if (tmp->rotation > 0) {
      --tmp->rotation;
      tmp = tmp->next;
    } else {
      tmp->cb_func(tmp->user_data);
      if (tmp == slots[cur_slot]) {
        printf("delete header in cur_slot\n");
        slots[cur_slot] = tmp->next;
        delete tmp;
        if (slots[cur_slot]) {
          slots[cur_slot]->prev = nullptr;
        }
        tmp = slots[cur_slot];
      } else {
        tmp->prev->next = tmp->next;
        if (tmp->next) {
          tmp->next->prev = tmp->prev;
        }
        // next one
        auto *new_tmp = tmp->next;
        delete tmp;
        tmp = new_tmp;
      }
    }
  }
  // next slot
  cur_slot = (cur_slot + 1) % N;
}
