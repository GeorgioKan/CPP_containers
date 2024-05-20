#define S21_VECTOR_HPP
#ifdef S21_VECTOR_HPP

#include <iostream>

namespace s21 {
template <typename T> class s21_vector {

public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = T *;
  using const_iterator = const T &;
  using size_type = size_t;

  // Functions
  s21_vector();
  s21_vector(size_type n);
  s21_vector(std::initializer_list<value_type> const &items);
  s21_vector(const s21_vector &v);
  s21_vector(s21_vector &&v);
  ~s21_vector();
  s21_vector &operator=(s21_vector &&v) noexcept;

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  // Vector iterators
  iterator begin();
  iterator end();

  // Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(s21_vector &other);

private:
  iterator data_;
  size_type size_;
  size_type capacity_;
};

template <typename T> s21_vector<T>::s21_vector() {
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T> s21_vector<T>::s21_vector(size_type n) {
  size_ = n;
  capacity_ = n;
  data_ = new value_type[n];
  std::fill_n(data_, n, value_type());
}

template <typename T> s21_vector<T>::~s21_vector() {
  size_ = 0;
  capacity_ = 0;
  delete[] data_;
}

template <typename T>
s21_vector<T>::s21_vector(const s21_vector &v)
    : data_(new value_type[v.capacity_]), size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

template <typename T>
s21_vector<T>::s21_vector(std::initializer_list<value_type> const &items)
    : size_(items.size()), capacity_(items.capacity()),
      data_(new value_type[items.size()]) {
  std::copy(items.begin(), items.end(), data_);
}

template <typename T> s21_vector<T>::s21_vector(s21_vector &&v) {
  data_ = std::exchange(v.data_, nullptr);
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
}

template <typename T>
s21_vector<T> &s21_vector<T>::operator=(s21_vector<T> &&v) noexcept {
  if (this != &v) {
    data_ delete[];

    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return this;
}

template <typename T>
s21_vector<T>::reference s21_vector<T>::at(size_type pos) {
  if (pos > size_) {
    throw std::out_of_range("vector::at - out of range");
  }
  return data_[pos];
}

template <typename T>
s21_vector<T>::reference s21_vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T> s21_vector<T>::const_reference s21_vector<T>::front() {
  if (size_ == 0) {
    throw std::out_of_range("vector::front - vector is empty");
  }
  return data_[0];
}

template <typename T> s21_vector<T>::const_reference s21_vector<T>::back() {
  if (size_ == 0) {
    throw std::out_of_range("vector::back - vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T> T *s21_vector<T>::data() { return data_; }

template <typename T> s21_vector<T>::iterator s21_vector<T>::begin() {
  return data_;
}

template <typename T> s21_vector<T>::iterator s21_vector<T>::end() {
  return data_ + size_;
}

template <typename T> bool s21_vector<T>::empty() { return size_ == 0; }

template <typename T> s21_vector<T>::size_type s21_vector<T>::size() {
  if (size_ == 0) {
    throw std::out_of_range("vector::size - vector is empty")
  }
  return size_;
}

template <typename T> s21_vector<T>::size_type s21_vector<T>::max_size() {
  return std::numeric_limits<size_type> max();
}

template <typename T> void s21_vector<T>::reserve(size_type size) {
  if (size <= capacity_) {
    throw std::out_of_range(
        "vector::reserve - too large size for a new capacity")
  }
  if (size > max_size()) {
    throw std::length_error("vecto::reserve - impossible to allocate memory")
  }

  iterator new_data = new value_type[size];
  for (size_type i = 0; i < size; i++) {
    new_data[i] = std::move(data_[i]);
  }
  delete data_[];

  data_ = new_data;
  capacity_ = size;
}

template <typename T> s21_vector<T>::size_type s21_vector<T>::capacity() {
  return capacity_;
}

template <typename T> void s21_vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    iterator new_data = new value_type[size_];
    std::copy(data_, data_ + size_, new_data);
    delete data_[];
    data_ = new_data;
    capacity_ = size_;
  }
}
template <typename T> void s21_vector<T>::clear() {
  delete data_[];
  size_ = 0;
  capacity = 0;
  data_ = nullptr;
}
template <typename T>
s21_vector<T>::iterator s21_vector<T>::insert(iterator pos,
                                              const_reference value) {
  size_type current_position = pos - begin();
  if (size_ > pos) {
    throw std::out_of_range(
        "vector::insert - the insert position is out of memory range")
  }

  size_type new_capacity = 1;
  if (capacity_ <= size_) {
    new_capacity = capacity * 2;
  }

  if (capacity_ >= size_) {
    reserve(new_capacity);
    pos = begin() + current_position;
  }

  std::move_backward(pos, end(), end() + 1);

  *pos = value;
  size_++;
}

template <typename T> void s21_vector<T>::erase(iterator pos) {}

template <typename T> void s21_vector<T>::push_back(const_reference value) {}

template <typename T> void s21_vector<T>::pop_back() {}

template <typename T> void s21_vector<T>::swap(s21_vector &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity);
}

} // namespace s21

#endif