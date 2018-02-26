//
// C++ concurrency in Action.
//

#include <memory>
#include <mutex>

#include <iostream>

template <typename T>
class threadsafe_list {
  struct node {
    std::mutex m;
    std::shared_ptr<T> data;
    std::unique_ptr<node> next;

    node() = default;
    node(T const &value) : data(std::make_shared<T>(value)) {}
  };
  node head;

public:
  threadsafe_list() = default;
  ~threadsafe_list() {
    remove_if([](T const &) { return true; });
  }

  threadsafe_list(threadsafe_list const &other) = delete;
  threadsafe_list &operator=(threadsafe_list const &other)= delete;

  void push_front(T const &value) {
    std::unique_ptr<node> new_node(new node(value));
    std::lock_guard<std::mutex> lk(head.m);
    new_node->next = std::move(head.next);
    head.next = std::move(new_node);
  }

  template <typename Function>
  void for_each(Function f) {
    node *current = &head;
    std::unique_lock<std::mutex> lk(head.m);
    while (node *const next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m);
      lk.unlock();
      f(*next->data);
      current = next;
      lk = std::move(next_lk);
    }
  }

  template <typename Predicate>
  std::shared_ptr<T> find_first_if(Predicate p) {
    node *current = &head;
    std::unique_lock<std::mutex> lk(head.m);
    while (node *const next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m);
      lk.unlock();
      if (p(*next->data)) {
        return next->data;
      }
      current = next;
      lk = std::move(next_lk);
    }
    return std::shared_ptr<T>();
  }

  template <typename Predicate>
  void remove_if(Predicate p) {
    node *current = &head;
    std::unique_lock<std::mutex> lk(head.m);
    while (node *const next = current->next.get()) {
      std::unique_lock<std::mutex> next_lk(next->m);
      if (p(*next->data)) {
        // should unlock next_lk before destroy "std::unique_ptr<node> old_next"
        // because it's undefined behavior to destroy a locked mutex
        std::unique_ptr<node> old_next = std::move(current->next);
        current->next = std::move(next->next);
        next_lk.unlock();
      } else {
        lk.unlock();
        current = next;
        lk = std::move(next_lk);
      }
    }
  }
};

int main() {
  threadsafe_list<int> ls;
  ls.push_front(1);
  ls.push_front(2);
  ls.push_front(3);
  ls.push_front(4);
  ls.push_front(5);

  ls.for_each([](int i) { std::cout << i << std::endl; });
  ls.remove_if([](int i) { return i == 3; });
  std::cout << std::endl;
  ls.for_each([](int i) { std::cout << i << std::endl; });
  return 0;
}
