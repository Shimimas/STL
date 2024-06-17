namespace s21 {

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const& items)
    : tree<value_type>() {
  for (auto it = items.begin(); it != items.end(); it++) {
    this->insert(*it);
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type> map<key_type, mapped_type>::operator=(map&& map) {
  if (!this->empty()) {
    this->clear();
  }
  this->copy(map.root_);
  return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
  return iterator(this->find_start_el());
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
  return iterator(this->find_end_el()->right_);
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(
    const typename map<key_type, mapped_type>::value_type& value) {
  std::pair<typename tree<value_type>::iterator, bool> result(nullptr, true);
  if (this->root_ == nullptr) {
    this->create_tree(value);
  } else {
    typename tree<value_type>::data* curr = this->root_;
    bool stop = true;
    while (curr != nullptr && stop == true) {
      if (curr->value_.first == value.first) {
        result.second = false;
        throw std::runtime_error("Error: cant add eq ell");
      } else if (curr->value_.first > value.first && curr->left_ == nullptr) {
        curr->left_ =
            new typename tree<value_type>::data(value, nullptr, nullptr, curr);
        result.first = typename tree<value_type>::iterator(curr->left_);
        this->capacity_++;
        stop = false;
      } else if (curr->value_.first < value.first && curr->right_ == nullptr) {
        curr->right_ =
            new typename tree<value_type>::data(value, nullptr, nullptr, curr);
        result.first = typename tree<value_type>::iterator(curr->right_);
        this->capacity_++;
        stop = false;
      } else if (curr->value_.first > value.first) {
        curr = curr->left_;
      } else {
        curr = curr->right_;
      }
    }
  }
  return result;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  std::pair<typename tree<value_type>::iterator, bool> result(nullptr, true);
  result.first = find_by_key(key);
  if (result.first != nullptr) {
    result.first.ptr->value_.second = obj;
    result.second = true;
  } else {
    result.second = false;
  }
  return result;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  std::pair<typename tree<value_type>::iterator, bool> result(nullptr, true);
  if (contains(key)) {
    result = insert(key, obj);
  } else {
    result = insert({key, obj});
  }
  return result;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) {
  bool result = true;
  if (find_by_key(key) == nullptr) {
    result = false;
  }
  return result;
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) {
  typename map<key_type, mapped_type>::data* tmp = find_by_key(key);
  if (tmp == nullptr) {
    throw std::runtime_error("Error: this key not detected");
  }
  return tmp->value_.second;
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::operator[](const key_type& key) {
  typename map<key_type, mapped_type>::data* tmp = find_by_key(key);
  if (tmp == nullptr) {
    tmp = insert({key, 0}).first.ptr;
  }
  return tmp->value_.second;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
  this->swap_base(other.root_, other.capacity_);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    if (!contains(it.ptr->value_.first)) {
      insert(it.ptr->value_);
    }
  }
}

template <typename key_type, typename mapped_type>
typename tree<typename map<key_type, mapped_type>::value_type>::data*
map<key_type, mapped_type>::find_by_key(const key_type& key) {
  typename tree<typename map<key_type, mapped_type>::value_type>::data* result =
      this->root_;
  if (result != nullptr) {
    while (key != result->value_.first) {
      if (key > result->value_.first && result->right_ != nullptr) {
        result = result->right_;
      } else if (key < result->value_.first && result->left_ != nullptr) {
        result = result->left_;
      } else {
        break;
      }
    }
    if (key != result->value_.first) {
      result = nullptr;
    }
  }
  return result;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::copy(
    const typename tree<value_type>::data* map) {
  if (map != nullptr) {
    copy(map->left_);
    insert(map->value_);
    copy(map->right_);
  }
}

template <typename key_type, typename mapped_type>
template <typename... Args>
vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
map<key_type, mapped_type>::emplace(Args&&... args) {
  map<key_type, mapped_type> multiset_tmp;
  multiset_tmp.emplace_help(args...);
  vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
      vector_result;
  for (auto it = multiset_tmp.begin(); it != multiset_tmp.end(); ++it) {
    insert(*it);
  }
  return vector_result;
}

template <typename key_type, typename mapped_type>
template <typename V, typename... Args>
void map<key_type, mapped_type>::emplace_help(V value, Args&&... args) {
  insert(value);
  emplace_help(args...);
}

}  // namespace s21