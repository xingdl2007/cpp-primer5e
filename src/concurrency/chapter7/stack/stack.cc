//
// C++ concurrency in Action.
//

#include <atomic>
#include <string>
#include <memory>

#include <iostream>

template <typename T>
class stack {
private:
  struct node {
    std::shared_ptr<T> data;
    node *next;
    explicit node(const T &data_) : data(std::make_shared<T>(data_)) {}
  };

  std::atomic<node *> head{nullptr};
  std::atomic<unsigned> threads_in_pop{0};
  std::atomic<node *> to_be_deleted{nullptr};

  void try_reclaim(node *old_head) {
    if (threads_in_pop == 1) {
      node *to_delete = to_be_deleted.exchange(nullptr);
      if (!--threads_in_pop) {
        delete_nodes(to_delete);
      } else if (to_delete) {
        chain_pending_nodes(to_delete);
      }
      delete old_head;
    } else {
      chain_pending_node(old_head);
      --threads_in_pop;
    }
  }

  static void delete_nodes(node *n) {
    while (n) {
      node *next = n->next;
      delete n;
      n = next;
    }
  }

  // insert candidate to to_be_deleted list
  void chain_pending_nodes(node *first, node *last) {
    last->next = to_be_deleted;
    while (!to_be_deleted.compare_exchange_weak(last->next, first));
  }

  // caller make sure head != nullptr
  void chain_pending_nodes(node *head) {
    node *last = head;
    while (node *next = head->next) {
      last = next;
    }
    chain_pending_nodes(head, last);
  }

  // a special case
  void chain_pending_node(node *n) {
    chain_pending_nodes(n, n);
  }

public:
  stack() = default;
  stack(const stack &) = delete;
  stack &operator=(const stack &) = delete;

  void push(const T &data) {
    auto *const n = new node(data);
    n->next = head.load();
    while (!head.compare_exchange_weak(n->next, n)); // compare/exchange or compare-and-swap function
  }

  // node leaky
  std::shared_ptr<T> pop() {
    ++threads_in_pop;
    node *old_head = head.load();
    // which will not suffer "ABA problem"
    while (old_head && !head.compare_exchange_weak(old_head, old_head->next));
    std::shared_ptr<T> res;
    if (old_head) {
      res.swap(old_head->data);
    }
    try_reclaim(old_head);
    return res;
  }
};

// lock-free version without node leak
// manage memory with split reference count
template <typename T>
class lock_free_stack {
private:
  struct node;
  struct counted_node_ptr {
    int external_count;
    node *ptr;
  };
  struct node {
    std::shared_ptr<T> data;
    std::atomic<int> internal_count;
    counted_node_ptr next;
    node(T const &data_) :
        data(std::make_shared<T>(data_)),
        internal_count(0) {}
  };
  std::atomic<counted_node_ptr> head;
  void increase_head_count(counted_node_ptr &old_counter) {
    counted_node_ptr new_counter;
    do {
      new_counter = old_counter;
      ++new_counter.external_count;
    } while (!head.compare_exchange_strong(
        old_counter, new_counter,
        std::memory_order_acquire,
        std::memory_order_relaxed));
    old_counter.external_count = new_counter.external_count;
  }
public:
  ~lock_free_stack() {
    while (pop());
  }

  void push(T const &data) {
    counted_node_ptr new_node;
    new_node.ptr = new node(data);
    new_node.external_count = 1;
    new_node.ptr->next = head.load(std::memory_order_relaxed);
    while (!head.compare_exchange_weak(
        new_node.ptr->next, new_node,
        std::memory_order_release,
        std::memory_order_relaxed));
  }
  std::shared_ptr<T> pop() {
    counted_node_ptr old_head =
        head.load(std::memory_order_relaxed);
    for (;;) {
      increase_head_count(old_head);
      node *const ptr = old_head.ptr;
      if (!ptr) {
        return std::shared_ptr<T>();
      }
      if (head.compare_exchange_strong(
          old_head, ptr->next, std::memory_order_relaxed)) {
        std::shared_ptr<T> res;
        res.swap(ptr->data);
        int const count_increase = old_head.external_count - 2;
        if (ptr->internal_count.fetch_add(
            count_increase, std::memory_order_release) == -count_increase) {
          delete ptr;
        }
        return res;
      } else if (ptr->internal_count.fetch_add(
          -1, std::memory_order_relaxed) == 1) {
        ptr->internal_count.load(std::memory_order_acquire);
        delete ptr;
      }
    }
  }
};

int main() {
  stack<std::string> list;
  // empty test
  if (auto e = list.pop()) {
    std::cout << *e << std::endl;
  }
  list.push(std::string("hello"));
  list.push(std::string("world"));

  auto w = list.pop();
  auto h = list.pop();
  std::cout << *h << " " << *w << std::endl;

  // smart pointer: shared_ptr is not atomic
  std::shared_ptr<int> i;
  if (std::atomic_is_lock_free(&i)) {
    std::cout << "atomic" << std::endl;
  }
}
