//=== src/datatypes/FacultyNumberType.cpp ===
#include "FacultyNumberType.h"
#include "../utils/StringUtils.h"

bool FacultyNumberType::setValue(const std::string &val)
{
  if (!isValid(val))
    return false;
  value = StringUtils::removeQuotes(StringUtils::trim(val));
  return true;
}

DataType *FacultyNumberType::clone() const
{
  return new FacultyNumberType(value);
}

int FacultyNumberType::compare(const DataType &other) const
{
  if (other.getType() != DataTypeEnum::FACULTY_NUMBER)
    return -1;

  const FacultyNumberType &otherFN = static_cast<const FacultyNumberType &>(other);

  // Compare by specialty first
  std::string mySpec = getSpecialty();
  std::string otherSpec = otherFN.getSpecialty();

  if (mySpec < otherSpec)
    return -1;
  if (mySpec > otherSpec)
    return 1;

  // Same specialty - compare by format (old format comes first)
  bool myOld = isOldFormat();
  bool otherOld = otherFN.isOldFormat();

  if (myOld && !otherOld)
    return -1;
  if (!myOld && otherOld)
    return 1;

  // Same format - compare by number
  int myNum = getNumber();
  int otherNum = otherFN.getNumber();

  if (myNum < otherNum)
    return -1;
  if (myNum > otherNum)
    return 1;
  return 0;
}

bool FacultyNumberType::isValid(const std::string &val) const
{
  std::string cleanVal = StringUtils::removeQuotes(StringUtils::trim(val));

  if (cleanVal.length() == 5)
  {
    // Old format: 45123
    for (char c : cleanVal)
    {
      if (c < '0' || c > '9')
        return false;
    }

    std::string specialtyCode = cleanVal.substr(0, 2);
    return isValidSpecialtyCode(specialtyCode);
  }

  if (cleanVal.length() == 10)
  {
    // New format: 0MI0400123
    if (cleanVal[0] != '0')
      return false;

    // Check specialty code (positions 1-2)
    std::string specialtyCode = cleanVal.substr(1, 2);
    if (!isValidSpecialtyCode(specialtyCode))
      return false;

    // Check year (positions 3-4) - should be digits
    if (cleanVal[3] < '0' || cleanVal[3] > '9' || cleanVal[4] < '0' || cleanVal[4] > '9')
    {
      return false;
    }

    // Check remaining digits (positions 5-9)
    for (int i = 5; i < 10; ++i)
    {
      if (cleanVal[i] < '0' || cleanVal[i] > '9')
        return false;
    }

    return true;
  }

  return false;
}

bool FacultyNumberType::isOldFormat() const
{
  return value.length() == 5;
}

std::string FacultyNumberType::getSpecialty() const
{
  if (isOldFormat())
  {
    return value.substr(0, 2);
  }
  else
  {
    return value.substr(1, 2);
  }
}

int FacultyNumberType::getNumber() const
{
  if (isOldFormat())
  {
    return (value[2] - '0') * 1000 + (value[3] - '0') * 100 + (value[4] - '0') * 10 + (value[4] - '0');
  }
  else
  {
    int num = 0;
    for (int i = 5; i < 10; ++i)
    {
      num = num * 10 + (value[i] - '0');
    }
    return num;
  }
}

bool FacultyNumberType::isValidSpecialtyCode(const std::string &code) const
{
  // Valid specialty codes for FMI
  return code == "MI" || code == "IS" || code == "CS" || code == "SE" ||
         code == "45" || code == "62" || code == "71" || code == "81" || code == "82";
}