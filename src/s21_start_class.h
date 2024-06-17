#ifndef SRC_S21_START_CLASS_H_
#define SRC_S21_START_CLASS_H_

namespace s21 {

class start {
 public:
  using size_type = std::size_t;

  size_type size();
  bool empty();

 protected:
  start(){};
  ~start(){};

  size_type capacity_ = 0;
};

}  // namespace s21

#include "s21_start_class.cpp"

#endif  // SRC_S21_START_CLASS_H_