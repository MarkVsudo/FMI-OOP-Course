//=== src/datatypes/TextType.h ===
#ifndef TEXTTYPE_H
#define TEXTTYPE_H

#include "DataType.h"

class TextType : public DataType
{
public:
  TextType() : DataType(DataTypeEnum::TEXT) {}
  TextType(const std::string &val) : DataType(DataTypeEnum::TEXT) { setValue(val); }

  bool setValue(const std::string &val) override;
  DataType *clone() const override;
  int compare(const DataType &other) const override;
  bool isValid(const std::string &val) const override;
};

#endif