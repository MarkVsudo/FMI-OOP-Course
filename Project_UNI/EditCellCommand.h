//=== src/command/EditCellCommand.h ===
#pragma once

#include "Command.h"
#include "Table.h"

class EditCellCommand : public Command
{
private:
  Table *table;
  size_t row;
  size_t col;
  std::string newValue;
  std::string oldValue;

public:
  EditCellCommand(Table *t, size_t r, size_t c, const std::string &value)
      : table(t), row(r), col(c), newValue(value) {}

  void execute() override;
  void undo() override;
  Command *clone() const override;
};
