//=== src/datatypes/EGNType.h ===
#ifndef EGNTYPE_H
#define EGNTYPE_H

#include "DataType.h"

class EGNType : public DataType
{
public:
  EGNType() : DataType(DataTypeEnum::EGN) {}
  EGNType(const std::string &val) : DataType(DataTypeEnum::EGN) { setValue(val); }

  bool setValue(const std::string &val) override;
  DataType *clone() const override;
  int compare(const DataType &other) const override;
  bool isValid(const std::string &val) const override;

private:
  bool isValidDate(int year, int month, int day) const;
};

#endif