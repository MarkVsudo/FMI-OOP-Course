//=== src/core/Column.h ===
#ifndef COLUMN_H
#define COLUMN_H

#include <string>
#include "../datatypes/DataType.h"

class Column
{
private:
  std::string name;
  DataTypeEnum type;

public:
  Column() : name(""), type(DataTypeEnum::TEXT) {}
  Column(const std::string &columnName) : name(columnName), type(DataTypeEnum::TEXT) {}
  Column(const std::string &columnName, DataTypeEnum columnType) : name(columnName), type(columnType) {}

  std::string getName() const { return name; }
  void setName(const std::string &newName) { name = newName; }

  DataTypeEnum getType() const { return type; }
  void setType(DataTypeEnum newType) { type = newType; }
};

#endif