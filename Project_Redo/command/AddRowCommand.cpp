//=== src/command/AddRowCommand.cpp ===
#include "AddRowCommand.h"

void AddRowCommand::execute()
{
  addedRowIndex = table->getRowCount();
  table->addRow(row);
}

void AddRowCommand::undo()
{
  if (addedRowIndex < table->getRowCount())
  {
    table->removeRow(addedRowIndex);
  }
}

Command *AddRowCommand::clone() const
{
  return new AddRowCommand(table, row);
}