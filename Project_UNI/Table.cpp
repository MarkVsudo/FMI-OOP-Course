//=== src/core/Table.cpp (UPDATED) ===
#include "Table.h"
#include "Exception.h"
#include "StringUtils.h"
#include "NumberType.h"
#include <iostream>

Table::Table() : hasHeaders(false), isModified(false) {}

Table::~Table()
{
  // Cleanup is handled automatically by std::vector destructors
}

// Rest of Table implementation stays the same...
void Table::addColumn(const Column &column)
{
  columns.push_back(column);

  // Add empty cells to existing rows
  for (Row &row : rows)
  {
    row.addCell(Cell(""));
  }
  setModified(true);
}

void Table::removeColumn(size_t index)
{
  if (index >= columns.size())
  {
    throw InvalidColumnException("Column index out of range");
  }

  columns.erase(columns.begin() + index);

  // Remove cells from all rows
  for (Row &row : rows)
  {
    if (index < row.size())
    {
      row.removeCell(index);
    }
  }
  setModified(true);
}

void Table::removeColumn(const std::string &name)
{
  size_t index = getColumnIndex(name);
  removeColumn(index);
}

size_t Table::getColumnIndex(const std::string &name) const
{
  for (size_t i = 0; i < columns.size(); ++i)
  {
    if (columns[i].getName() == name)
    {
      return i;
    }
  }
  throw InvalidColumnException("Column not found: " + name);
}

Column &Table::getColumn(size_t index)
{
  if (index >= columns.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  return columns[index];
}

const Column &Table::getColumn(size_t index) const
{
  if (index >= columns.size())
  {
    throw InvalidColumnException("Column index out of range");
  }
  return columns[index];
}

size_t Table::getColumnCount() const
{
  return columns.size();
}

void Table::reorderColumns(const std::vector<size_t> &newOrder)
{
  if (newOrder.size() != columns.size())
  {
    throw InvalidColumnException("Invalid permutation size");
  }

  // Check if permutation is valid
  std::vector<bool> used(columns.size(), false);
  for (size_t index : newOrder)
  {
    if (index >= columns.size() || used[index])
    {
      throw InvalidColumnException("Invalid permutation");
    }
    used[index] = true;
  }

  // Reorder columns
  std::vector<Column> newColumns;
  for (size_t index : newOrder)
  {
    newColumns.push_back(columns[index]);
  }
  columns = newColumns;

  // Reorder cells in all rows
  for (Row &row : rows)
  {
    std::vector<Cell> newCells;
    for (size_t index : newOrder)
    {
      if (index < row.size())
      {
        newCells.push_back(row.getCell(index));
      }
    }

    row.clear();
    for (const Cell &cell : newCells)
    {
      row.addCell(cell);
    }
  }
  setModified(true);
}

void Table::duplicateColumn(size_t index)
{
  if (index >= columns.size())
  {
    throw InvalidColumnException("Column index out of range");
  }

  Column originalCol = columns[index];
  std::string newName = generateUniqueColumnName(originalCol.getName());
  Column newColumn(newName, originalCol.getType());

  columns.insert(columns.begin() + index + 1, newColumn);

  // Duplicate cells in all rows
  for (Row &row : rows)
  {
    if (index < row.size())
    {
      Cell duplicatedCell = row.getCell(index);
      row.insertCell(index + 1, duplicatedCell);
    }
    else
    {
      row.insertCell(index + 1, Cell(""));
    }
  }
  setModified(true);
}

void Table::addRow(const Row &row)
{
  rows.push_back(row);
  setModified(true);
}

void Table::removeRow(size_t index)
{
  if (index >= rows.size())
  {
    throw InvalidColumnException("Row index out of range");
  }
  rows.erase(rows.begin() + index);
  setModified(true);
}

Row &Table::getRow(size_t index)
{
  if (index >= rows.size())
  {
    throw InvalidColumnException("Row index out of range");
  }
  return rows[index];
}

const Row &Table::getRow(size_t index) const
{
  if (index >= rows.size())
  {
    throw InvalidColumnException("Row index out of range");
  }
  return rows[index];
}

size_t Table::getRowCount() const
{
  return rows.size();
}

Cell &Table::getCell(size_t row, size_t col)
{
  if (row >= rows.size())
  {
    throw InvalidColumnException("Row index out of range");
  }
  return rows[row].getCell(col);
}

const Cell &Table::getCell(size_t row, size_t col) const
{
  if (row >= rows.size())
  {
    throw InvalidColumnException("Row index out of range");
  }
  return rows[row].getCell(col);
}

void Table::setCell(size_t row, size_t col, const std::string &value)
{
  if (row >= rows.size())
  {
    throw InvalidColumnException("Row index out of range");
  }
  rows[row].setCell(col, value);
  setModified(true);
}

void Table::sort(size_t columnIndex, bool ascending)
{
  if (columnIndex >= columns.size())
  {
    throw InvalidColumnException("Column index out of range");
  }

  // Simple bubble sort implementation
  for (size_t i = 0; i < rows.size(); ++i)
  {
    for (size_t j = 0; j < rows.size() - 1 - i; ++j)
    {
      const Cell &cell1 = rows[j].getCell(columnIndex);
      const Cell &cell2 = rows[j + 1].getCell(columnIndex);

      int cmp = cell1.compare(cell2);
      bool shouldSwap = ascending ? (cmp > 0) : (cmp < 0);

      if (shouldSwap)
      {
        Row temp = rows[j];
        rows[j] = rows[j + 1];
        rows[j + 1] = temp;
      }
    }
  }
  setModified(true);
}

void Table::sort(const std::string &columnName, bool ascending)
{
  size_t index = getColumnIndex(columnName);
  sort(index, ascending);
}

void Table::filter(size_t columnIndex, const std::string &operation, const std::string &value)
{
  if (columnIndex >= columns.size())
  {
    throw InvalidColumnException("Column index out of range");
  }

  Cell filterValue(value);
  std::vector<Row> filteredRows;

  for (const Row &row : rows)
  {
    const Cell &cell = row.getCell(columnIndex);
    bool keep = false;

    if (operation == "==")
    {
      keep = (cell == filterValue);
    }
    else if (operation == "!=")
    {
      keep = (cell != filterValue);
    }
    else if (operation == "<")
    {
      keep = (cell < filterValue);
    }
    else if (operation == "<=")
    {
      keep = (cell <= filterValue);
    }
    else if (operation == ">")
    {
      keep = (cell > filterValue);
    }
    else if (operation == ">=")
    {
      keep = (cell >= filterValue);
    }

    if (keep)
    {
      filteredRows.push_back(row);
    }
  }

  rows = filteredRows;
  setModified(true);
}

void Table::removeDuplicates()
{
  std::vector<Row> uniqueRows;

  for (const Row &row : rows)
  {
    bool isDuplicate = false;
    for (const Row &uniqueRow : uniqueRows)
    {
      if (row == uniqueRow)
      {
        isDuplicate = true;
        break;
      }
    }

    if (!isDuplicate)
    {
      uniqueRows.push_back(row);
    }
  }

  rows = uniqueRows;
  setModified(true);
}

void Table::addRowCopy(size_t sourceRow)
{
  if (sourceRow >= rows.size())
  {
    throw InvalidColumnException("Row index out of range");
  }

  rows.push_back(rows[sourceRow]);
  setModified(true);
}

void Table::addRowMin()
{
  if (rows.empty() || columns.empty())
  {
    return;
  }

  Row minRow;

  for (size_t col = 0; col < columns.size(); ++col)
  {
    std::string minValue = rows[0].getCell(col).getValue();

    for (size_t row = 1; row < rows.size(); ++row)
    {
      const Cell &cell = rows[row].getCell(col);
      if (cell < Cell(minValue))
      {
        minValue = cell.getValue();
      }
    }

    minRow.addCell(Cell(minValue));
  }

  addRow(minRow);
}

void Table::addRowMax()
{
  if (rows.empty() || columns.empty())
  {
    return;
  }

  Row maxRow;

  for (size_t col = 0; col < columns.size(); ++col)
  {
    std::string maxValue = rows[0].getCell(col).getValue();

    for (size_t row = 1; row < rows.size(); ++row)
    {
      const Cell &cell = rows[row].getCell(col);
      if (cell > Cell(maxValue))
      {
        maxValue = cell.getValue();
      }
    }

    maxRow.addCell(Cell(maxValue));
  }

  addRow(maxRow);
}

void Table::addRowMode()
{
  if (rows.empty() || columns.empty())
  {
    return;
  }

  Row modeRow;

  for (size_t col = 0; col < columns.size(); ++col)
  {
    std::vector<std::pair<std::string, int>> valueCounts;

    // Count occurrences of each value
    for (size_t row = 0; row < rows.size(); ++row)
    {
      std::string value = rows[row].getCell(col).getValue();

      bool found = false;
      for (auto &pair : valueCounts)
      {
        if (pair.first == value)
        {
          pair.second++;
          found = true;
          break;
        }
      }

      if (!found)
      {
        valueCounts.push_back(std::make_pair(value, 1));
      }
    }

    // Find mode (most frequent value, smallest if tie)
    std::string modeValue = valueCounts[0].first;
    int maxCount = valueCounts[0].second;

    for (const auto &pair : valueCounts)
    {
      if (pair.second > maxCount ||
          (pair.second == maxCount && pair.first < modeValue))
      {
        modeValue = pair.first;
        maxCount = pair.second;
      }
    }

    modeRow.addCell(Cell(modeValue));
  }

  addRow(modeRow);
}

void Table::clear()
{
  columns.clear();
  rows.clear();
  hasHeaders = false;
  isModified = false;
}

bool Table::empty() const
{
  return rows.empty() && columns.empty();
}

void Table::detectColumnTypes()
{
  for (size_t col = 0; col < columns.size(); ++col)
  {
    if (rows.empty())
    {
      columns[col].setType(DataTypeEnum::TEXT);
      continue;
    }

    // Use first non-empty cell to determine type
    DataTypeEnum detectedType = DataTypeEnum::TEXT;
    for (size_t row = 0; row < rows.size(); ++row)
    {
      const Cell &cell = rows[row].getCell(col);
      if (!cell.getValue().empty())
      {
        detectedType = cell.getType();
        break;
      }
    }

    columns[col].setType(detectedType);
  }
}

std::string Table::generateUniqueColumnName(const std::string &baseName) const
{
  std::string newName = baseName;
  int counter = 1;

  while (true)
  {
    bool exists = false;
    for (const Column &col : columns)
    {
      if (col.getName() == newName)
      {
        exists = true;
        break;
      }
    }

    if (!exists)
    {
      return newName;
    }

    newName = baseName + StringUtils::toString(counter);
    counter++;
  }
}

bool Table::rowExists(const Row &row) const
{
  for (const Row &existingRow : rows)
  {
    if (existingRow == row)
    {
      return true;
    }
  }
  return false;
}