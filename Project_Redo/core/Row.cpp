//=== src/core/Row.cpp ===
#include "Row.h"
#include "../utils/Exception.h"

Row::Row(const std::vector<std::string> &values)
{
  for (const std::string &value : values)
  {
    cells.push_back(Cell(value));
  }
}

Row::Row(const Row &other) : cells(other.cells) {}

Row &Row::operator=(const Row &other)
{
  if (this != &other)
  {
    cells = other.cells;
  }
  return *this;
}

void Row::addCell(const Cell &cell)
{
  cells.push_back(cell);
}

void Row::addCell(const std::string &value)
{
  cells.push_back(Cell(value));
}

Cell &Row::getCell(size_t index)
{
  if (index >= cells.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  return cells[index];
}

const Cell &Row::getCell(size_t index) const
{
  if (index >= cells.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  return cells[index];
}

void Row::setCell(size_t index, const Cell &cell)
{
  if (index >= cells.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  cells[index] = cell;
}

void Row::setCell(size_t index, const std::string &value)
{
  if (index >= cells.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  cells[index].setValue(value);
}

void Row::removeCell(size_t index)
{
  if (index >= cells.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  cells.erase(cells.begin() + index);
}

void Row::insertCell(size_t index, const Cell &cell)
{
  if (index > cells.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  cells.insert(cells.begin() + index, cell);
}

size_t Row::size() const
{
  return cells.size();
}

bool Row::empty() const
{
  return cells.empty();
}

void Row::clear()
{
  cells.clear();
}

bool Row::operator==(const Row &other) const
{
  if (cells.size() != other.cells.size())
    return false;

  for (size_t i = 0; i < cells.size(); ++i)
  {
    if (cells[i] != other.cells[i])
      return false;
  }
  return true;
}

bool Row::operator!=(const Row &other) const
{
  return !(*this == other);
}
