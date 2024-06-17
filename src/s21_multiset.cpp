namespace s21 {

template <typename key_type>
multiset<key_type>::multiset(std::initializer_list<value_type> const& items)
    : tree<value_type>() {
  for (auto it = items.begin(); it != items.end(); it++) {
    this->insert(*it);
  }
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::begin() {
  return iterator(this->find_start_el());
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::end() {
  return iterator(this->find_end_el()->right_);
}

template <typename key_type>
multiset<key_type> multiset<key_type>::operator=(multiset&& map) {
  if (!this->empty()) {
    this->clear();
  }
  this->copy(map.root_);
  return *this;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::insert(
    const value_type& value) {
  typename multiset<key_type>::iterator result(nullptr);
  if (this->root_ == nullptr) {
    this->create_tree(value);
  } else {
    typename tree<value_type>::data* curr = this->root_;
    bool stop = true;
    while (curr != nullptr && stop == true) {
      if (curr->value_ > value && curr->left_ == nullptr) {
        curr->left_ =
            new typename tree<value_type>::data(value, nullptr, nullptr, curr);
        result = typename tree<value_type>::iterator(curr->left_);
        this->capacity_++;
        stop = false;
      } else if (curr->value_ <= value && curr->right_ == nullptr) {
        curr->right_ =
            new typename tree<value_type>::data(value, nullptr, nullptr, curr);
        result = typename tree<value_type>::iterator(curr->right_);
        this->capacity_++;
        stop = false;
      } else if (curr->value_ > value) {
        curr = curr->left_;
      } else {
        curr = curr->right_;
      }
    }
  }
  return result;
}

template <typename key_type>
void multiset<key_type>::swap(multiset& other) {
  this->swap_base(other.root_, other.capacity_);
}

template <typename key_type>
typename tree<typename multiset<key_type>::value_type>::data*
multiset<key_type>::find_by_key(const key_type& key) {
  typename tree<value_type>::data* result = this->root_;
  if (result != nullptr) {
    while (key != result->value_) {
      if (key >= result->value_ && result->right_ != nullptr) {
        result = result->right_;
      } else if (key < result->value_ && result->left_ != nullptr) {
        result = result->left_;
      } else {
        break;
      }
    }
    if (key != result->value_) {
      result = nullptr;
    }
  }
  return result;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::find(
    const key_type& key) {
  return iterator(find_by_key(key));
}

template <typename key_type>
bool multiset<key_type>::contains(const key_type& key) {
  bool result = true;
  if (find_by_key(key) == nullptr) {
    result = false;
  }
  return result;
}

template <typename key_type>
typename multiset<key_type>::size_type multiset<key_type>::count(
    const key_type& key) {
  typename multiset<key_type>::size_type result = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      result++;
    }
  }
  return result;
}

template <typename key_type>
std::pair<typename multiset<key_type>::iterator,
          typename multiset<key_type>::iterator>
multiset<key_type>::equal_range(const key_type& key) {
  std::pair<typename multiset<key_type>::iterator,
            typename multiset<key_type>::iterator>
      result(iterator(nullptr), iterator(nullptr));
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      if (result.first.ptr == nullptr) {
        result.first.ptr = it.ptr;
      }
      result.second.ptr = it.ptr;
    }
  }
  return result;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::lower_bound(
    const key_type& key) {
  typename multiset<key_type>::iterator result(nullptr);
  for (auto it = begin(); it != end(); ++it) {
    if (*it >= key) {
      result.ptr = it.ptr;
      break;
    }
  }
  return result;
}

template <typename key_type>
typename multiset<key_type>::iterator multiset<key_type>::upper_bound(
    const key_type& key) {
  typename multiset<key_type>::iterator result(nullptr);
  for (auto it = begin(); it != end(); ++it) {
    if (key < *it) {
      result.ptr = it.ptr;
      break;
    }
  }
  return result;
}

template <typename key_type>
void multiset<key_type>::merge(multiset& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(it.ptr->value_);
  }
  other.delete_tree(other.root_);
  other.capacity_ = 0;
  other.root_ = nullptr;
}

template <typename key_type>
void multiset<key_type>::copy(const typename tree<value_type>::data* map) {
  if (map != nullptr) {
    copy(map->left_);
    insert(map->value_);
    copy(map->right_);
  }
}

template <typename value_type>
template <typename... Args>
vector<std::pair<typename multiset<value_type>::iterator, bool>>
multiset<value_type>::emplace(Args&&... args) {
  multiset<value_type> multiset_tmp;
  multiset_tmp.emplace_help(args...);
  vector<std::pair<typename multiset<value_type>::iterator, bool>>
      vector_result;
  for (auto it = multiset_tmp.begin(); it != multiset_tmp.end(); ++it) {
    insert(*it);
  }
  return vector_result;
}

template <typename value_type>
template <typename V, typename... Args>
void multiset<value_type>::emplace_help(V value, Args&&... args) {
  insert(value);
  emplace_help(args...);
}

}  // namespace s21