//=== src/command/AddColumnCommand.cpp ===
#include "AddColumnCommand.h"

void AddColumnCommand::execute()
{
  addedColumnIndex = table->getColumnCount();
  table->addColumn(column);
}

void AddColumnCommand::undo()
{
  if (addedColumnIndex < table->getColumnCount())
  {
    table->removeColumn(addedColumnIndex);
  }
}

Command *AddColumnCommand::clone() const
{
  return new AddColumnCommand(table, column);
}