//=== src/csv/CSVParser.h ===
#ifndef CSVPARSER_H
#define CSVPARSER_H

#include "../core/Table.h"
#include <string>

class CSVParser
{
private:
  char delimiter;

public:
  CSVParser(char delim = ',') : delimiter(delim) {}

  Table parse(const std::string &filename);
  void setDelimiter(char delim) { delimiter = delim; }
  char getDelimiter() const { return delimiter; }

private:
  std::vector<std::string> parseLine(const std::string &line);
  bool isHeaderRow(const std::vector<std::string> &firstRow, const std::vector<std::string> &secondRow);
};

#endif
