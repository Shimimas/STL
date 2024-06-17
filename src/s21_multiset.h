#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include "s21_vector.h"

namespace s21 {

template <typename Key>
class multiset : public tree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree<value_type>::TreeIterator;
  using const_iterator = const iterator;
  using size_type = std::size_t;

  multiset(){};
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &multiset) {
    if (&multiset != this) {
      this->copy(multiset.root_);
    }
  };
  multiset(multiset &&multiset) {
    if (&multiset != this) {
      this->move_base(multiset.root_, multiset.capacity_);
    }
  };
  ~multiset(){};
  multiset operator=(multiset &&multiset);

  iterator begin();
  iterator end();

  iterator insert(const_reference value);
  void swap(multiset &other);
  void merge(multiset &other);

  iterator find(const_reference key);
  bool contains(const_reference key);
  size_type count(const_reference key);
  std::pair<iterator, iterator> equal_range(const_reference key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  typename tree<value_type>::data *find_by_key(const key_type &key);
  void copy(const typename tree<value_type>::data *map);
  template <typename V, typename... Args>
  void emplace_help(V value, Args &&...args);
  void emplace_help(){};
};

}  // namespace s21

#include "s21_multiset.cpp"

#endif  // SRC_S21_MULTISET_H_