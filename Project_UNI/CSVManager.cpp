//=== src/csv/CSVManager.cpp ===
#include "CSVManager.h"

CSVManager::CSVManager(char delimiter) : parser(delimiter), writer(delimiter) {}

Table CSVManager::loadTable(const std::string &filename)
{
  return parser.parse(filename);
}

void CSVManager::saveTable(const Table &table, const std::string &filename)
{
  writer.write(table, filename);
}

void CSVManager::setDelimiter(char delimiter)
{
  parser.setDelimiter(delimiter);
  writer.setDelimiter(delimiter);
}

char CSVManager::getDelimiter() const
{
  return parser.getDelimiter();
}
