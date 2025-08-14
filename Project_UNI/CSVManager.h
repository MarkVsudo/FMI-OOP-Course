//=== src/csv/CSVManager.h ===
#pragma once

#include "Table.h"
#include "CSVParser.h"
#include "CSVWriter.h"
#include <string>

class CSVManager
{
private:
  CSVParser parser;
  CSVWriter writer;

public:
  CSVManager(char delimiter = ',');

  Table loadTable(const std::string &filename);
  void saveTable(const Table &table, const std::string &filename);

  void setDelimiter(char delimiter);
  char getDelimiter() const;
};
