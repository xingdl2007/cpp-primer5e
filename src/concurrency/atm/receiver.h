//
// Created by xing on 4/2/18.
//
#pragma once

#include "sender.h"
#include "dispatcher.h"

namespace messaging {
class receiver {
  queue q;
public:
  operator sender() {
    return sender(&q);
  }
  dispatcher wait() {
    return dispatcher(&q);
  }
};
}

