#pragma once

#include "myString.h"
#include "dataType.h"

// String conversion functions
double stringToDouble(const String &str);
int stringToInt(const String &str);
String intToString(int value);

// Character classification functions
bool isDigitChar(char c);
bool isAlphaChar(char c);
bool isSpaceChar(char c);

// String validation functions
bool isAllDigits(const String &str);
bool isAllAlpha(const String &str);
bool isNumber(const String &str);

// Specialized validation functions
bool isValidEGN(const String &egn);
bool isValidFacultyNumber(const String &facNum);

// Data type determination
DataType determineDataType(const String &value);
