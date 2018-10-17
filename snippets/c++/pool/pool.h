#ifndef POOL_H_
#define POOL_H_

#include <memory>
#include <stack>

// RAII idiom
template <class T, class D = std::default_delete<T>>
class SmartObjectPool {
  // clever and tricky
  struct ReturnToPool_Deleter {
    explicit ReturnToPool_Deleter(std::weak_ptr<SmartObjectPool<T, D>*> pool)
        : pool_(pool) {}

    void operator()(T* ptr) {
      // two layers of indirect
      if (auto pool_ptr = pool_.lock()) {
        // so this line is quite possibly not exception safe
        try {
          (*pool_ptr.get())->add(std::unique_ptr<T, D>{ptr});
          return;
        } catch (const std::bad_alloc&) {
          // if std::stack::push throw
        }
        // if you run out of memory, clear up some by destroying an object
        // instead of returning it to the pool.
        // A good way to both mitigate a problem, and not crash and burn.
        D{}(ptr);
      } else {
        D{}(ptr);  // default delete
      }
    }

   private:
    std::weak_ptr<SmartObjectPool<T, D>*> pool_;
  };

 public:
  SmartObjectPool() : this_ptr_(new SmartObjectPool<T, D>*(this)) {}

  // Insert objects into the pool
  // push may throw std::bad_alloc
  void add(std::unique_ptr<T, D> t) { pool_.push(std::move(t)); }

  // Returns an object, with a special deleter that returns the object to the
  // pool, instead of destroying it.
  std::unique_ptr<T, ReturnToPool_Deleter> acquire() {
    ReturnToPool_Deleter deleter{this_ptr_};
    T* ptr = pool_.top().release();
    pool_.pop();
    return std::unique_ptr<T, ReturnToPool_Deleter>(ptr, deleter);
  }

  // Get the number of acquirable pool object
  size_t size() const { return pool_.size(); }

 private:
  std::stack<std::unique_ptr<T, D>> pool_;

  // why another indirect layer? interesting!?
  // Because we can't use std::shared_ptr<SmartObjectPool<T,D>>, it will
  // cause double delete, and not confused with std::enable_shared_from_this.

  // A shared_ptr object that contains a pointer to our smart pool. If the pool
  // is destroyed, so is the shared_ptr, and any weak_ptr derived from it can be
  // made aware of it.
  std::shared_ptr<SmartObjectPool<T, D>*> this_ptr_;
};

#endif
