//=== src/core/Row.h ===
#pragma once

#include "Cell.h"
#include <vector>

class Row
{
private:
  std::vector<Cell> cells;

public:
  Row() {}
  Row(const std::vector<std::string> &values);
  Row(const Row &other);
  Row &operator=(const Row &other);

  void addCell(const Cell &cell);
  void addCell(const std::string &value);

  Cell &getCell(size_t index);
  const Cell &getCell(size_t index) const;

  void setCell(size_t index, const Cell &cell);
  void setCell(size_t index, const std::string &value);

  void removeCell(size_t index);
  void insertCell(size_t index, const Cell &cell);

  size_t size() const;
  bool empty() const;
  void clear();

  bool operator==(const Row &other) const;
  bool operator!=(const Row &other) const;

  // Iterator support
  std::vector<Cell>::iterator begin() { return cells.begin(); }
  std::vector<Cell>::iterator end() { return cells.end(); }
  std::vector<Cell>::const_iterator begin() const { return cells.begin(); }
  std::vector<Cell>::const_iterator end() const { return cells.end(); }
};
