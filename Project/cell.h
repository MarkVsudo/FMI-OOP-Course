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

  // Helper methods
  int compareValues(const Cell &other) const;
  int compareFacultyNumbers(const Cell &other) const;
  String extractSpecialty(const String &facNum) const;

public:
  // Constructors
  Cell();
  Cell(const String &value, DataType type);

  // Getters and setters
  const String &getValue() const;
  DataType getType() const;
  void setValue(const String &value);
  void setType(DataType type);

  // Comparison operators
  bool operator==(const Cell &other) const;
  bool operator!=(const Cell &other) const;
  bool operator<(const Cell &other) const;
  bool operator<=(const Cell &other) const;
  bool operator>(const Cell &other) const;
  bool operator>=(const Cell &other) const;
};
