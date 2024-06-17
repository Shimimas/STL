namespace s21 {

template <typename value_type>
base<value_type>::base(size_type n) : start() {
  for (size_type i = 0; i < n; i++) {
    push_back_base(0);
  }
}

template <typename value_type>
base<value_type>::base(std::initializer_list<value_type> const &items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    push_back_base(*it);
  }
}

template <typename value_type>
base<value_type>::~base() {
  clear_base();
}

template <typename value_type>
void base<value_type>::clear_base() {
  while (capacity_) {
    pop_front_base();
  }
}

template <typename value_type>
void base<value_type>::push_back_base(const_reference value) {
  data *tmp = new data(value, nullptr);
  capacity_++;
  if (head_ == nullptr) {
    head_ = tmp;
  } else {
    data *current = get_last_data_ptr(head_);
    current->pointer_next = tmp;
  }
}

template <typename value_type>
void base<value_type>::pop_front_base() {
  empty_check();
  data *tmp = head_;
  head_ = head_->pointer_next;
  delete tmp;
  capacity_--;
}

template <typename value_type>
void base<value_type>::push_front_base(const_reference value) {
  if (head_ == nullptr) {
    push_back_base(value);
  } else {
    data *tmp = new data(value, head_);
    head_ = tmp;
    capacity_++;
  }
}

template <typename value_type>
void base<value_type>::empty_check() {
  if (head_ == nullptr) {
    throw std::runtime_error("Error: this container is empty");
  }
}

template <typename value_type>
typename base<value_type>::data *base<value_type>::get_last_data_ptr(
    data *element) {
  empty_check(element);
  data *tmp = element;
  typename base<value_type>::size_type size_tmp = capacity_;
  while (tmp->pointer_next != nullptr && size_tmp) {
    tmp = tmp->pointer_next;
    size_tmp--;
  }
  return tmp;
}

template <typename value_type>
void base<value_type>::empty_check(const data *element) {
  if (element == nullptr) {
    throw std::runtime_error("Error: this container is empty");
  }
}

template <typename value_type>
typename base<value_type>::const_reference base<value_type>::front_base() {
  empty_check();
  return head_->value;
}

}  // namespace s21