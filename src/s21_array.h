#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include "s21_start_class.h"

namespace s21 {

template <typename T>
class array : public start {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array(){};
  array(std::initializer_list<value_type> const &items);
  array(const array &array);
  array(array &&array);
  ~array();
  array operator=(array &&array);

  iterator begin();
  iterator end();

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  size_type max_size();

  void swap(array &other);
  void fill(const_reference value);

 private:
  void copy(const array &array);
  void move(array &&array);
  value_type *array_data = nullptr;
};

}  // namespace s21

#include "s21_array.cpp"

#endif  // SRC_S21_ARRAY_H_