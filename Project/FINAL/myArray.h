#pragma once
#include <cstdlib>
#include <new>

template <typename T>
class MyArray
{
private:
  T *data_;
  size_t size_;
  size_t capacity_;

  void resize(size_t newCapacity);

public:
  // Constructors
  MyArray();
  MyArray(const MyArray &other);

  // Destructor
  ~MyArray();

  // Assignment operator
  MyArray &operator=(const MyArray &other);

  // Capacity methods
  size_t size() const;
  bool empty() const;
  void reserve(size_t newCapacity);

  // Element access
  T &operator[](size_t index);
  const T &operator[](size_t index) const;

  // Modifiers
  void pushBack(const T &value);
  void erase(size_t index);
  void clear();

  // Iterator-like access
  T *begin();
  const T *begin() const;
  T *end();
  const T *end() const;
};

// Template implementation must be in header file
template <typename T>
void MyArray<T>::resize(size_t newCapacity)
{
  T *newData = new T[newCapacity];
  if (data_)
  {
    for (size_t i = 0; i < size_; ++i)
    {
      newData[i] = data_[i];
    }
    delete[] data_;
  }
  data_ = newData;
  capacity_ = newCapacity;
}

template <typename T>
MyArray<T>::MyArray() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
MyArray<T>::MyArray(const MyArray &other) : data_(nullptr), size_(0), capacity_(0)
{
  if (other.size_ > 0)
  {
    resize(other.capacity_);
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i] = other.data_[i];
    }
  }
}

template <typename T>
MyArray<T>::~MyArray()
{
  delete[] data_;
}

template <typename T>
MyArray<T> &MyArray<T>::operator=(const MyArray &other)
{
  if (this != &other)
  {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;

    if (other.size_ > 0)
    {
      resize(other.capacity_);
      size_ = other.size_;
      for (size_t i = 0; i < size_; ++i)
      {
        data_[i] = other.data_[i];
      }
    }
  }
  return *this;
}

template <typename T>
size_t MyArray<T>::size() const { return size_; }

template <typename T>
bool MyArray<T>::empty() const { return size_ == 0; }

template <typename T>
T &MyArray<T>::operator[](size_t index) { return data_[index]; }

template <typename T>
const T &MyArray<T>::operator[](size_t index) const { return data_[index]; }

template <typename T>
void MyArray<T>::pushBack(const T &value)
{
  if (size_ >= capacity_)
  {
    size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
    resize(newCapacity);
  }
  data_[size_++] = value;
}

template <typename T>
void MyArray<T>::erase(size_t index)
{
  if (index < size_)
  {
    for (size_t i = index; i < size_ - 1; ++i)
    {
      data_[i] = data_[i + 1];
    }
    --size_;
  }
}

template <typename T>
void MyArray<T>::clear()
{
  size_ = 0;
}

template <typename T>
void MyArray<T>::reserve(size_t newCapacity)
{
  if (newCapacity > capacity_)
  {
    resize(newCapacity);
  }
}

template <typename T>
T *MyArray<T>::begin() { return data_; }

template <typename T>
const T *MyArray<T>::begin() const { return data_; }

template <typename T>
T *MyArray<T>::end() { return data_ + size_; }

template <typename T>
const T *MyArray<T>::end() const { return data_ + size_; }
