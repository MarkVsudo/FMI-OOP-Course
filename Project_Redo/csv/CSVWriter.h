//=== src/csv/CSVWriter.h ===
#ifndef CSVWRITER_H
#define CSVWRITER_H

#include "../core/Table.h"
#include <string>

class CSVWriter
{
private:
  char delimiter;

public:
  CSVWriter(char delim = ',') : delimiter(delim) {}

  void write(const Table &table, const std::string &filename);
  void setDelimiter(char delim) { delimiter = delim; }
  char getDelimiter() const { return delimiter; }

private:
  std::string escapeValue(const std::string &value);
};

#endif