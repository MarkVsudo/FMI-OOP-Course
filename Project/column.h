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
  MyArray<Cell> cells_;

public:
  // Конструктори
  Column();
  Column(const String &name);

  // Getter-и и Setter-и
  const String &getName() const;
  void setName(const String &name);

  DataType getType() const;
  void setType(DataType type);

  // Size
  size_t size() const;

  // Достъп до клетки и модификация
  const Cell &getCell(size_t index) const;
  void setCell(size_t index, const Cell &cell);
  void addCell(const Cell &cell);
  void removeCell(size_t index);

  // Статичстически операции
  Cell getMinValue() const;
  Cell getMaxValue() const;
  Cell getMostFrequentValue() const;
};
