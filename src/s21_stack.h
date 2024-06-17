#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include "s21_base_class.h"

namespace s21 {

template <typename T>
class stack : public base<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack(){};
  explicit stack(size_type n);
  stack(std::initializer_list<value_type> const &items)
      : base<value_type>(items){};
  stack(const stack &stack) : base<value_type>() { copy(stack); };
  stack(stack &&stack) : base<value_type>() { move(std::move(stack)); };
  ~stack(){};
  stack operator=(stack &&stack);

  const_reference top();

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  void copy(const stack &stack);
  void move(stack &&stack);

  template <typename V, typename... Args>
  void emplace_front_help(V value, Args &&...args);
  void emplace_front_help(){};
};

}  // namespace s21

#include "s21_stack.cpp"

#endif  // SRC_S21_STACK_H_