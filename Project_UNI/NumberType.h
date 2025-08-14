//=== src/datatypes/NumberType.h ===
#pragma once
#include "DataType.h"
#include "StringUtils.h"

class NumberType : public DataType
{
private:
  double numValue;

public:
  NumberType() : DataType(DataTypeEnum::NUMBER), numValue(0.0) {}
  NumberType(const std::string &val) : DataType(DataTypeEnum::NUMBER), numValue(0.0) { setValue(val); }
  NumberType(double val) : DataType(DataTypeEnum::NUMBER), numValue(val)
  {
    value = StringUtils::toString(val);
  }

  bool setValue(const std::string &val) override;
  DataType *clone() const override;
  int compare(const DataType &other) const override;
  bool isValid(const std::string &val) const override;

  double getNumericValue() const { return numValue; }
};
