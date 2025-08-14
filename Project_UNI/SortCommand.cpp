//=== src/command/SortCommand.cpp ===
#include "SortCommand.h"

void SortCommand::execute()
{
  // Save original state
  originalRows.clear();
  for (size_t i = 0; i < table->getRowCount(); ++i)
  {
    originalRows.push_back(table->getRow(i));
  }

  // Execute sort
  table->sort(columnIndex, ascending);
}

void SortCommand::undo()
{
  // Restore original rows
  for (size_t i = 0; i < originalRows.size() && i < table->getRowCount(); ++i)
  {
    table->getRow(i) = originalRows[i];
  }

  // Handle size differences
  while (table->getRowCount() > originalRows.size())
  {
    table->removeRow(table->getRowCount() - 1);
  }

  while (table->getRowCount() < originalRows.size())
  {
    table->addRow(originalRows[table->getRowCount()]);
  }
}

Command *SortCommand::clone() const
{
  return new SortCommand(table, columnIndex, ascending);
}