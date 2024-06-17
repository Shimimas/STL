#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include "s21_base_class.h"

namespace s21 {

template <typename T>
class list : public base<T> {
 public:
  class ListIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = const ListIterator;
  using size_type = std::size_t;

  list(){};
  explicit list(size_type n) : base<value_type>(n){};
  list(std::initializer_list<value_type> const &items)
      : base<value_type>(items){};
  list(const list &list) : base<value_type>() { copy(list); };
  list(list &&list) : base<value_type>() { move(std::move(list)); };
  ~list(){};
  list operator=(list &&list);

  class ListIterator {
   public:
    explicit ListIterator(typename base<value_type>::data *init) : ptr(init){};
    typename base<value_type>::data *ptr = nullptr;
    ListIterator operator++();
    value_type operator*();
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
  };

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void sort();
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  void copy(const list &list);
  void move(list &&list);
  typename base<value_type>::data *merge(
      typename base<value_type>::data *left,
      typename base<value_type>::data *right);
  typename base<value_type>::data *mergesort(
      typename base<value_type>::data *head);
  template <typename V, typename... Args>
  void emplace_front_help(V value, Args &&...args);
  void emplace_front_help(){};
  template <typename V, typename... Args>
  void emplace_back_help(V value, Args &&...args);
  void emplace_back_help(){};
};

}  // namespace s21

#include "s21_list.cpp"

#endif  // SRC_S21_LIST_H_