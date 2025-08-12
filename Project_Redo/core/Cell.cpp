//=== src/core/Cell.cpp ===
#include "Cell.h"
#include "../datatypes/TextType.h"

Cell::Cell()
{
  data = new TextType("");
}

Cell::Cell(const std::string &value)
{
  data = DataType::detectType(value);
  data->setValue(value);
}

Cell::Cell(const Cell &other)
{
  data = other.data->clone();
}

Cell &Cell::operator=(const Cell &other)
{
  if (this != &other)
  {
    delete data;
    data = other.data->clone();
  }
  return *this;
}

Cell::~Cell()
{
  delete data;
}

bool Cell::setValue(const std::string &value)
{
  // Try to set value with current type first
  if (data->isValid(value))
  {
    return data->setValue(value);
  }

  // If that fails, detect new type
  delete data;
  data = DataType::detectType(value);
  return data->setValue(value);
}

std::string Cell::getValue() const
{
  return data->getValue();
}

DataType *Cell::getDataType() const
{
  return data;
}

DataTypeEnum Cell::getType() const
{
  return data->getType();
}

int Cell::compare(const Cell &other) const
{
  return data->compare(*other.data);
}

bool Cell::operator==(const Cell &other) const
{
  return compare(other) == 0;
}

bool Cell::operator!=(const Cell &other) const
{
  return compare(other) != 0;
}

bool Cell::operator<(const Cell &other) const
{
  return compare(other) < 0;
}

bool Cell::operator<=(const Cell &other) const
{
  return compare(other) <= 0;
}

bool Cell::operator>(const Cell &other) const
{
  return compare(other) > 0;
}

bool Cell::operator>=(const Cell &other) const
{
  return compare(other) >= 0;
}
