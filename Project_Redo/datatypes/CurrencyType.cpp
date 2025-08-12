//=== src/datatypes/CurrencyType.cpp ===
#include "CurrencyType.h"
#include "../utils/StringUtils.h"
#include <cstdlib>

bool CurrencyType::setValue(const std::string &val)
{
  if (!isValid(val))
    return false;

  std::string cleanVal = StringUtils::removeQuotes(StringUtils::trim(val));

  // Find where number ends and currency begins
  size_t currencyStart = cleanVal.length() - 3;
  std::string numPart = cleanVal.substr(0, currencyStart);
  currency = cleanVal.substr(currencyStart);

  amount = std::strtod(numPart.c_str(), nullptr);
  value = cleanVal;
  return true;
}

DataType *CurrencyType::clone() const
{
  return new CurrencyType(value);
}

int CurrencyType::compare(const DataType &other) const
{
  if (other.getType() != DataTypeEnum::CURRENCY)
    return -1;

  const CurrencyType &otherCurr = static_cast<const CurrencyType &>(other);

  // First compare by currency
  if (currency < otherCurr.currency)
    return -1;
  if (currency > otherCurr.currency)
    return 1;

  // Then by amount
  if (amount < otherCurr.amount)
    return -1;
  if (amount > otherCurr.amount)
    return 1;
  return 0;
}

bool CurrencyType::isValid(const std::string &val) const
{
  std::string cleanVal = StringUtils::removeQuotes(StringUtils::trim(val));

  if (cleanVal.length() < 4)
    return false; // At least 1 digit + 3 currency chars

  // Check if last 3 characters are letters
  for (int i = cleanVal.length() - 3; i < cleanVal.length(); ++i)
  {
    char c = cleanVal[i];
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
    {
      return false;
    }
  }

  // Check if the part before currency is a valid number
  std::string numPart = cleanVal.substr(0, cleanVal.length() - 3);
  return StringUtils::isNumber(numPart);
}