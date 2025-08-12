//=== src/csv/CSVFormatter.cpp ===
#include "CSVFormatter.h"
#include <iostream>

void CSVFormatter::printTable(const Table &table)
{
  if (table.empty())
  {
    std::cout << "Table is empty.\n";
    return;
  }

  std::vector<size_t> widths = calculateColumnWidths(table);

  // Print headers if available
  if (table.getHasHeaders())
  {
    std::vector<std::string> headers;
    for (size_t i = 0; i < table.getColumnCount(); ++i)
    {
      headers.push_back(table.getColumn(i).getName());
    }

    printSeparator(widths);
    printRow(headers, widths);
    printSeparator(widths);
  }

  // Print data rows
  for (size_t row = 0; row < table.getRowCount(); ++row)
  {
    std::vector<std::string> values;
    const Row &tableRow = table.getRow(row);

    for (size_t col = 0; col < table.getColumnCount(); ++col)
    {
      if (col < tableRow.size())
      {
        values.push_back(tableRow.getCell(col).getValue());
      }
      else
      {
        values.push_back("");
      }
    }

    printRow(values, widths);
  }

  printSeparator(widths);
}

std::vector<size_t> CSVFormatter::calculateColumnWidths(const Table &table)
{
  std::vector<size_t> widths(table.getColumnCount(), 0);

  // Check header widths
  if (table.getHasHeaders())
  {
    for (size_t i = 0; i < table.getColumnCount(); ++i)
    {
      size_t headerLen = table.getColumn(i).getName().length();
      if (headerLen > widths[i])
      {
        widths[i] = headerLen;
      }
    }
  }

  // Check data widths
  for (size_t row = 0; row < table.getRowCount(); ++row)
  {
    const Row &tableRow = table.getRow(row);
    for (size_t col = 0; col < table.getColumnCount() && col < tableRow.size(); ++col)
    {
      size_t cellLen = tableRow.getCell(col).getValue().length();
      if (cellLen > widths[col])
      {
        widths[col] = cellLen;
      }
    }
  }

  // Ensure minimum width of 3 characters
  for (size_t &width : widths)
  {
    if (width < 3)
      width = 3;
  }

  return widths;
}

void CSVFormatter::printSeparator(const std::vector<size_t> &widths)
{
  std::cout << "+";
  for (size_t width : widths)
  {
    for (size_t i = 0; i < width + 2; ++i)
    {
      std::cout << "-";
    }
    std::cout << "+";
  }
  std::cout << "\n";
}

void CSVFormatter::printRow(const std::vector<std::string> &values, const std::vector<size_t> &widths)
{
  std::cout << "|";
  for (size_t i = 0; i < values.size() && i < widths.size(); ++i)
  {
    std::cout << " " << padString(values[i], widths[i]) << " |";
  }
  std::cout << "\n";
}

std::string CSVFormatter::padString(const std::string &str, size_t width)
{
  if (str.length() >= width)
  {
    return str;
  }

  std::string result = str;
  while (result.length() < width)
  {
    result += " ";
  }
  return result;
}