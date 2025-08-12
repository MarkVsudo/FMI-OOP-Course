
//=== src/core/Table.h ===
#ifndef TABLE_H
#define TABLE_H

#include "Row.h"
#include "Column.h"
#include <vector>
#include <string>

class Table
{
private:
  std::vector<Column> columns;
  std::vector<Row> rows;
  bool hasHeaders;
  std::string filename;
  bool isModified;

public:
  Table();
  ~Table();

  // File operations
  void setFilename(const std::string &name) { filename = name; }
  std::string getFilename() const { return filename; }
  void setModified(bool modified) { isModified = modified; }
  bool getModified() const { return isModified; }

  // Column operations
  void addColumn(const Column &column);
  void removeColumn(size_t index);
  void removeColumn(const std::string &name);
  size_t getColumnIndex(const std::string &name) const;
  Column &getColumn(size_t index);
  const Column &getColumn(size_t index) const;
  size_t getColumnCount() const;
  void reorderColumns(const std::vector<size_t> &newOrder);
  void duplicateColumn(size_t index);

  // Row operations
  void addRow(const Row &row);
  void removeRow(size_t index);
  Row &getRow(size_t index);
  const Row &getRow(size_t index) const;
  size_t getRowCount() const;

  // Cell operations
  Cell &getCell(size_t row, size_t col);
  const Cell &getCell(size_t row, size_t col) const;
  void setCell(size_t row, size_t col, const std::string &value);

  // Headers
  void setHasHeaders(bool headers) { hasHeaders = headers; }
  bool getHasHeaders() const { return hasHeaders; }

  // Data operations
  void sort(size_t columnIndex, bool ascending = true);
  void sort(const std::string &columnName, bool ascending = true);
  void filter(size_t columnIndex, const std::string &operation, const std::string &value);
  void removeDuplicates();

  // Special row operations
  void addRowCopy(size_t sourceRow);
  void addRowMin();
  void addRowMax();
  void addRowMode();

  // Utility
  void clear();
  bool empty() const;

private:
  void detectColumnTypes();
  std::string generateUniqueColumnName(const std::string &baseName) const;
  bool rowExists(const Row &row) const;
};

#endif