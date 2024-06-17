#pragma once

namespace s21 {

template <typename T>
class vector {
 public:
  class VectorIterator;

  using value_type = T;
  using reference = T &;
  using size_type = size_t;
  using const_reference = const T &;
  using iterator = VectorIterator;
  using const_iterator = const iterator;

  vector() : m_size_(0), m_capacity_(0), arr_(nullptr) {}
  explicit vector(size_type type)
      : m_size_(type),
        m_capacity_(type),
        arr_(type ? new value_type[type] : nullptr) {}
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &vector) {
    if (this == &vector) {
      throw std::runtime_error("Error: the same vector");
    }
    m_size_ = vector.m_size_;
    m_capacity_ = vector.m_capacity_;
    arr_ = new value_type[vector.m_size_];
    for (int i = 0; i < (int)m_size_; i++) {
      arr_[i] = vector[i];
    }
  }
  vector(vector &&vector)
      : m_size_(vector.m_size_),
        m_capacity_(vector.m_capacity_),
        arr_(vector.arr_) {
    vector.arr_ = nullptr;
    vector.m_size_ = 0;
    vector.m_capacity_ = 0;
  }
  ~vector() { clear(); }
  vector &operator=(vector &other);

  bool operator==(const vector &other);
  bool operator!=(const vector &other);

  class VectorIterator {
   public:
    value_type *current = nullptr;

    explicit VectorIterator(value_type *init) : current(init){};
    VectorIterator operator+(int n) { return iterator(current + n); }
    VectorIterator operator-(int n) { return iterator(current - n); }
    VectorIterator operator++() { return iterator(++current); }
    VectorIterator operator--() { return iterator(--current); }

    bool operator==(const VectorIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const VectorIterator &other) const {
      return current != other.current;
    }

    value_type operator*() { return *current; }
    value_type operator=(value_type value) { return *current = value; }
  };

  T *data();

  size_type size();
  size_type max_size();
  size_type capacity() const noexcept;

  reference at(size_type i) const;
  reference operator[](size_type i) const;

  void clear();
  void pop_back();
  void print_vector();
  void shrink_to_fit();
  void resize(size_type n);
  void swap(vector &other);
  void erase(iterator pos);
  void move(vector &&vector);
  void reserve(size_type size);
  void push_back(value_type value);
  void resize(size_type n, value_type value);
  void assign(size_type n, value_type value);

  iterator end();
  iterator begin();
  iterator insert(iterator pos, const_reference value);

  const_reference front();
  const_reference back();

  bool empty();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);

 private:
  size_t m_size_;
  size_t m_capacity_;
  T *arr_;

  void reserve_more_capacity(size_type size);
  void resize_all(size_type n, value_type value, int flag);
  void merge_vectors(const_iterator pos, vector &other);

  bool eq_operator(const vector &other, bool flag);

  template <typename V, typename... Args>
  void emplace_back_help(V value, Args &&...args);
  void emplace_back_help(){};
};

}  //  namespace s21

#include "s21_vector.cpp"
