#pragma once
#include <stdexcept>
#include "myString.h"
#include "dataType.h"
#include "utils.h"

class Cell
{
private:
  String value_;
  DataType type_;

  // Помощни функции
  int compareValues(const Cell &other) const;
  int compareFacultyNumbers(const Cell &other) const;
  String extractSpecialty(const String &facNum) const;

public:
  // Конструктори
  Cell();
  Cell(const String &value, DataType type);

  // Getter-и и Setter-и
  const String &getValue() const;
  DataType getType() const;
  void setValue(const String &value);
  void setType(DataType type);

  // Оператори за сравнение
  bool operator==(const Cell &other) const;
  bool operator!=(const Cell &other) const;
  bool operator<(const Cell &other) const;
  bool operator<=(const Cell &other) const;
  bool operator>(const Cell &other) const;
  bool operator>=(const Cell &other) const;
};
