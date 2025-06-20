#include "column.h"

Column::Column() : name_(""), type_(DataType::TEXT) {}
Column::Column(const String &name) : name_(name), type_(DataType::TEXT) {}

const String &Column::getName() const { return name_; }
void Column::setName(const String &name) { name_ = name; }

DataType Column::getType() const { return type_; }
void Column::setType(DataType type) { type_ = type; }

size_t Column::size() const { return cells_.size(); }

const Cell &Column::getCell(size_t index) const
{
  if (index >= cells_.size())
  {
    throw std::out_of_range("Cell index out of range");
  }
  return cells_[index];
}

void Column::setCell(size_t index, const Cell &cell)
{
  while (index >= cells_.size())
  {
    cells_.pushBack(Cell());
  }
  cells_[index] = cell;
}

void Column::addCell(const Cell &cell)
{
  cells_.pushBack(cell);
}

void Column::removeCell(size_t index)
{
  if (index < cells_.size())
  {
    cells_.erase(index);
  }
}

Cell Column::getMinValue() const
{
  if (cells_.empty())
    return Cell();

  Cell min = cells_[0];
  for (size_t i = 1; i < cells_.size(); ++i)
  {
    if (cells_[i] < min)
    {
      min = cells_[i];
    }
  }
  return min;
}

Cell Column::getMaxValue() const
{
  if (cells_.empty())
    return Cell();

  Cell max = cells_[0];
  for (size_t i = 1; i < cells_.size(); ++i)
  {
    if (cells_[i] > max)
    {
      max = cells_[i];
    }
  }
  return max;
}

Cell Column::getMostFrequentValue() const
{
  if (cells_.empty())
    return Cell();

  // Simple frequency counting without std::map
  Vector<Cell> uniqueCells;
  Vector<int> frequencies;

  for (size_t i = 0; i < cells_.size(); ++i)
  {
    bool found = false;
    for (size_t j = 0; j < uniqueCells.size(); ++j)
    {
      if (uniqueCells[j] == cells_[i])
      {
        frequencies[j]++;
        found = true;
        break;
      }
    }
    if (!found)
    {
      uniqueCells.pushBack(cells_[i]);
      frequencies.pushBack(1);
    }
  }

  Cell mostFrequent = uniqueCells[0];
  int maxFreq = frequencies[0];

  for (size_t i = 1; i < uniqueCells.size(); ++i)
  {
    if (frequencies[i] > maxFreq ||
        (frequencies[i] == maxFreq && uniqueCells[i] < mostFrequent))
    {
      mostFrequent = uniqueCells[i];
      maxFreq = frequencies[i];
    }
  }

  return mostFrequent;
}
