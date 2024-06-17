namespace s21 {

template <typename value_type>
void tree<value_type>::create_tree(value_type value) {
  root_ = new data(value, nullptr, nullptr, nullptr);
  capacity_++;
}

template <typename value_type>
void tree<value_type>::delete_tree(data *curr) {
  if (curr != nullptr) {
    delete_tree(curr->left_);
    delete_tree(curr->right_);
    delete curr;
  }
}

template <typename value_type>
void tree<value_type>::clear() {
  delete_tree(root_);
  root_ = nullptr;
  capacity_ = 0;
}

template <typename value_type>
void tree<value_type>::erase(iterator pos) {
  this->empty_check();
  this->capacity_--;
  if (pos.ptr->parent_ == nullptr && pos.ptr->left_ == nullptr &&
      pos.ptr->right_ == nullptr) {
    this->root_ = nullptr;
  } else if (pos.ptr->left_ == nullptr && pos.ptr->right_ == nullptr) {
    if (pos.ptr->parent_->left_ == pos.ptr) {
      pos.ptr->parent_->left_ = nullptr;
    } else {
      pos.ptr->parent_->right_ = nullptr;
    }
  } else if ((pos.ptr->left_ != nullptr && pos.ptr->right_ == nullptr) ||
             (pos.ptr->left_ == nullptr && pos.ptr->right_ != nullptr)) {
    if (pos.ptr->parent_->left_ == pos.ptr) {
      if (pos.ptr->left_ != nullptr) {
        pos.ptr->parent_->left_ = pos.ptr->left_;
      } else {
        pos.ptr->parent_->left_ = pos.ptr->right_;
      }
    } else {
      if (pos.ptr->left_ != nullptr) {
        pos.ptr->parent_->right_ = pos.ptr->left_;
      } else {
        pos.ptr->parent_->right_ = pos.ptr->right_;
      }
    }
  } else {
    auto tmp = ++pos;
    typename tree<value_type>::data *temp =
        new data(tmp.ptr->value_, pos.ptr->left_, pos.ptr->right_, nullptr);
    if (pos.ptr->parent_ != nullptr) {
      temp->parent_ = pos.ptr->parent_;
      if (temp->parent_->left_ == temp) {
        temp->parent_->left_ = temp;
      } else {
        temp->parent_->right_ = temp;
      }
    }
    temp->left_->parent_ = temp;
    temp->right_->parent_ = temp;
    erase(tmp);
  }
  delete pos.ptr;
}

template <typename value_type>
typename tree<value_type>::size_type tree<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() /
         (sizeof(typename tree<value_type>::data));
}

template <typename value_type>
void tree<value_type>::swap_base(data *&other, size_type &size_tmp) {
  typename tree<value_type>::data *tmp = other;
  other = root_;
  root_ = tmp;
  size_type size_temp = size_tmp;
  size_tmp = capacity_;
  capacity_ = size_temp;
}

template <typename value_type>
typename tree<value_type>::data *tree<value_type>::find_start_el() {
  empty_check();
  typename tree<value_type>::data *tmp = root_;
  while (tmp->left_ != nullptr) {
    tmp = tmp->left_;
  }
  return tmp;
}

template <typename value_type>
typename tree<value_type>::data *tree<value_type>::find_end_el() {
  empty_check();
  typename tree<value_type>::data *tmp = root_;
  while (tmp->right_ != nullptr) {
    tmp = tmp->right_;
  }
  return tmp;
}

template <typename value_type>
void tree<value_type>::TreeIterator::iterator_help(bool type) {
  if (type == false) {
    ptr = ptr->right_;
    while (ptr->left_ != nullptr) {
      ptr = ptr->left_;
    }
  } else {
    ptr = ptr->left_;
    while (ptr->right_ != nullptr) {
      ptr = ptr->right_;
    }
  }
}

template <typename value_type>
typename tree<value_type>::TreeIterator
tree<value_type>::TreeIterator::operator++() {
  if (ptr == nullptr) {
    throw std::runtime_error("Error: root tree is empty");
  }
  if (ptr->parent_ == nullptr) {
    if (ptr->right_ != nullptr) {
      iterator_help(false);
    }
  } else if (ptr == ptr->parent_->left_) {
    if (ptr->right_ == nullptr) {
      ptr = ptr->parent_;
    } else {
      iterator_help(false);
    }
  } else if (ptr == ptr->parent_->right_ && ptr->right_ != nullptr) {
    iterator_help(false);
  } else {
    bool stop = true;
    while (ptr->parent_ != nullptr && stop == true) {
      if (ptr != ptr->parent_->right_) {
        stop = false;
      }
      ptr = ptr->parent_;
    }
    if (ptr->parent_ == nullptr && stop == true) {
      ptr = nullptr;
    }
  }
  return *this;
}

template <typename value_type>
typename tree<value_type>::TreeIterator
tree<value_type>::TreeIterator::operator--() {
  if (ptr == nullptr) {
    throw std::runtime_error("Error: root tree is empty");
  }
  if (ptr->parent_ == nullptr) {
    if (ptr->left_ != nullptr) {
      iterator_help(true);
    }
  } else if (ptr == ptr->parent_->left_) {
    if (ptr->left_ == nullptr) {
      bool stop = true;
      while (ptr->parent_ != nullptr && stop == true) {
        if (ptr != ptr->parent_->left_) {
          stop = false;
        }
        ptr = ptr->parent_;
      }
      if (ptr->parent_ == nullptr && stop == true) {
        throw std::runtime_error(
            "Error: can't get ellement before first tree ell");
      }
    } else {
      iterator_help(true);
    }
  } else {
    if (ptr->left_ == nullptr) {
      ptr = ptr->parent_;
    } else {
      iterator_help(true);
    }
  }
  return *this;
}

template <typename value_type>
bool tree<value_type>::iterator::operator==(const_iterator &other) const {
  return ptr == other.ptr;
}

template <typename value_type>
bool tree<value_type>::iterator::operator!=(const_iterator &other) const {
  return ptr != other.ptr;
}

template <typename value_type>
typename tree<value_type>::value_type
tree<value_type>::TreeIterator::operator*() {
  if (ptr == nullptr) {
    throw std::runtime_error("Error: can't add nullptr pointer");
  }
  return ptr->value_;
}

template <typename value_type>
void tree<value_type>::empty_check() {
  if (root_ == nullptr) {
    throw std::runtime_error("Error: root tree is empty");
  }
}

template <typename value_type>
void tree<value_type>::move_base(
    typename tree<value_type>::data *&map,
    typename tree<value_type>::size_type &size_tmp) {
  this->root_ = map;
  this->capacity_ = size_tmp;
  map = nullptr;
  size_tmp = 0;
}

}  // namespace s21