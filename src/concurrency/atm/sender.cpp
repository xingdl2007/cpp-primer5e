//
// Created by xing on 4/2/18.
//

namespace messaging {
class sender {
  queue *q;
public:
  sender() :
      q(nullptr) {}
  explicit sender(queue *q_) :
      q(q_) {}
  template<typename Message>
  void send(Message const &msg) {
    if (q) {
      q->push(msg);
    }
  }
};
}

