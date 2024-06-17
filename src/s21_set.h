#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

namespace s21 {

template <typename Key>
class set : public tree<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename tree<value_type>::TreeIterator;
  using const_iterator = const iterator;
  using size_type = std::size_t;

  set(){};
  set(std::initializer_list<value_type> const& items);
  set(const set& set) {
    if (&set != this) {
      this->copy(set.root_);
    }
  };
  set(set&& set) {
    if (&set != this) {
      this->move_base(set.root_, set.capacity_);
    }
  };
  ~set(){};
  set operator=(set&& set);

  iterator begin();
  iterator end();

  std::pair<iterator, bool> insert(const value_type& value);
  void swap(set& other);
  void merge(set& other);

  iterator find(const key_type& key);
  bool contains(const Key& key);

  template <typename... Args>
  vector<std::pair<iterator, bool>> emplace(Args&&... args);

 private:
  typename tree<value_type>::data* find_by_key(const key_type& key);
  void copy(const typename tree<value_type>::data* map);
  template <typename V, typename... Args>
  void emplace_help(V value, Args&&... args);
  void emplace_help(){};
};

}  // namespace s21

#include "s21_set.cpp"

#endif  // SRC_S21_SET_H_