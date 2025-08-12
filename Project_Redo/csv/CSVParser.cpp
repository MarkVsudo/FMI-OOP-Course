//=== src/csv/CSVParser.cpp ===
#include "CSVParser.h"
#include "../utils/StringUtils.h"
#include "../utils/Exception.h"
#include <fstream>
#include <iostream>

Table CSVParser::parse(const std::string &filename)
{
  std::ifstream file(filename.c_str());
  if (!file.is_open())
  {
    throw FileException("Cannot open file: " + filename);
  }

  Table table;
  table.setFilename(filename);

  std::string line;
  std::vector<std::vector<std::string>> allRows;

  // Read all lines
  while (std::getline(file, line))
  {
    if (!line.empty())
    {
      allRows.push_back(parseLine(line));
    }
  }
  file.close();

  if (allRows.empty())
  {
    return table;
  }

  // Determine if first row is header
  bool hasHeaders = false;
  if (allRows.size() > 1)
  {
    hasHeaders = isHeaderRow(allRows[0], allRows[1]);
  }
  table.setHasHeaders(hasHeaders);

  // Set up columns
  size_t numCols = allRows[0].size();
  for (size_t i = 0; i < numCols; ++i)
  {
    std::string columnName;
    if (hasHeaders)
    {
      columnName = allRows[0][i];
    }
    else
    {
      columnName = "Column" + StringUtils::toString(i + 1);
    }
    table.addColumn(Column(columnName));
  }

  // Add data rows
  size_t startRow = hasHeaders ? 1 : 0;
  for (size_t i = startRow; i < allRows.size(); ++i)
  {
    Row row(allRows[i]);

    // Pad row with empty cells if necessary
    while (row.size() < numCols)
    {
      row.addCell(Cell(""));
    }

    // Truncate row if it has too many columns
    while (row.size() > numCols)
    {
      row.removeCell(row.size() - 1);
    }

    table.addRow(row);
  }

  table.setModified(false);
  return table;
}

std::vector<std::string> CSVParser::parseLine(const std::string &line)
{
  return StringUtils::split(line, delimiter);
}

bool CSVParser::isHeaderRow(const std::vector<std::string> &firstRow, const std::vector<std::string> &secondRow)
{
  // Simple heuristic: if first row contains quoted strings or non-numeric values
  // and second row contains more numeric-looking values, assume first is header

  int firstRowTextCount = 0;
  int secondRowTextCount = 0;

  for (const std::string &cell : firstRow)
  {
    if (StringUtils::isQuoted(cell) || !StringUtils::isNumber(StringUtils::trim(cell)))
    {
      firstRowTextCount++;
    }
  }

  for (const std::string &cell : secondRow)
  {
    if (StringUtils::isQuoted(cell) || !StringUtils::isNumber(StringUtils::trim(cell)))
    {
      secondRowTextCount++;
    }
  }

  return firstRowTextCount > secondRowTextCount;
}