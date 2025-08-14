//=== src/datatypes/CurrencyType.h ===
#pragma once

#include "DataType.h"

class CurrencyType : public DataType
{
private:
  double amount;
  std::string currency;

public:
  CurrencyType() : DataType(DataTypeEnum::CURRENCY), amount(0.0) {}
  CurrencyType(const std::string &val) : DataType(DataTypeEnum::CURRENCY), amount(0.0) { setValue(val); }

  bool setValue(const std::string &val) override;
  DataType *clone() const override;
  int compare(const DataType &other) const override;
  bool isValid(const std::string &val) const override;

  double getAmount() const { return amount; }
  std::string getCurrency() const { return currency; }
};
