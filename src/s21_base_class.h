#ifndef SRC_S21_BASE_CLASS_H_
#define SRC_S21_BASE_CLASS_H_

#include "s21_start_class.h"

namespace s21 {

template <typename T>
class base : public start {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 protected:
  base(){};
  explicit base(size_type n);
  base(std::initializer_list<value_type> const &items);
  ~base();

  struct data {
    data(value_type value_, data *pointer_next_) : value(value_) {
      pointer_next = pointer_next_;
    };
    data() : pointer_next(nullptr){};
    value_type value;
    data *pointer_next = nullptr;
  };

  data *head_ = nullptr;

  void empty_check();
  data *get_last_data_ptr(data *element);
  void empty_check(const data *element);
  void clear_base();
  void pop_front_base();
  void push_back_base(const_reference value);
  void push_front_base(const_reference value);
  const_reference front_base();
};

}  // namespace s21

#include "s21_base_class.cpp"

#endif  // SRC_S21_BASE_CLASS_H_