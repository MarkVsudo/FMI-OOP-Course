//=== src/datatypes/FacultyNumberType.h ===
#pragma once

#include "DataType.h"

class FacultyNumberType : public DataType
{
public:
  FacultyNumberType() : DataType(DataTypeEnum::FACULTY_NUMBER) {}
  FacultyNumberType(const std::string &val) : DataType(DataTypeEnum::FACULTY_NUMBER) { setValue(val); }

  bool setValue(const std::string &val) override;
  DataType *clone() const override;
  int compare(const DataType &other) const override;
  bool isValid(const std::string &val) const override;

private:
  bool isOldFormat() const;
  std::string getSpecialty() const;
  int getNumber() const;
  bool isValidSpecialtyCode(const std::string &code) const;
};
