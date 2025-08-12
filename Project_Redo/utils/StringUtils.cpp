//=== src/utils/StringUtils.cpp ===
#include "StringUtils.h"
#include <iostream>

std::vector<std::string> StringUtils::split(const std::string &str, char delimiter)
{
  std::vector<std::string> result;
  std::string current;
  bool inQuotes = false;
  char quoteChar = '\0';

  for (size_t i = 0; i < str.length(); ++i)
  {
    char c = str[i];

    if (!inQuotes && (c == '"' || c == '\''))
    {
      inQuotes = true;
      quoteChar = c;
      current += c;
    }
    else if (inQuotes && c == quoteChar)
    {
      inQuotes = false;
      current += c;
    }
    else if (!inQuotes && c == delimiter)
    {
      result.push_back(current);
      current.clear();
    }
    else
    {
      current += c;
    }
  }

  if (!current.empty())
  {
    result.push_back(current);
  }

  return result;
}

std::string StringUtils::trim(const std::string &str)
{
  size_t start = 0;
  size_t end = str.length();

  while (start < end && (str[start] == ' ' || str[start] == '\t'))
  {
    ++start;
  }

  while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
  {
    --end;
  }

  return str.substr(start, end - start);
}

std::string StringUtils::toLowerCase(const std::string &str)
{
  std::string result = str;
  for (size_t i = 0; i < result.length(); ++i)
  {
    if (result[i] >= 'A' && result[i] <= 'Z')
    {
      result[i] = result[i] + 32;
    }
  }
  return result;
}

bool StringUtils::isQuoted(const std::string &str)
{
  if (str.length() < 2)
    return false;
  char first = str[0];
  char last = str[str.length() - 1];
  return (first == '"' && last == '"') || (first == '\'' && last == '\'');
}

std::string StringUtils::removeQuotes(const std::string &str)
{
  if (isQuoted(str))
  {
    return str.substr(1, str.length() - 2);
  }
  return str;
}

bool StringUtils::isNumber(const std::string &str)
{
  if (str.empty())
    return false;

  size_t start = 0;
  if (str[0] == '-' || str[0] == '+')
    start = 1;
  if (start >= str.length())
    return false;

  bool hasDot = false;
  for (size_t i = start; i < str.length(); ++i)
  {
    if (str[i] == '.')
    {
      if (hasDot)
        return false;
      hasDot = true;
    }
    else if (str[i] < '0' || str[i] > '9')
    {
      return false;
    }
  }
  return true;
}

std::string StringUtils::toString(double value)
{
  std::string result;

  // Handle negative numbers
  if (value < 0)
  {
    result += '-';
    value = -value;
  }

  // Convert integer part
  long long intPart = (long long)value;
  if (intPart == 0)
  {
    result += '0';
  }
  else
  {
    std::string intStr;
    while (intPart > 0)
    {
      intStr = char('0' + (intPart % 10)) + intStr;
      intPart /= 10;
    }
    result += intStr;
  }

  // Convert decimal part
  double fracPart = value - (long long)value;
  if (fracPart > 0.0001)
  { // Only show decimals if significant
    result += '.';
    for (int i = 0; i < 6 && fracPart > 0.0001; ++i)
    {
      fracPart *= 10;
      int digit = (int)fracPart;
      result += char('0' + digit);
      fracPart -= digit;
    }
  }

  return result;
}