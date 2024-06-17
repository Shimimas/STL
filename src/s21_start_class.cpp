namespace s21 {

typename start::size_type start::size() { return capacity_; }

bool start::empty() { return capacity_ == 0 ? true : false; }

}  // namespace s21