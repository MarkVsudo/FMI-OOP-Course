//=== src/command/AddRowCommand.h ===
#pragma once

#include "Command.h"
#include "Table.h"

class AddRowCommand : public Command
{
private:
  Table *table;
  Row row;
  size_t addedRowIndex;

public:
  AddRowCommand(Table *t, const Row &r) : table(t), row(r), addedRowIndex(0) {}

  void execute() override;
  void undo() override;
  Command *clone() const override;
};
