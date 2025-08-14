//=== src/command/AddColumnCommand.h ===
#pragma once

#include "Command.h"
#include "Table.h"

class AddColumnCommand : public Command
{
private:
  Table *table;
  Column column;
  size_t addedColumnIndex;

public:
  AddColumnCommand(Table *t, const Column &col) : table(t), column(col), addedColumnIndex(0) {}

  void execute() override;
  void undo() override;
  Command *clone() const override;
};
