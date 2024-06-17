namespace s21 {

template <typename value_type>
queue<value_type>::queue(size_type n) : base<value_type>() {
  for (size_type i = 0; i < n; i++) {
    push(0);
  }
}

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const &items)
    : base<value_type>() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename value_type>
queue<value_type> queue<value_type>::operator=(queue &&queue) {
  if (!this->empty()) {
    this->clear_base();
  }
  copy(queue);
  return *this;
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() {
  return this->front_base();
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() {
  return tail_->value;
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  typename base<value_type>::data *tmp =
      new typename base<value_type>::data(value, nullptr);
  this->capacity_++;
  if (this->head_ == nullptr) {
    this->head_ = tmp;
    tail_ = tmp;
  } else {
    tail_->pointer_next = tmp;
    tail_ = tmp;
  }
}

template <typename value_type>
void queue<value_type>::pop() {
  this->empty_check();
  this->pop_front_base();
}

template <typename value_type>
void queue<value_type>::swap(queue &other) {
  if (other.head_ == nullptr) {
    throw std::runtime_error("Error: this queue is empty");
  }
  std::swap(this->head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(this->capacity_, other.capacity_);
}

// privat functions

template <typename value_type>
void queue<value_type>::copy(const queue &queue) {
  if (&queue != this) {
    typename base<value_type>::data *tmp = queue.head_;
    while (tmp != nullptr) {
      push(tmp->value);
      tmp = tmp->pointer_next;
    }
  }
}

template <typename value_type>
void queue<value_type>::move(queue &&queue) {
  if (&queue != this) {
    this->head_ = queue.head_;
    this->tail_ = queue.tail_;
    this->capacity_ = queue.capacity_;
    queue.head_ = nullptr;
    queue.tail_ = nullptr;
    queue.capacity_ = 0;
  }
}

template <typename value_type>
template <typename... Args>
void queue<value_type>::emplace_back(Args &&...args) {
  emplace_back_help(args...);
}

template <typename value_type>
template <typename V, typename... Args>
void queue<value_type>::emplace_back_help(V value, Args &&...args) {
  push(value);
  emplace_back_help(args...);
}

}  // namespace s21