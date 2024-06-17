namespace s21 {

template <typename value_type>
stack<value_type>::stack(size_type n) : base<value_type>() {
  for (size_type i = 0; i < n; i++) {
    this->push_back_base(0);
  }
}

template <typename value_type>
stack<value_type> stack<value_type>::operator=(stack &&stack) {
  if (!this->empty()) {
    this->clear_base();
  }
  copy(stack);
  return *this;
}

template <typename value_type>
typename stack<value_type>::const_reference stack<value_type>::top() {
  return this->front_base();
}

template <typename value_type>
void stack<value_type>::push(const_reference value) {
  return this->push_front_base(value);
}

template <typename value_type>
void stack<value_type>::pop() {
  this->empty_check();
  this->pop_front_base();
}

template <typename value_type>
void stack<value_type>::swap(stack &other) {
  if (other.head_ == nullptr) {
    throw std::runtime_error("Error: this queue is empty");
  }
  std::swap(this->head_, other.head_);
  std::swap(this->capacity_, other.capacity_);
}

// privat functions

template <typename value_type>
void stack<value_type>::copy(const stack &stack) {
  if (&stack != this) {
    typename base<value_type>::data *tmp = stack.head_;
    while (tmp != nullptr) {
      this->push_back_base(tmp->value);
      tmp = tmp->pointer_next;
    }
  }
}

template <typename value_type>
void stack<value_type>::move(stack &&stack) {
  if (&stack != this) {
    this->head_ = stack.head_;
    this->capacity_ = stack.capacity_;
    stack.head_ = nullptr;
    stack.capacity_ = 0;
  }
}

template <typename value_type>
template <typename... Args>
void stack<value_type>::emplace_front(Args &&...args) {
  emplace_front_help(args...);
}

template <typename value_type>
template <typename V, typename... Args>
void stack<value_type>::emplace_front_help(V value, Args &&...args) {
  emplace_front_help(args...);
  push(value);
}

}  // namespace s21