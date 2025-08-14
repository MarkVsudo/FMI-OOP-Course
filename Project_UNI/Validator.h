//=== src/utils/Validator.h ===
#pragma once

#include <string>

class Validator
{
public:
  static bool isValidEGN(const std::string &egn);
  static bool isValidFacultyNumber(const std::string &fn);
  static bool isValidCurrency(const std::string &currency);
  static bool isValidNumber(const std::string &number);
  static bool isValidDate(int year, int month, int day);

private:
  static bool isValidSpecialtyCode(const std::string &code);
};
