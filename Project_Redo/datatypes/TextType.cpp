//=== src/datatypes/TextType.cpp ===
#include "TextType.h"
#include "../utils/StringUtils.h"

bool TextType::setValue(const std::string &val)
{
  value = StringUtils::removeQuotes(val);
  return true;
}

DataType *TextType::clone() const
{
  return new TextType(value);
}

int TextType::compare(const DataType &other) const
{
  if (other.getType() != DataTypeEnum::TEXT)
    return -1;

  const std::string &otherVal = other.getValue();
  if (value < otherVal)
    return -1;
  if (value > otherVal)
    return 1;
  return 0;
}

bool TextType::isValid(const std::string &val) const
{
  return true; // All strings are valid text
}