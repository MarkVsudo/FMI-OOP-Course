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
  // Constructors
  String();
  String(const char *str);
  String(const String &other);

  // Destructor
  ~String();

  // Assignment operators
  String &operator=(const String &other);
  String &operator=(const char *str);

  // Access methods
  const char *c_str() const;
  size_t length() const;
  size_t size() const;
  bool empty() const;

  // Element access
  char &operator[](size_t index);
  const char &operator[](size_t index) const;
  char front() const;
  char back() const;

  // Modifiers
  void pushBack(char c);
  void clear();

  // String operations
  String substr(size_t pos, size_t len = SIZE_MAX) const;

  // Concatenation operators
  String operator+(const String &other) const;
  String &operator+=(const String &other);

  // Comparison methods
  int compare(const String &other) const;

  // Comparison operators
  bool operator==(const String &other) const;
  bool operator!=(const String &other) const;
  bool operator<(const String &other) const;
  bool operator<=(const String &other) const;
  bool operator>(const String &other) const;
  bool operator>=(const String &other) const;
};
