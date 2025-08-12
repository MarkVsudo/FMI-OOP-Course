//=== src/command/EditCellCommand.cpp ===
#include "EditCellCommand.h"

void EditCellCommand::execute()
{
  oldValue = table->getCell(row, col).getValue();
  table->setCell(row, col, newValue);
}

void EditCellCommand::undo()
{
  table->setCell(row, col, oldValue);
}

Command *EditCellCommand::clone() const
{
  return new EditCellCommand(table, row, col, newValue);
}
