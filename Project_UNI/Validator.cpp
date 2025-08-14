//=== src/utils/Validator.cpp ===
#include "Validator.h"
#include "StringUtils.h"

bool Validator::isValidEGN(const std::string &egn)
{
  std::string cleanEGN = StringUtils::removeQuotes(StringUtils::trim(egn));

  if (cleanEGN.length() != 10)
    return false;

  // Check if all characters are digits
  for (char c : cleanEGN)
  {
    if (c < '0' || c > '9')
      return false;
  }

  // Extract date components
  int year = (cleanEGN[0] - '0') * 10 + (cleanEGN[1] - '0');
  int month = (cleanEGN[2] - '0') * 10 + (cleanEGN[3] - '0');
  int day = (cleanEGN[4] - '0') * 10 + (cleanEGN[5] - '0');

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

bool Validator::isValidFacultyNumber(const std::string &fn)
{
  std::string cleanFN = StringUtils::removeQuotes(StringUtils::trim(fn));

  if (cleanFN.length() == 5)
  {
    // Old format: 45123
    for (char c : cleanFN)
    {
      if (c < '0' || c > '9')
        return false;
    }

    std::string specialtyCode = cleanFN.substr(0, 2);
    return isValidSpecialtyCode(specialtyCode);
  }

  if (cleanFN.length() == 10)
  {
    // New format: 0MI0400123
    if (cleanFN[0] != '0')
      return false;

    // Check specialty code (positions 1-2)
    std::string specialtyCode = cleanFN.substr(1, 2);
    if (!isValidSpecialtyCode(specialtyCode))
      return false;

    // Check year (positions 3-4) - should be digits
    if (cleanFN[3] < '0' || cleanFN[3] > '9' || cleanFN[4] < '0' || cleanFN[4] > '9')
    {
      return false;
    }

    // Check remaining digits (positions 5-9)
    for (int i = 5; i < 10; ++i)
    {
      if (cleanFN[i] < '0' || cleanFN[i] > '9')
        return false;
    }

    return true;
  }

  return false;
}

bool Validator::isValidCurrency(const std::string &currency)
{
  std::string cleanCurr = StringUtils::removeQuotes(StringUtils::trim(currency));

  if (cleanCurr.length() < 4)
    return false; // At least 1 digit + 3 currency chars

  // Check if last 3 characters are letters
  for (int i = cleanCurr.length() - 3; i < cleanCurr.length(); ++i)
  {
    char c = cleanCurr[i];
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
    {
      return false;
    }
  }

  // Check if the part before currency is a valid number
  std::string numPart = cleanCurr.substr(0, cleanCurr.length() - 3);
  return isValidNumber(numPart);
}

bool Validator::isValidNumber(const std::string &number)
{
  std::string cleanNum = StringUtils::removeQuotes(StringUtils::trim(number));
  return StringUtils::isNumber(cleanNum);
}

bool Validator::isValidDate(int year, int month, int day)
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

bool Validator::isValidSpecialtyCode(const std::string &code)
{
  // Valid specialty codes for FMI
  return code == "MI" || code == "IS" || code == "CS" || code == "SE" ||
         code == "45" || code == "62" || code == "71" || code == "81" || code == "82";
}