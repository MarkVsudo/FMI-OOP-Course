#pragma once

#include "myString.h"
#include "dataType.h"

// Фунцкции за конвертиране на низ
double stringToDouble(const String &str);
int stringToInt(const String &str);
String intToString(int value);

// Функции за определяне на типа символ
bool isDigitChar(char c);
bool isAlphaChar(char c);
bool isSpaceChar(char c);

// Функции за валидация на низ
bool isAllDigits(const String &str);
bool isAllAlpha(const String &str);
bool isNumber(const String &str);

// Функции за валидиране на други типове
bool isValidEGN(const String &egn);
bool isValidFacultyNumber(const String &facNum);

// Определяне на тип
DataType determineDataType(const String &value);
