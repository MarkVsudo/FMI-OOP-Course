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

  // Фунцкия за преоразмеряване
  void resize(size_t newCapacity);

public:
  // Конструктори
  MyArray();
  MyArray(const MyArray &other);

  // Деструктор
  ~MyArray();

  // Assignment operator
  MyArray &operator=(const MyArray &other);

  // Функции за размер
  size_t size() const;
  bool empty() const;
  void reserve(size_t newCapacity);

  // Достъп до елементи
  T &operator[](size_t index);
  const T &operator[](size_t index) const;

  // Модификатори
  void pushBack(const T &value);
  void erase(size_t index);
  void clear();

  // Достъп до елементи
  T *begin();
  const T *begin() const;
  T *end();
  const T *end() const;
};

// Преоразмеряване на масива с копиране на даанните
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

// Конструктор по подразбиране - създава празен масив
template <typename T>
MyArray<T>::MyArray() : data_(nullptr), size_(0), capacity_(0) {}

// Copy конструктор
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

// Деструктор - освобождава алокираната памет
template <typename T>
MyArray<T>::~MyArray()
{
  delete[] data_;
}

// Оператор за присвояване
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

// Връща текущия брой елементи в масива
template <typename T>
size_t MyArray<T>::size() const { return size_; }

// Проверява дали масивът е празен
template <typename T>
bool MyArray<T>::empty() const { return size_ == 0; }

// Оператор за достъп до елемент по индекс (non-const версия)
template <typename T>
T &MyArray<T>::operator[](size_t index) { return data_[index]; }

// Оператор за достъп до елемент по индекс (const версия)
template <typename T>
const T &MyArray<T>::operator[](size_t index) const { return data_[index]; }

// Добавя елемент в края на масива
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

// Премахва елемент на определен index в масива
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

// Премахва елементите от масива
template <typename T>
void MyArray<T>::clear()
{
  size_ = 0;
}

template <typename T>
void MyArray<T>::reserve(size_t newCapacity)
{
  // Резервира памет за масива без да променя текущия размер
  // Увеличава капацитета само ако новият е по-голям от текущия
  if (newCapacity > capacity_)
  {
    resize(newCapacity); // Алокира нова памет с по-голям капацитет
  }
}

// Връща указател към първия елемент на масива
// (non-const версия)
template <typename T>
T *MyArray<T>::begin() { return data_; }

// Връща константен указател към първия елемент на масива
// (const версия)
template <typename T>
const T *MyArray<T>::begin() const { return data_; }

// Връща указател към позицията след последния елемент
// (non-const версия)
template <typename T>
T *MyArray<T>::end() { return data_ + size_; }

// Връща константен указател към позицията след последния елемент
// (const версия)
template <typename T>
const T *MyArray<T>::end() const { return data_ + size_; }
