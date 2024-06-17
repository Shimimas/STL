namespace s21 {

template <typename value_type>
list<value_type> list<value_type>::operator=(list &&list) {
  if (!this->empty()) {
    clear();
  }
  copy(list);
  return *this;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  return this->front_base();
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  this->empty_check();
  typename base<value_type>::data *current =
      this->get_last_data_ptr(this->head_);
  return current->value;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  this->empty_check();
  return iterator(this->head_);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(this->get_last_data_ptr(this->head_)->pointer_next);
}

template <typename value_type>
value_type list<value_type>::ListIterator::operator*() {
  if (ptr == nullptr) {
    throw std::runtime_error("Error: try to dereference a nullptr iterator");
  }
  return ptr->value;
}

template <typename value_type>
typename list<value_type>::ListIterator
list<value_type>::ListIterator::operator++() {
  if (ptr == nullptr) {
    throw std::runtime_error("Error: try to dereference a nullptr iterator");
  }
  ptr = ptr->pointer_next;
  return *this;
}

template <typename value_type>
bool list<value_type>::iterator::operator==(const iterator &other) const {
  return ptr == other.ptr;
}

template <typename value_type>
bool list<value_type>::iterator::operator!=(const iterator &other) const {
  return ptr != other.ptr;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() /
         (sizeof(typename base<value_type>::data));
}

template <typename value_type>
void list<value_type>::clear() {
  this->clear_base();
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  if (pos.ptr == nullptr) {
    throw std::runtime_error(
        "Error: try to set ellement after nullptr iterator");
  }
  this->empty_check();
  if (pos.ptr == this->head_) {
    push_front(value);
  } else if (pos.ptr == this->get_last_data_ptr(this->head_)) {
    push_back(value);
  } else {
    typename base<value_type>::data *tmp = this->head_;
    while (tmp->pointer_next != pos.ptr) {
      tmp = tmp->pointer_next;
    }
    typename base<value_type>::data *newdata =
        new typename base<value_type>::data(value, tmp->pointer_next);
    tmp->pointer_next = newdata;
    this->capacity_++;
    pos.ptr = newdata;
  }
  return pos;
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (pos.ptr == nullptr) {
    throw std::runtime_error(
        "Error: try to delete ellement after nullptr iterator");
  }
  this->empty_check();
  if (pos.ptr == this->head_) {
    pop_front();
  } else {
    typename base<value_type>::data *tmp = this->head_;
    while (tmp->pointer_next != pos.ptr) {
      tmp = tmp->pointer_next;
    }
    typename base<value_type>::data *next_data =
        tmp->pointer_next->pointer_next;
    delete pos.ptr;
    tmp->pointer_next = next_data;
    this->capacity_--;
  }
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  this->push_back_base(value);
}

template <typename value_type>
void list<value_type>::pop_back() {
  this->empty_check();
  erase(iterator(this->get_last_data_ptr(this->head_)));
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  this->push_front_base(value);
}

template <typename value_type>
void list<value_type>::pop_front() {
  this->pop_front_base();
}

template <typename value_type>
void list<value_type>::swap(list &other) {
  if (other.head_ == nullptr) {
    throw std::runtime_error("Error: this list is empty");
  }
  std::swap(this->head_, other.head_);
  std::swap(this->capacity_, other.capacity_);
}

template <typename value_type>
void list<value_type>::sort() {
  this->empty_check();
  this->head_ = mergesort(this->head_);
}

template <typename value_type>
void list<value_type>::merge(list &other) {
  this->get_last_data_ptr(this->head_)->pointer_next = other.head_;
  this->capacity_ += other.capacity_;
  other.head_ = nullptr;
  other.capacity_ = 0;
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  if (other.head_ == nullptr) {
    throw std::runtime_error("Error: this list is empty");
  }
  typename base<value_type>::data *tmp = other.head_;
  int counter = 0;
  while (tmp->pointer_next != pos.ptr && tmp->pointer_next != nullptr) {
    counter++;
    tmp = tmp->pointer_next;
  }
  this->get_last_data_ptr(this->head_)->pointer_next = tmp->pointer_next;
  tmp->pointer_next = nullptr;
  size_type change = other.size() - counter - 1;
  this->capacity_ += change;
  other.capacity_ -= change;
}

template <typename value_type>
void list<value_type>::reverse() {
  this->empty_check();
  typename base<value_type>::data *tmp_head = this->head_;
  list<value_type> tmp;
  while (tmp_head != nullptr) {
    tmp.push_front(tmp_head->value);
    tmp_head = tmp_head->pointer_next;
  }
  clear();
  this->head_ = tmp.head_;
  this->capacity_ = tmp.capacity_;
  tmp.head_ = nullptr;
  tmp.capacity_ = 0;
}

template <typename value_type>
void list<value_type>::unique() {
  this->empty_check();
  typename base<value_type>::data *tmp_head = this->head_;
  value_type check = this->head_->value;
  while (tmp_head->pointer_next != nullptr) {
    if (tmp_head->pointer_next->value == check) {
      typename base<value_type>::data *tmp = tmp_head->pointer_next;
      if (tmp_head->pointer_next->pointer_next != nullptr) {
        tmp_head->pointer_next = tmp_head->pointer_next->pointer_next;
      } else {
        tmp_head->pointer_next = nullptr;
      }
      delete tmp;
      this->capacity_--;
    } else {
      check = tmp_head->pointer_next->value;
      tmp_head = tmp_head->pointer_next;
    }
  }
}

// privat functions

template <typename value_type>
typename base<value_type>::data *list<value_type>::merge(
    typename base<value_type>::data *left,
    typename base<value_type>::data *right) {
  typename base<value_type>::data *result;
  if (left == nullptr) {
    result = right;
  } else if (right == nullptr) {
    result = left;
  } else {
    if (left->value < right->value) {
      result = left;
      left->pointer_next = merge(left->pointer_next, right);
    } else {
      result = right;
      right->pointer_next = merge(left, right->pointer_next);
    }
  }
  return result;
}

template <typename value_type>
typename base<value_type>::data *list<value_type>::mergesort(
    typename base<value_type>::data *head) {
  typename base<value_type>::data *result;
  if (head == nullptr || head->pointer_next == nullptr) {
    result = head;
  } else {
    typename base<value_type>::data *left = head, *right = head->pointer_next;
    while (right != nullptr && right->pointer_next != nullptr) {
      head = head->pointer_next;
      right = right->pointer_next->pointer_next;
    }
    right = head->pointer_next;
    head->pointer_next = nullptr;
    result = merge(mergesort(left), mergesort(right));
  }
  return result;
}

template <typename value_type>
void list<value_type>::copy(const list &list) {
  if (&list != this) {
    typename base<value_type>::data *tmp = list.head_;
    while (tmp != nullptr) {
      push_back(tmp->value);
      tmp = tmp->pointer_next;
    }
  }
}

template <typename value_type>
void list<value_type>::move(list &&list) {
  if (&list != this) {
    this->head_ = list.head_;
    this->capacity_ = list.capacity_;
    list.head_ = nullptr;
    list.capacity_ = 0;
  }
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::emplace(
    const_iterator pos, Args &&...args) {
  typename list<value_type>::iterator result(nullptr);
  if (pos == begin()) {
    emplace_front(args...);
  } else if (pos.ptr->pointer_next == nullptr) {
    emplace_back(args...);
  } else {
    typename list<value_type>::size_type capacity_left = 0;
    typename list<value_type>::iterator left(nullptr);
    for (auto it = begin(); it != end(); ++it) {
      capacity_left++;
      if (it.ptr->pointer_next == pos.ptr) {
        left.ptr = it.ptr;
        left.ptr->pointer_next = nullptr;
        break;
      }
    }
    typename list<value_type>::size_type capacity_right =
        this->capacity_ - capacity_left;
    this->capacity_ = capacity_left;
    emplace_back(args...);
    result.ptr = this->get_last_data_ptr(this->head_);
    result.ptr->pointer_next = pos.ptr;
    this->capacity_ += capacity_right;
  }
  return result;
}

template <typename value_type>
template <typename... Args>
void list<value_type>::emplace_front(Args &&...args) {
  emplace_front_help(args...);
}

template <typename value_type>
template <typename... Args>
void list<value_type>::emplace_back(Args &&...args) {
  emplace_back_help(args...);
}

template <typename value_type>
template <typename V, typename... Args>
void list<value_type>::emplace_front_help(V value, Args &&...args) {
  emplace_front_help(args...);
  push_front(value);
}

template <typename value_type>
template <typename V, typename... Args>
void list<value_type>::emplace_back_help(V value, Args &&...args) {
  push_back(value);
  emplace_back_help(args...);
}

}  // namespace s21