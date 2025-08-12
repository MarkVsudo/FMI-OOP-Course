//=== src/csv/CSVFormatter.h ===
#ifndef CSVFORMATTER_H
#define CSVFORMATTER_H

#include "../core/Table.h"
#include <string>
#include <vector>

class CSVFormatter
{
public:
  static void printTable(const Table &table);

private:
  static std::vector<size_t> calculateColumnWidths(const Table &table);
  static void printSeparator(const std::vector<size_t> &widths);
  static void printRow(const std::vector<std::string> &values, const std::vector<size_t> &widths);
  static std::string padString(const std::string &str, size_t width);
};

#endif