//=== src/datatypes/NumberType.cpp ===
#include "NumberType.h"
#include "../utils/StringUtils.h"
#include <cstdlib>

bool NumberType::setValue(const std::string &val)
{
  if (!isValid(val))
    return false;

  std::string cleanVal = StringUtils::removeQuotes(StringUtils::trim(val));
  numValue = std::strtod(cleanVal.c_str(), nullptr);
  value = cleanVal;
  return true;
}

DataType *NumberType::clone() const
{
  return new NumberType(numValue);
}

int NumberType::compare(const DataType &other) const
{
  if (other.getType() != DataTypeEnum::NUMBER)
    return -1;

  const NumberType &otherNum = static_cast<const NumberType &>(other);
  double otherVal = otherNum.getNumericValue();

  if (numValue < otherVal)
    return -1;
  if (numValue > otherVal)
    return 1;
  return 0;
}

bool NumberType::isValid(const std::string &val) const
{
  std::string cleanVal = StringUtils::removeQuotes(StringUtils::trim(val));
  return StringUtils::isNumber(cleanVal);
}
