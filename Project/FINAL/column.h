#pragma once

#include <stdexcept>
#include "string.h"
#include "myArray.h"
#include "cell.h"

class Column
{
private:
  String name_;
  DataType type_;
  Vector<Cell> cells_;

public:
  // Constructors
  Column();
  Column(const String &name);

  // Name getters and setters
  const String &getName() const;
  void setName(const String &name);

  // Type getters and setters
  DataType getType() const;
  void setType(DataType type);

  // Size
  size_t size() const;

  // Cell access and modification
  const Cell &getCell(size_t index) const;
  void setCell(size_t index, const Cell &cell);
  void addCell(const Cell &cell);
  void removeCell(size_t index);

  // Statistical operations
  Cell getMinValue() const;
  Cell getMaxValue() const;
  Cell getMostFrequentValue() const;
};
