#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "s21_tree_class.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class map : public tree<std::pair<const Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename tree<value_type>::TreeIterator;
  using const_iterator = const iterator;
  using size_type = std::size_t;

  map(){};
  map(std::initializer_list<value_type> const& items);
  map(const map& map) {
    if (&map != this) {
      this->copy(map.root_);
    }
  };
  map(map&& map) {
    if (&map != this) {
      this->move_base(map.root_, map.capacity_);
    }
  };
  ~map(){};
  map operator=(map&& map);

  T& at(const Key& key);
  T& operator[](const Key& key);

  iterator begin();
  iterator end();

  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void swap(map& other);
  void merge(map& other);

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

#include "s21_map.cpp"

#endif  // SRC_S21_MAP_H_