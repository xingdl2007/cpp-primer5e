//
// Created by xing on 4/9/18.
//
// maintain timer with a double-linked list

#include <stdio.h>
#include "util_timer.h"

void SortedTimerList::add_timer(util_timer *timer) {
  if (timer == nullptr) {
    return;
  }
  if (!head) {
    head = tail = timer;
    return;
  }
  if (timer->expire < head->expire) {
    timer->next = head;
    head->prev = timer;
    head = timer;
    return;
  }
  return add_timer(timer, head);
}

// assumption: adjust time bigger than previous time
void SortedTimerList::adjust_timer(util_timer *timer) {
  if (timer == nullptr) {
    return;
  }
  util_timer *tmp = timer->next;
  // last one or still small than next one
  if (!tmp || timer->expire < tmp->expire) {
    return;
  }
  if (timer == head) {
    head = head->next;
    head->prev = nullptr;
    timer->next = nullptr;
    add_timer(timer, head);
  } else {
    timer->prev->next = timer->next;
    timer->next->prev = timer->prev;
    add_timer(timer, timer->next);
  }
}

void SortedTimerList::del_timer(util_timer *timer) {
  if (timer == nullptr) {
    return;
  }
  if (timer == tail && timer == head) {
    delete timer;
    head = tail = nullptr;
    return;
  }
  if (timer == head) {
    head = head->next;
    head->prev = nullptr;
    delete timer;
    return;
  }
  if (timer == tail) {
    tail = tail->prev;
    tail->next = nullptr;
    delete timer;
    return;
  }
  timer->prev->next = timer->next;
  timer->next->prev = timer->prev;
  delete timer;
}

void SortedTimerList::tick() {
  if (head == nullptr) {
    return;
  }
  printf("timer tick\n");
  time_t cur = time(nullptr);
  util_timer *tmp = head;

  while (tmp) {
    if (cur < tmp->expire) {
      break;
    }
    // callback function
    tmp->cb_func(tmp->user_data);
    head = tmp->next;
    if (head) {
      head->prev = nullptr;
    }
    delete tmp;
    tmp = head;
  }
}

// helper function
void SortedTimerList::add_timer(util_timer *timer, util_timer *lst_head) {
  util_timer *prev = lst_head;
  util_timer *tmp = prev->next;

  while (tmp) {
    if (timer->expire < tmp->expire) {
      prev->next = timer;
      timer->next = tmp;
      tmp->prev = timer;
      timer->prev = prev;
      break;
    }
    prev = tmp;
    tmp = prev->next;
  }
  if (!tmp) {
    prev->next = timer;
    timer->prev = prev;
    timer->next = nullptr;
    tail = timer;
  }
}
