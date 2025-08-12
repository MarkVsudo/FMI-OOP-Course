//=== src/command/RemoveRowCommand.cpp ===
#include "RemoveRowCommand.h"

void RemoveRowCommand::execute()
{
  if (rowIndex < table->getRowCount())
  {
    removedRow = table->getRow(rowIndex);
    table->removeRow(rowIndex);
  }
}

void RemoveRowCommand::undo()
{
  if (rowIndex <= table->getRowCount())
  {
    // Insert the row back at its original position
    table->addRow(removedRow); // Add at end first

    // Move it to correct position
    for (size_t i = table->getRowCount() - 1; i > rowIndex; --i)
    {
      Row temp = table->getRow(i);
      table->getRow(i) = table->getRow(i - 1);
      table->getRow(i - 1) = temp;
    }
  }
}

Command *RemoveRowCommand::clone() const
{
  return new RemoveRowCommand(table, rowIndex);
}