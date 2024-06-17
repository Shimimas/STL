#ifndef SRC_S21_TREE_CLASS_H_
#define SRC_S21_TREE_CLASS_H_

#include "s21_start_class.h"

namespace s21 {

template <typename T>
class tree : public start {
 public:
  class TreeIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = TreeIterator;
  using const_iterator = const iterator;

  void clear();
  void erase(iterator pos);
  size_type max_size();

 protected:
  struct data {
    value_type value_;
    data *left_ = nullptr;
    data *right_ = nullptr;
    data *parent_ = nullptr;
    explicit data(value_type value, data *left, data *right, data *parent)
        : value_(value), left_(left), right_(right), parent_(parent) {}
  };

  data *root_ = nullptr;

  tree(){};
  ~tree() { clear(); };

  void delete_tree(data *curr);
  void create_tree(value_type value);
  data *find_start_el();
  data *find_end_el();
  void move_base(data *&map, size_type &size_tmp);
  void swap_base(data *&other, size_type &size_tmp);

 public:
  class TreeIterator {
   public:
    TreeIterator(data *init) : ptr(init){};
    data *ptr = nullptr;
    iterator operator++();
    iterator operator--();
    value_type operator*();
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;

   private:
    void iterator_help(bool type);
  };

 private:
  void empty_check();
};

}  // namespace s21

#include "s21_tree_class.cpp"

#endif  // SRC_S21_TREE_CLASS_H_