//
// Created by xing on 4/2/18.
//

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

