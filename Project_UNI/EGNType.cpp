//=== src/datatypes/EGNType.cpp ===
#include "EGNType.h"
#include "StringUtils.h"

bool EGNType::setValue(const std::string &val)
{
  if (!isValid(val))
    return false;
  value = StringUtils::removeQuotes(StringUtils::trim(val));
  return true;
}

DataType *EGNType::clone() const
{
  return new EGNType(value);
}

int EGNType::compare(const DataType &other) const
{
  if (other.getType() != DataTypeEnum::EGN)
    return -1;

  const std::string &otherVal = other.getValue();
  if (value < otherVal)
    return -1;
  if (value > otherVal)
    return 1;
  return 0;
}

bool EGNType::isValid(const std::string &val) const
{
  std::string cleanVal = StringUtils::removeQuotes(StringUtils::trim(val));

  if (cleanVal.length() != 10)
    return false;

  // Check if all characters are digits
  for (char c : cleanVal)
  {
    if (c < '0' || c > '9')
      return false;
  }

  // Extract date components
  int year = (cleanVal[0] - '0') * 10 + (cleanVal[1] - '0');
  int month = (cleanVal[2] - '0') * 10 + (cleanVal[3] - '0');
  int day = (cleanVal[4] - '0') * 10 + (cleanVal[5] - '0');

  // Determine century and adjust year
  if (month >= 1 && month <= 12)
  {
    year += 1900; // 1900-1999
  }
  else if (month >= 21 && month <= 32)
  {
    year += 1800; // 1800-1899
    month -= 20;
  }
  else if (month >= 41 && month <= 52)
  {
    year += 2000; // 2000-2099
    month -= 40;
  }
  else
  {
    return false; // Invalid month encoding
  }

  return isValidDate(year, month, day);
}

bool EGNType::isValidDate(int year, int month, int day) const
{
  if (month < 1 || month > 12)
    return false;
  if (day < 1)
    return false;

  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Check for leap year
  if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
  {
    daysInMonth[1] = 29;
  }

  return day <= daysInMonth[month - 1];
}