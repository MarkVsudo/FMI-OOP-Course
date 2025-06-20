#include "myString.h"

void String::resize(size_t newCapacity)
{
  char *newData = new char[newCapacity + 1];
  if (data_)
  {
    for (size_t i = 0; i < size_; ++i)
    {
      newData[i] = data_[i];
    }
    delete[] data_;
  }
  data_ = newData;
  data_[size_] = '\0';
  capacity_ = newCapacity;
}

String::String() : data_(nullptr), size_(0), capacity_(0)
{
  resize(16);
}

String::String(const char *str) : data_(nullptr), size_(0), capacity_(0)
{
  if (str)
  {
    size_ = strlen(str);
    resize(size_ > 16 ? size_ * 2 : 16);
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i] = str[i];
    }
    data_[size_] = '\0';
  }
  else
  {
    resize(16);
  }
}

String::String(const String &other) : data_(nullptr), size_(0), capacity_(0)
{
  size_ = other.size_;
  resize(size_ > 16 ? size_ * 2 : 16);
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i] = other.data_[i];
  }
  data_[size_] = '\0';
}

String::~String()
{
  delete[] data_;
}

String &String::operator=(const String &other)
{
  if (this != &other)
  {
    size_ = other.size_;
    if (capacity_ < size_)
    {
      resize(size_ > 16 ? size_ * 2 : 16);
    }
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i] = other.data_[i];
    }
    data_[size_] = '\0';
  }
  return *this;
}

String &String::operator=(const char *str)
{
  if (str)
  {
    size_ = strlen(str);
    if (capacity_ < size_)
    {
      resize(size_ > 16 ? size_ * 2 : 16);
    }
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i] = str[i];
    }
  }
  else
  {
    size_ = 0;
  }
  data_[size_] = '\0';
  return *this;
}

const char *String::c_str() const { return data_ ? data_ : ""; }
size_t String::length() const { return size_; }
size_t String::size() const { return size_; }
bool String::empty() const { return size_ == 0; }

char &String::operator[](size_t index) { return data_[index]; }
const char &String::operator[](size_t index) const { return data_[index]; }

char String::front() const { return size_ > 0 ? data_[0] : '\0'; }
char String::back() const { return size_ > 0 ? data_[size_ - 1] : '\0'; }

void String::pushBack(char c)
{
  if (size_ >= capacity_)
  {
    resize(capacity_ * 2);
  }
  data_[size_++] = c;
  data_[size_] = '\0';
}

void String::clear()
{
  size_ = 0;
  data_[0] = '\0';
}

String String::substr(size_t pos, size_t len) const
{
  if (pos >= size_)
    return String();

  size_t actualLen = (len == SIZE_MAX || pos + len > size_) ? size_ - pos : len;
  String result;
  result.resize(actualLen > 16 ? actualLen * 2 : 16);
  result.size_ = actualLen;

  for (size_t i = 0; i < actualLen; ++i)
  {
    result.data_[i] = data_[pos + i];
  }
  result.data_[result.size_] = '\0';
  return result;
}

String String::operator+(const String &other) const
{
  String result;
  result.resize(size_ + other.size_ + 1);
  result.size_ = size_ + other.size_;

  for (size_t i = 0; i < size_; ++i)
  {
    result.data_[i] = data_[i];
  }
  for (size_t i = 0; i < other.size_; ++i)
  {
    result.data_[size_ + i] = other.data_[i];
  }
  result.data_[result.size_] = '\0';
  return result;
}

String &String::operator+=(const String &other)
{
  size_t newSize = size_ + other.size_;
  if (newSize >= capacity_)
  {
    resize(newSize * 2);
  }
  for (size_t i = 0; i < other.size_; ++i)
  {
    data_[size_ + i] = other.data_[i];
  }
  size_ = newSize;
  data_[size_] = '\0';
  return *this;
}

int String::compare(const String &other) const
{
  return strcmp(c_str(), other.c_str());
}

bool String::operator==(const String &other) const
{
  return compare(other) == 0;
}

bool String::operator!=(const String &other) const
{
  return compare(other) != 0;
}

bool String::operator<(const String &other) const
{
  return compare(other) < 0;
}

bool String::operator<=(const String &other) const
{
  return compare(other) <= 0;
}

bool String::operator>(const String &other) const
{
  return compare(other) > 0;
}

bool String::operator>=(const String &other) const
{
  return compare(other) >= 0;
}
