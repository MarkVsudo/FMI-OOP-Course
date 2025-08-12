//=== src/datatypes/DataType.cpp ===
#include "DataType.h"
#include "TextType.h"
#include "NumberType.h"
#include "CurrencyType.h"
#include "EGNType.h"
#include "FacultyNumberType.h"
#include "../utils/StringUtils.h"

DataType *DataType::detectType(const std::string &val)
{
  std::string cleanVal = StringUtils::trim(val);

  // If quoted, always treat as text
  if (StringUtils::isQuoted(cleanVal))
  {
    return new TextType(cleanVal);
  }

  // Try EGN
  EGNType egn;
  if (egn.isValid(cleanVal))
  {
    return new EGNType(cleanVal);
  }

  // Try Faculty Number
  FacultyNumberType fn;
  if (fn.isValid(cleanVal))
  {
    return new FacultyNumberType(cleanVal);
  }

  // Try Currency
  CurrencyType curr;
  if (curr.isValid(cleanVal))
  {
    return new CurrencyType(cleanVal);
  }

  // Try Number
  NumberType num;
  if (num.isValid(cleanVal))
  {
    return new NumberType(cleanVal);
  }

  // Default to text
  return new TextType(cleanVal);
}