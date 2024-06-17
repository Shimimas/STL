namespace s21 {

template <typename value_type>
void vector<value_type>::reserve_more_capacity(size_t size) {
  value_type *buff = new value_type[size];
  if (size < m_size_) {
    m_size_ = size;
  }
  for (size_t i = 0; i < m_size_; ++i) {
    if (arr_ != nullptr) {
      buff[i] = std::move(arr_[i]);
    }
  }
  if (arr_ != nullptr) {
    delete[] arr_;
  }
  arr_ = buff;
  m_capacity_ = size;
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  m_size_ = items.size();
  m_capacity_ = items.size();
};

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
  return m_size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() /
         (sizeof(typename vector<value_type>::vector));
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity()
    const noexcept {
  return m_capacity_;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(
    size_type i) const {
  return arr_[i];
}

template <typename value_type>
void vector<value_type>::push_back(value_type value) {
  if (m_size_ == 0) {
    reserve_more_capacity(1);
  }
  if (m_size_ == m_capacity_) {
    reserve_more_capacity(m_size_ * 2);
  }
  arr_[m_size_++] = value;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](
    size_type i) const {
  if (i >= m_size_) {
    throw std::runtime_error("Error: index out of range");
  }
  return arr_[i];
}

template <typename value_type>
bool vector<value_type>::empty() {
  return arr_ == nullptr;
}

template <typename value_type>
void vector<value_type>::pop_back() {
  if (this->size() == 0) {
    throw std::runtime_error("Error: try to delete ellement in nullptr vector");
  }
  reserve_more_capacity(m_size_ - 1);
}

template <typename value_type>
void vector<value_type>::print_vector() {
  for (typename vector<value_type>::value_type *p = arr_; p < arr_ + m_size_;
       p++) {
    std::cout << *p << ' ';
  }
  std::cout << std::endl;
}

template <typename value_type>
void vector<value_type>::clear() {
  m_size_ = 0;
  m_capacity_ = 0;
  if (arr_ != nullptr) {
    delete[] arr_;
  }
  arr_ = nullptr;
}

template <typename value_type>
void vector<value_type>::resize_all(size_type n, value_type value, int flag) {
  if (flag == 0) {
    if (n == m_size_) {
      throw std::runtime_error("Error: the same vector's size");
    }

    if (n < m_size_) {
      reserve_more_capacity(n);
      m_size_ = n;
    } else {
      reserve_more_capacity(n);
      for (int i = m_size_; i < (int)n; i++) {
        arr_[i] = value;
      }
      m_size_ = n;
    }
  } else {
    reserve_more_capacity(n);
    for (int i = 0; i < (int)n; i++) {
      arr_[i] = value;
    }
    m_size_ = n;
  }
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
  return iterator(arr_);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
  return iterator(arr_ + m_size_);
}

template <typename value_type>
void vector<value_type>::resize(size_type n) {
  resize_all(n, 0, 0);
}

template <typename value_type>
void vector<value_type>::resize(size_type n, value_type value) {
  resize_all(n, value, 0);
}

template <typename value_type>
void vector<value_type>::assign(size_type n, value_type value) {
  resize_all(n, value, 1);
}

template <typename value_type>
void vector<value_type>::swap(vector &other) {
  s21::vector<value_type> vector_tmp(other);
  other.reserve_more_capacity(m_size_);
  for (int i = 0; i < (int)m_size_; i++) {
    other.arr_[i] = arr_[i];
  }
  other.m_size_ = m_size_;
  other.m_capacity_ = m_capacity_;
  reserve_more_capacity(vector_tmp.m_size_);
  for (int i = 0; i < (int)vector_tmp.m_size_; i++) {
    arr_[i] = vector_tmp.arr_[i];
  }
  m_size_ = vector_tmp.m_size_;
  m_capacity_ = vector_tmp.m_capacity_;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector &other) {
  move(std::move(other));

  return *this;
}

template <typename value_type>
bool vector<value_type>::eq_operator(const vector &other, bool flag) {
  bool res = 1;
  if (m_size_ != other.m_size_ && m_capacity_ != other.m_capacity_) {
    res = 0;
  } else {
    for (int i = 0; i < (int)m_size_; i++) {
      if (arr_[i] != other[i]) {
        res = 0;
        break;
      }
    }
  }

  return (flag == 1 ? !res : res);
}

template <typename value_type>
bool vector<value_type>::operator==(const vector &other) {
  return eq_operator(other, 0);
}

template <typename value_type>
bool vector<value_type>::operator!=(const vector &other) {
  return eq_operator(other, 1);
}

template <typename value_type>
void vector<value_type>::reserve(size_t capacity) {
  reserve_more_capacity(capacity);
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
  reserve_more_capacity(m_size_ - 1);
  int iter = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (it == pos) {
      iter += 2;
      continue;
    }
    it = arr_[iter];
    iter++;
  }
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(
    iterator pos, const_reference value) {
  bool flag = 0;
  value_type tmp, tmp2;
  reserve_more_capacity(m_size_ + 1);
  m_size_ = m_size_ + 1;
  for (auto it = begin(); it != end(); ++it) {
    if (flag) {
      tmp2 = *it;
      it = tmp;
      tmp = tmp2;
    }

    if (it == pos) {
      tmp = *it;
      it = value;
      flag = 1;
    }
  }

  return pos;
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
  if (arr_ == nullptr) {
    throw std::runtime_error("Error: Vector is empty");
  }
  return arr_[0];
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
  if (arr_ == nullptr) {
    throw std::runtime_error("Error: Vector is empty");
  }
  return arr_[m_size_ - 1];
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (m_capacity_ > m_size_) {
    m_capacity_ = m_size_;
  }
}

template <typename value_type>
typename vector<value_type>::value_type *vector<value_type>::data() {
  return (arr_ == nullptr ? nullptr : arr_);
}

template <typename value_type>
void vector<value_type>::move(vector &&vector) {
  this->m_size_ = vector.m_size_;
  this->m_capacity_ = vector.m_capacity_;
  value_type *result = new value_type[vector.m_capacity_];

  for (size_t i = 0; i < vector.m_size_; ++i) {
    result[i] = std::move(vector.arr_[i]);
  }
  if (this->arr_ != nullptr) {
    delete[] this->arr_;
  }

  arr_ = result;
}

template <typename value_type>
void vector<value_type>::merge_vectors(const_iterator pos, vector &other) {
  value_type *result = new value_type[m_size_ + other.m_size_];
  int i = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (it == pos) {
      for (auto other_it = other.begin(); other_it != other.end(); ++other_it) {
        result[i] = (value_type)*other_it;
        i++;
      }
    }

    result[i] = *it;
    i++;
  }
  if (this->arr_ != nullptr) {
    delete[] this->arr_;
  }

  arr_ = result;
  m_size_ = m_size_ + other.m_size_;
  m_capacity_ = m_capacity_ + other.m_capacity_;
}

template <typename value_type>
template <typename... Args>
void vector<value_type>::emplace_back(Args &&...args) {
  emplace_back_help(args...);
}

template <typename value_type>
template <typename V, typename... Args>
void vector<value_type>::emplace_back_help(V value, Args &&...args) {
  push_back(value);
  emplace_back_help(args...);
}

template <typename value_type>
template <typename... Args>
typename vector<value_type>::iterator vector<value_type>::emplace(
    const_iterator pos, Args &&...args) {
  typename vector<value_type>::iterator result(pos.current);
  vector<value_type> vector_tmp;
  vector_tmp.emplace_back(args...);
  merge_vectors(pos, vector_tmp);
  return result;
}

}  // namespace s21
