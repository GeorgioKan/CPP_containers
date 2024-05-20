#define S21_LIST_H
#ifdef S21_LIST_H

template <typename T> class s21_list {
private:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;

public:
  // Functions
  s21_list();
  s21_list(size_type n);
  s21_list(std::initializer_s21_list<value_type> const &items);
  s21_list(const s21_list &l);
  s21_list(s21_list &&l);
  ~s21_list();
  operator=(s21_list && l);

  // Element access
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear() iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();
};

s21_list::s21_list() {}

s21_list::~s21_list() {}

#endif