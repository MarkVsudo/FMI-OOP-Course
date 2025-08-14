//=== src/utils/StringUtils.h ===
#pragma once

#include <string>
#include <vector>

class StringUtils
{
public:
  static std::vector<std::string> split(const std::string &str, char delimiter);
  static std::string trim(const std::string &str);
  static std::string toLowerCase(const std::string &str);
  static bool isQuoted(const std::string &str);
  static std::string removeQuotes(const std::string &str);
  static bool isNumber(const std::string &str);
  static std::string toString(double value);
};
