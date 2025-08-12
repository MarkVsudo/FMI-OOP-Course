//=== src/command/AddColumnCommand.h ===
#ifndef ADDCOLUMNCOMMAND_H
#define ADDCOLUMNCOMMAND_H

#include "Command.h"
#include "../core/Table.h"

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

#endif