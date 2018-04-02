//
// C++ concurrency in Action.
//

#include <list>
#include <algorithm>
#include <future>
#include <iostream>

using namespace std;

// sequential version quick-sort
template<typename T>
list<T> sequential_quick_sort(list<T> input) {
  if (input.empty()) {
    return input;
  }

  std::list<T> result;
  result.splice(result.begin(), input, input.begin());

  const T &pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
                                     [&](const T &t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

  auto new_lower(sequential_quick_sort(std::move(lower_part)));
  auto new_higher(sequential_quick_sort(std::move(input)));

  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower);

  return result;
};

// parallel version quick-sort with futures
template<typename T>
list<T> parallel_quick_sort(list<T> input) {
  if (input.empty()) {
    return input;
  }
  std::list<T> result;
  result.splice(result.begin(), input, input.begin());

  const T &pivot = *result.begin();
  auto divide_point = std::partition(input.begin(), input.end(),
                                     [&](const T &t) { return t < pivot; });
  std::list<T> lower_part;
  lower_part.splice(lower_part.end(), input, input.begin(), divide_point);

  std::future<std::list<T>> new_lower = std::async(&parallel_quick_sort<T>, std::move(lower_part));
  auto new_higher(parallel_quick_sort(std::move(input)));
  result.splice(result.end(), new_higher);
  result.splice(result.begin(), new_lower.get());

  return result;
};

template<typename T>
T func(T a) {
  return a;
}

// experiment
template<typename F, typename A>
typename std::result_of<F(A &&)>::type result(F &&f, A &&a) {
  return f(std::forward<A>(a));
};

// spawn-task: what is the difference between std::move and std::forward?
// highlight:
// std::forward is for perfect forwarding, std::move just allow you treat
// a object as a temporary(an rvalue).
//
// ref: https://stackoverflow.com/questions/9671749/whats-the-difference-between-stdmove-and-stdforward
//
// std::move takes an object and allows you to treat it as a temporary (an rvalue).
// Although it isn't a semantic requirement, typically a function accepting a reference
// to an rvalue will invalidate it.
// When you see std::move, it indicates that the value of the object should not be used
// afterwards, but you can still assign a new value and continue using it.
//
// std::forward has a single use case: to cast a templated function parameter (inside the
// function) to the value category (lvalue or rvalue) the caller used to pass it. This
// allows rvalue arguments to be passed on as rvalues, and lvalues to be passed on as
// lvalues, a scheme called "perfect forwarding."
//
template<typename F, typename... A>
std::future<typename std::result_of<F(A &&...)>::type> spawn_task(F &&f, A &&... a) {
  typedef typename std::result_of<F(A &&...)>::type result_type;
  std::packaged_task<result_type(A &&...)> task(std::forward<F>(f));
  std::future<result_type> res(task.get_future());
  std::thread t(std::move(task), std::forward<A>(a)...);
  t.detach();
  return res;
}

int main() {
  list<int> l{6, 7, 2, 3, 1, 9, 10, 8, 4, 5,};
  auto r = sequential_quick_sort(l);
  auto r2 = sequential_quick_sort(l);
  for_each(r.begin(), r.end(), [](int e) { cout << e << " "; });
  cout << endl;

  for_each(r2.begin(), r2.end(), [](int e) { cout << e << " "; });
  cout << endl;

  // result type
  cout << result(func<int>, 1) << endl;
  cout << result(func<double>, .1) << endl;
  cout << result(func<string>, "hello") << endl;
  cout << result(func<string>, string("world")) << endl;

  // spawn task
  auto r3 = spawn_task(func<string>, string("hello, world"));
  cout << r3.get() << endl;
  return 0;
}
