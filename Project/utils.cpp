#include "utils.h"
#include <cstdlib>
#include <iostream>

// Функции за конвертиране на низове
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

// Функции за класификация на символи
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
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// ункции за валидация на низове
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

// Валидиращи фунцкии
bool isValidEGN(const String &egn)
{
  if (egn.length() != 10 || !isAllDigits(egn))
    return false;

  int month = stringToInt(egn.substr(2, 2));
  int day = stringToInt(egn.substr(4, 2));

  // Нормализиране на месеца според века
  if (month >= 21 && month <= 32)
    month -= 20;
  else if (month >= 41 && month <= 52)
    month -= 40;

  if (month < 1 || month > 12 || day < 1 || day > 31)
    return false;

  return true;
}

bool isValidFacultyNumber(const String &facNum)
{
  // Стар формат: 5 цифри
  if (facNum.length() == 5 && isAllDigits(facNum))
  {
    return true;
  }

  // Нов формат: 0XX0Y00123
  if (facNum.length() == 10 &&
      facNum[0] == '0' &&                    // Започва с '0'
      isAllDigits(facNum.substr(1, 2)) &&    // Позиции 1-2: две цифри
      facNum[3] == '0' &&                    // Позиция 3: '0'
      isDigitChar(facNum[4]) &&              // Позиция 4: произволна цифра
      facNum.substr(5, 2) == String("00") && // Позиции 5-6: "00"
      isAllDigits(facNum.substr(7, 3)))      // Позиции 7-9: три цифри
  {
    return true;
  }

  return false;
}
// Определяне на типа на данните
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

  // По подразбиране се счита за текст
  return DataType::TEXT;
}