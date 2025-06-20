#include "cell.h"

Cell::Cell() : value_(""), type_(DataType::TEXT) {}
Cell::Cell(const String &value, DataType type) : value_(value), type_(type) {}

const String &Cell::getValue() const { return value_; }
DataType Cell::getType() const { return type_; }
void Cell::setValue(const String &value) { value_ = value; }
void Cell::setType(DataType type) { type_ = type; }

// Оператори за сравнение
bool Cell::operator==(const Cell &other) const
{
  if (type_ != other.type_)
    return false;
  return compareValues(other) == 0;
}

bool Cell::operator!=(const Cell &other) const { return !(*this == other); }
bool Cell::operator<(const Cell &other) const { return compareValues(other) < 0; }
bool Cell::operator<=(const Cell &other) const { return compareValues(other) <= 0; }
bool Cell::operator>(const Cell &other) const { return compareValues(other) > 0; }
bool Cell::operator>=(const Cell &other) const { return compareValues(other) >= 0; }

int Cell::compareValues(const Cell &other) const
{
  if (type_ != other.type_)
  {
    throw std::runtime_error("Cannot compare different data types");
  }

  switch (type_)
  {
  case DataType::NUMBER:
  {
    double val1 = stringToDouble(value_);
    double val2 = stringToDouble(other.value_);
    if (val1 < val2)
      return -1;
    if (val1 > val2)
      return 1;
    return 0;
  }
  case DataType::CURRENCY:
  {
    String numPart1 = value_.substr(0, value_.length() - 3);
    String numPart2 = other.value_.substr(0, other.value_.length() - 3);
    double val1 = stringToDouble(numPart1);
    double val2 = stringToDouble(numPart2);
    if (val1 < val2)
      return -1;
    if (val1 > val2)
      return 1;
    return 0;
  }
  case DataType::FACULTY_NUMBER:
    return compareFacultyNumbers(other);
  default:
    return value_.compare(other.value_);
  }
}

int Cell::compareFacultyNumbers(const Cell &other) const
{
  // Извличане на специалност от факултетен номер
  String spec1 = extractSpecialty(value_);
  String spec2 = extractSpecialty(other.value_);

  int specCompare = spec1.compare(spec2);
  if (specCompare != 0)
    return specCompare;

  // В рамките на една специалност - стари преди нови
  bool isOld1 = value_.length() == 5;
  bool isOld2 = other.value_.length() == 5;

  if (isOld1 && !isOld2)
    return -1;
  if (!isOld1 && isOld2)
    return 1;

  return value_.compare(other.value_);
}

String Cell::extractSpecialty(const String &facNum) const
{
  if (facNum.length() == 5)
  {
    return facNum.substr(0, 2);
  }
  else if (facNum.length() == 10)
  {
    return facNum.substr(1, 2);
  }
  return String("");
}
