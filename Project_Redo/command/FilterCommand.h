//=== src/command/FilterCommand.h ===
#ifndef FILTERCOMMAND_H
#define FILTERCOMMAND_H

#include "Command.h"
#include "../core/Table.h"

class FilterCommand : public Command
{
private:
  Table *table;
  size_t columnIndex;
  std::string operation;
  std::string value;
  std::vector<Row> originalRows;

public:
  FilterCommand(Table *t, size_t colIndex, const std::string &op, const std::string &val)
      : table(t), columnIndex(colIndex), operation(op), value(val) {}

  void execute() override;
  void undo() override;
  Command *clone() const override;
};

#endif