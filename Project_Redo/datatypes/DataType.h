//=== src/datatypes/DataType.h ===
#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>

enum class DataTypeEnum
{
  TEXT,
  NUMBER,
  CURRENCY,
  EGN,
  FACULTY_NUMBER
};

class DataType
{
protected:
  std::string value;
  DataTypeEnum type;

public:
  DataType(DataTypeEnum t) : type(t) {}
  virtual ~DataType() {}

  virtual bool setValue(const std::string &val) = 0;
  virtual std::string getValue() const { return value; }
  virtual DataType *clone() const = 0;
  virtual int compare(const DataType &other) const = 0;
  virtual bool isValid(const std::string &val) const = 0;

  DataTypeEnum getType() const { return type; }

  static DataType *detectType(const std::string &val);
};

#endif
