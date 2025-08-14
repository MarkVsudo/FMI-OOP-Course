//=== src/csv/CSVWriter.cpp ===
#include "CSVWriter.h"
#include "Exception.h"
#include <fstream>

void CSVWriter::write(const Table &table, const std::string &filename)
{
  std::ofstream file(filename.c_str());
  if (!file.is_open())
  {
    throw FileException("Cannot create file: " + filename);
  }

  // Write headers if table has them
  if (table.getHasHeaders())
  {
    for (size_t i = 0; i < table.getColumnCount(); ++i)
    {
      if (i > 0)
        file << delimiter;
      file << escapeValue(table.getColumn(i).getName());
    }
    file << '\n';
  }

  // Write data rows
  for (size_t row = 0; row < table.getRowCount(); ++row)
  {
    const Row &tableRow = table.getRow(row);
    for (size_t col = 0; col < table.getColumnCount() && col < tableRow.size(); ++col)
    {
      if (col > 0)
        file << delimiter;
      file << escapeValue(tableRow.getCell(col).getValue());
    }
    file << '\n';
  }

  file.close();
}

std::string CSVWriter::escapeValue(const std::string &value)
{
  // Simple escaping: if value contains delimiter or quotes, wrap in quotes
  bool needsQuotes = false;

  for (char c : value)
  {
    if (c == delimiter || c == '"' || c == '\n' || c == '\r')
    {
      needsQuotes = true;
      break;
    }
  }

  if (!needsQuotes)
  {
    return value;
  }

  std::string result = "\"";
  for (char c : value)
  {
    if (c == '"')
    {
      result += "\"\""; // Escape quotes by doubling
    }
    else
    {
      result += c;
    }
  }
  result += "\"";

  return result;
}