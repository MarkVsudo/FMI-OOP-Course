#include "utils.h"
#include <cstdlib>
#include <iostream>

// String conversion functions
double stringToDouble(const String &str)
{
  return atof(str.c_str());
}

int stringToInt(const String &str)
{
  return atoi(str.c_str());
}

String intToString(int value)
{
  char buffer[32];
  sprintf(buffer, "%d", value);
  return String(buffer);
}

// Character classification functions
bool isDigitChar(char c)
{
  return c >= '0' && c <= '9';
}

bool isAlphaChar(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isSpaceChar(char c)
{
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

// String validation functions
bool isAllDigits(const String &str)
{
  for (size_t i = 0; i < str.length(); ++i)
  {
    if (!isDigitChar(str[i]))
      return false;
  }
  return true;
}

bool isAllAlpha(const String &str)
{
  for (size_t i = 0; i < str.length(); ++i)
  {
    if (!isAlphaChar(str[i]))
      return false;
  }
  return true;
}

bool isNumber(const String &str)
{
  if (str.empty())
    return false;

  size_t start = 0;
  if (str[0] == '-' || str[0] == '+')
  {
    start = 1;
    if (str.length() == 1)
      return false;
  }

  bool hasDecimal = false;
  for (size_t i = start; i < str.length(); ++i)
  {
    if (str[i] == '.')
    {
      if (hasDecimal)
        return false;
      hasDecimal = true;
    }
    else if (!isDigitChar(str[i]))
    {
      return false;
    }
  }

  return true;
}

// Specialized validation functions
bool isValidEGN(const String &egn)
{
  if (egn.length() != 10 || !isAllDigits(egn))
    return false;

  // Проверка на датата
  // String yearStr = egn.substr(0, 2);
  String monthStr = egn.substr(2, 2);
  String dayStr = egn.substr(4, 2);

  // int year = stringToInt(yearStr);
  int month = stringToInt(monthStr);
  int day = stringToInt(dayStr);

  // Основна проверка на месец и ден
  if (month < 1 || month > 12 || day < 1 || day > 31)
  {
    // Проверка за месеци > 12 (19 век или 21 век)
    if (month >= 21 && month <= 32)
    {
      month -= 20; // 19 век
    }
    else if (month >= 41 && month <= 52)
    {
      month -= 40; // 21 век
    }
    else
    {
      return false;
    }

    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
      return false;
    }
  }

  return true;
}

bool isValidFacultyNumber(const String &facNum)
{
  // Стар формат: 5 цифри
  if (facNum.length() == 5 && isAllDigits(facNum))
  {
    return true;
  }

  // Нов формат: 0XX0400123
  if (facNum.length() == 10 && facNum[0] == '0' &&
      isAllDigits(facNum.substr(1, 2)) && facNum[3] == '0' &&
      facNum.substr(4, 3) == String("400") && isAllDigits(facNum.substr(7, 3)))
  {
    return true;
  }

  return false;
}

// Data type determination
DataType determineDataType(const String &value)
{
  if (value.empty())
    return DataType::TEXT;

  // Проверка за текст в кавички
  if ((value.front() == '"' && value.back() == '"') ||
      (value.front() == '\'' && value.back() == '\''))
  {
    return DataType::TEXT;
  }

  // Проверка за ЕГН (10 цифри)
  if (value.length() == 10 && isAllDigits(value))
  {
    if (isValidEGN(value))
      return DataType::EGN;
  }

  // Проверка за факултетен номер
  if (isValidFacultyNumber(value))
  {
    return DataType::FACULTY_NUMBER;
  }

  // Проверка за валута (число + 3 буквени символа)
  if (value.length() > 3)
  {
    String numPart = value.substr(0, value.length() - 3);
    String currPart = value.substr(value.length() - 3);

    if (isNumber(numPart) && isAllAlpha(currPart))
    {
      return DataType::CURRENCY;
    }
  }

  // Проверка за число
  if (isNumber(value))
  {
    return DataType::NUMBER;
  }

  return DataType::TEXT;
}