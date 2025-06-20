#include "column.h"

// Конструктор по подразбиране - създава колона без име с тип TEXT
Column::Column() : name_(""), type_(DataType::TEXT) {}
// Конструктор с име - създава колона с дадено име и тип TEXT по подразбиране
Column::Column(const String &name) : name_(name), type_(DataType::TEXT) {}

// Getter-и и Setter-и
const String &Column::getName() const { return name_; }
void Column::setName(const String &name) { name_ = name; }

DataType Column::getType() const { return type_; }
void Column::setType(DataType type) { type_ = type; }

// Връща броя клетки в колоната
size_t Column::size() const { return cells_.size(); }

// Връща клетка на дадена позиция (константна версия)
const Cell &Column::getCell(size_t index) const
{
  if (index >= cells_.size())
  {
    throw std::out_of_range("Cell index out of range");
  }
  return cells_[index];
}

// Задава клетка на дадена позиция
void Column::setCell(size_t index, const Cell &cell)
{
  // Ако индексът е извън границите, добавя празни клетки до достигане на позицията
  while (index >= cells_.size())
  {
    cells_.pushBack(Cell());
  }
  cells_[index] = cell;
}

// Добавя нова клетка в края на колоната
void Column::addCell(const Cell &cell)
{
  cells_.pushBack(cell);
}

// Премахва клетка на дадена позиция
void Column::removeCell(size_t index)
{
  if (index < cells_.size())
  {
    cells_.erase(index);
  }
}

// Намира клетката с минимална стойност в колоната
Cell Column::getMinValue() const
{
  if (cells_.empty())
    return Cell();

  // Започва с първата клетка като минимум
  Cell min = cells_[0];
  // Обхожда останалите клетки и намира най-малката
  for (size_t i = 1; i < cells_.size(); ++i)
  {
    if (cells_[i] < min)
    {
      min = cells_[i];
    }
  }
  return min;
}

// Намира клетката с максимална стойност в колоната
Cell Column::getMaxValue() const
{
  if (cells_.empty())
    return Cell();

  // Започва с първата клетка като максимум
  Cell max = cells_[0];
  // Обхожда останалите клетки и намира най-голямата
  for (size_t i = 1; i < cells_.size(); ++i)
  {
    if (cells_[i] > max)
    {
      max = cells_[i];
    }
  }
  return max;
}

// Намира най-често срещаната стойност в колоната
Cell Column::getMostFrequentValue() const
{
  if (cells_.empty())
    return Cell();

  MyArray<Cell> uniqueCells; // Масив за уникалните стойности
  MyArray<int> frequencies;  // Масив за честотата на всяка уникална стойност

  // Обхожда всички клетки и брои честотата
  for (size_t i = 0; i < cells_.size(); ++i)
  {
    bool found = false;
    // Проверява дали тази стойност вече е срещана
    for (size_t j = 0; j < uniqueCells.size(); ++j)
    {
      if (uniqueCells[j] == cells_[i])
      {
        frequencies[j]++;
        found = true;
        break;
      }
    }
    // Ако е нова стойност, добавя я в масивите
    if (!found)
    {
      uniqueCells.pushBack(cells_[i]);
      frequencies.pushBack(1);
    }
  }

  // Започва с първата уникална стойност като най-честа
  Cell mostFrequent = uniqueCells[0];
  int maxFreq = frequencies[0];

  // Търси стойността с най-висока честота
  for (size_t i = 1; i < uniqueCells.size(); ++i)
  {
    // Ако тази стойност е по-честа ИЛИ има същата честота но е по-малка лексикографски
    if (frequencies[i] > maxFreq ||
        (frequencies[i] == maxFreq && uniqueCells[i] < mostFrequent))
    {
      mostFrequent = uniqueCells[i];
      maxFreq = frequencies[i];
    }
  }

  return mostFrequent;
}
