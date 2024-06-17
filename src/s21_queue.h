#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include "s21_base_class.h"

namespace s21 {

template <typename T>
class queue : public base<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  queue(){};
  explicit queue(size_type n);
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &queue) : base<value_type>() { copy(queue); };
  queue(queue &&queue) : base<value_type>() { move(std::move(queue)); };
  ~queue(){};
  queue operator=(queue &&queue);

  const_reference front();
  const_reference back();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  typename base<T>::data *tail_ = nullptr;
  void copy(const queue &queue);
  void move(queue &&queue);
  template <typename V, typename... Args>
  void emplace_back_help(V value, Args &&...args);
  void emplace_back_help(){};
};

}  // namespace s21

#include "s21_queue.cpp"

#endif  // SRC_S21_QUEUE_H_