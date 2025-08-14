//=== src/command/SortCommand.h ===
#pragma once

#include "Command.h"
#include "Table.h"

class SortCommand : public Command
{
private:
  Table *table;
  size_t columnIndex;
  bool ascending;
  std::vector<Row> originalRows;

public:
  SortCommand(Table *t, size_t colIndex, bool asc)
      : table(t), columnIndex(colIndex), ascending(asc) {}

  void execute() override;
  void undo() override;
  Command *clone() const override;
};
