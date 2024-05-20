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
  if (this != &v)
  {
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

} // namespace s21

#endif