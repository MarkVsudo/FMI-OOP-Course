#pragma once
#include <cstring>
#include <cstdlib>
#include <iostream>

class String
{
private:
  char *data_;
  size_t size_;
  size_t capacity_;

  void resize(size_t newCapacity);

public:
  // Контруктори
  String();
  String(const char *str);
  String(const String &other);

  // Деструктор
  ~String();

  // Оператор за присвояване
  String &operator=(const String &other);
  String &operator=(const char *str);

  // Функции за достъп
  const char *c_str() const;
  size_t length() const;
  size_t size() const;
  bool empty() const;

  // Достъп до елемент
  char &operator[](size_t index);
  const char &operator[](size_t index) const;
  char front() const;
  char back() const;

  // Модификатори
  void pushBack(char c);
  void clear();

  // Операции над низове
  String substr(size_t pos, size_t len = SIZE_MAX) const;

  // Оператори за конкатенация на низове
  String operator+(const String &other) const;
  String &operator+=(const String &other);

  // Функция за сравнение
  int compare(const String &other) const;

  // Оператори за сравнение
  bool operator==(const String &other) const;
  bool operator!=(const String &other) const;
  bool operator<(const String &other) const;
  bool operator<=(const String &other) const;
  bool operator>(const String &other) const;
  bool operator>=(const String &other) const;
};
