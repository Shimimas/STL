namespace s21 {

template <typename value_type>
array<value_type>::array(std::initializer_list<value_type> const &items) {
  array_data = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    array_data[i] = *it;
    capacity_++;
    i++;
  }
}

template <typename value_type>
array<value_type>::array(const array &array) {
  copy(array);
}

template <typename value_type>
array<value_type>::array(array &&array) {
  move(std::move(array));
}

template <typename value_type>
array<value_type>::~array() {
  if (array_data != nullptr) {
    delete[] array_data;
    array_data = nullptr;
  }
  capacity_ = 0;
}

template <typename value_type>
array<value_type> array<value_type>::operator=(array &&array) {
  if (!empty()) {
    delete[] array_data;
    array_data = nullptr;
    capacity_ = 0;
  }
  copy(array);
  return *this;
}

template <typename value_type>
typename array<value_type>::iterator array<value_type>::begin() {
  return array_data;
}

template <typename value_type>
typename array<value_type>::iterator array<value_type>::end() {
  return (array_data + capacity_ - 1);
}

template <typename value_type>
typename array<value_type>::reference array<value_type>::at(
    typename array<value_type>::size_type pos) {
  if (pos > capacity_ - 1) {
    throw std::runtime_error("Error: array out of bounds");
  }
  return array_data[pos];
}

template <typename value_type>
typename array<value_type>::reference array<value_type>::operator[](
    typename array<value_type>::size_type pos) {
  return at(pos);
}

template <typename value_type>
typename array<value_type>::const_reference array<value_type>::front() {
  return *(begin());
}

template <typename value_type>
typename array<value_type>::const_reference array<value_type>::back() {
  return *(end());
}

template <typename value_type>
typename array<value_type>::iterator array<value_type>::data() {
  return array_data;
}

template <typename value_type>
typename array<value_type>::size_type array<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / (sizeof(value_type));
}

template <typename value_type>
void array<value_type>::swap(array &other) {
  array<value_type> tmp(std::move(other));
  other = std::move(*this);
  *this = std::move(tmp);
}

template <typename value_type>
void array<value_type>::fill(
    typename array<value_type>::const_reference value) {
  for (int i = 0; i < (int)capacity_; i++) {
    array_data[i] = value;
  }
}

template <typename value_type>
void array<value_type>::copy(const array &array) {
  if (&array != this) {
    array_data = new value_type[array.capacity_];
    for (int i = 0; i < (int)array.capacity_; i++) {
      array_data[i] = array.array_data[i];
      capacity_++;
    }
  }
}

template <typename value_type>
void array<value_type>::move(array &&array) {
  if (this != &array) {
    copy(array);
    array.capacity_ = 0;
    if (array.array_data != nullptr) {
      delete[] array.array_data;
      array.array_data = nullptr;
    }
  }
}

}  // namespace s21