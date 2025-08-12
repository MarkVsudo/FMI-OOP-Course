//=== src/command/RemoveRowCommand.h ===
#ifndef REMOVEROWCOMMAND_H
#define REMOVEROWCOMMAND_H

#include "Command.h"
#include "../core/Table.h"

class RemoveRowCommand : public Command
{
private:
  Table *table;
  size_t rowIndex;
  Row removedRow;

public:
  RemoveRowCommand(Table *t, size_t index) : table(t), rowIndex(index) {}

  void execute() override;
  void undo() override;
  Command *clone() const override;
};

#endif