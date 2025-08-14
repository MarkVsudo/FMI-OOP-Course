//=== src/core/Cell.h ===
#pragma once

#include "DataType.h"
#include <string>

class Cell
{
private:
  DataType *data;

public:
  Cell();
  Cell(const std::string &value);
  Cell(const Cell &other);
  Cell &operator=(const Cell &other);
  ~Cell();

  bool setValue(const std::string &value);
  std::string getValue() const;
  DataType *getDataType() const;
  DataTypeEnum getType() const;

  int compare(const Cell &other) const;

  bool operator==(const Cell &other) const;
  bool operator!=(const Cell &other) const;
  bool operator<(const Cell &other) const;
  bool operator<=(const Cell &other) const;
  bool operator>(const Cell &other) const;
  bool operator>=(const Cell &other) const;
};
