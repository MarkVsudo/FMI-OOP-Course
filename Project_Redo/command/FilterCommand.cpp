//=== src/command/FilterCommand.cpp ===
#include "FilterCommand.h"

void FilterCommand::execute()
{
  // Save original state
  originalRows.clear();
  for (size_t i = 0; i < table->getRowCount(); ++i)
  {
    originalRows.push_back(table->getRow(i));
  }

  // Execute filter
  table->filter(columnIndex, operation, value);
}

void FilterCommand::undo()
{
  // Clear current rows and restore original
  while (table->getRowCount() > 0)
  {
    table->removeRow(0);
  }

  for (const Row &row : originalRows)
  {
    table->addRow(row);
  }
}

Command *FilterCommand::clone() const
{
  return new FilterCommand(table, columnIndex, operation, value);
}