//=== src/io/CommandProcessor.cpp ===
#include "CommandProcessor.h"
#include "CSVParser.h"
#include "CSVWriter.h"
#include "CSVFormatter.h"
#include "SortCommand.h"
#include "FilterCommand.h"
#include "AddRowCommand.h"
#include "RemoveRowCommand.h"
#include "AddColumnCommand.h"
#include "EditCellCommand.h"
#include "Exception.h"
#include "StringUtils.h"
#include "InputParser.h"
#include <iostream>

bool CommandProcessor::processCommand(const std::string &input)
{
  try
  {
    ParsedCommand cmd = InputParser::parseCommand(input);

    if (cmd.command.empty())
    {
      return true; // Continue
    }

    if (cmd.command == "open")
    {
      handleOpen(cmd.arguments);
    }
    else if (cmd.command == "save")
    {
      handleSave(cmd.arguments);
    }
    else if (cmd.command == "saveas")
    {
      handleSaveAs(cmd.arguments);
    }
    else if (cmd.command == "print")
    {
      handlePrint(cmd.arguments);
    }
    else if (cmd.command == "sort")
    {
      handleSort(cmd.arguments);
    }
    else if (cmd.command == "filter")
    {
      handleFilter(cmd.arguments);
    }
    else if (cmd.command == "addrow")
    {
      handleAddRow(cmd.arguments);
    }
    else if (cmd.command == "removerow")
    {
      handleRemoveRow(cmd.arguments);
    }
    else if (cmd.command == "addcolumn")
    {
      handleAddColumn(cmd.arguments);
    }
    else if (cmd.command == "removecolumn")
    {
      handleRemoveColumn(cmd.arguments);
    }
    else if (cmd.command == "edit")
    {
      handleEditCell(cmd.arguments);
    }
    else if (cmd.command == "undo")
    {
      handleUndo(cmd.arguments);
    }
    else if (cmd.command == "exit")
    {
      handleExit(cmd.arguments);
      return false; // Exit
    }
    else if (cmd.command == "help")
    {
      handleHelp(cmd.arguments);
    }
    else
    {
      showError("Unknown command: " + cmd.command + ". Type 'help' for available commands.");
    }
  }
  catch (const CSVException &e)
  {
    showError(e.what());
  }
  catch (const std::exception &e)
  {
    showError("Error: " + std::string(e.what()));
  }

  return true; // Continue
}

void CommandProcessor::run()
{
  showMessage("CSV Table Manager");
  showMessage("Type 'help' for available commands or 'exit' to quit.");

  std::string input;
  while (true)
  {
    std::cout << "> ";
    std::getline(std::cin, input);

    if (!processCommand(input))
    {
      break;
    }
  }
}

void CommandProcessor::handleOpen(const std::vector<std::string> &args)
{
  if (args.empty())
  {
    showError("Usage: open <filename>");
    return;
  }

  if (currentTable.getModified())
  {
    if (!confirmSaveChanges())
    {
      return;
    }
  }

  CSVParser parser(csvDelimiter);
  currentTable = parser.parse(args[0]);
  showMessage("File loaded: " + args[0]);
}

void CommandProcessor::handleSave(const std::vector<std::string> &args)
{
  (void)args;

  if (currentTable.getFilename().empty())
  {
    showError("No file loaded. Use 'saveas <filename>' to save to a new file.");
    return;
  }
  CSVWriter writer(csvDelimiter);
  writer.write(currentTable, currentTable.getFilename());
  currentTable.setModified(false);
  showMessage("File saved: " + currentTable.getFilename());
}

void CommandProcessor::handleSaveAs(const std::vector<std::string> &args)
{
  (void)args;

  if (args.empty())
  {
    showError("Usage: saveas <filename>");
    return;
  }

  CSVWriter writer(csvDelimiter);
  writer.write(currentTable, args[0]);
  currentTable.setFilename(args[0]);
  currentTable.setModified(false);
  showMessage("File saved as: " + args[0]);
}

void CommandProcessor::handlePrint(const std::vector<std::string> &args)
{
  (void)args;

  CSVFormatter::printTable(currentTable);
}

void CommandProcessor::handleSort(const std::vector<std::string> &args)
{
  if (args.size() < 1)
  {
    showError("Usage: sort <column> [asc|desc]");
    return;
  }

  size_t columnIndex = parseColumnReference(args[0]);
  bool ascending = true;

  if (args.size() > 1)
  {
    std::string direction = StringUtils::toLowerCase(args[1]);
    if (direction == "desc")
    {
      ascending = false;
    }
  }

  SortCommand *cmd = new SortCommand(&currentTable, columnIndex, ascending);
  history.executeCommand(cmd);
  showMessage("Table sorted by column " + args[0]);
}

void CommandProcessor::handleFilter(const std::vector<std::string> &args)
{
  if (args.size() < 3)
  {
    showError("Usage: filter <column> <operator> <value>");
    showError("Operators: ==, !=, <, <=, >, >=");
    return;
  }

  size_t columnIndex = parseColumnReference(args[0]);
  std::string operation = args[1];
  std::string value = args[2];

  FilterCommand *cmd = new FilterCommand(&currentTable, columnIndex, operation, value);
  history.executeCommand(cmd);
  showMessage("Table filtered by column " + args[0] + " " + operation + " " + value);
}

void CommandProcessor::handleAddRow(const std::vector<std::string> &args)
{
  if (args.empty())
  {
    showError("Usage: addrow <type> [args]");
    showError("Types: copy <row_number>, min, max, mode");
    return;
  }

  std::string type = StringUtils::toLowerCase(args[0]);

  if (type == "copy")
  {
    if (args.size() < 2)
    {
      showError("Usage: addrow copy <row_number>");
      return;
    }

    size_t rowIndex = std::strtoul(args[1].c_str(), nullptr, 10) - 1; // Convert to 0-based
    if (rowIndex >= currentTable.getRowCount())
    {
      showError("Row number out of range");
      return;
    }

    Row newRow = currentTable.getRow(rowIndex);
    AddRowCommand *cmd = new AddRowCommand(&currentTable, newRow);
    history.executeCommand(cmd);
    showMessage("Row copied");
  }
  else if (type == "min")
  {
    currentTable.addRowMin();
    showMessage("Min row added");
  }
  else if (type == "max")
  {
    currentTable.addRowMax();
    showMessage("Max row added");
  }
  else if (type == "mode")
  {
    currentTable.addRowMode();
    showMessage("Mode row added");
  }
  else
  {
    showError("Unknown row type: " + type);
  }
}

void CommandProcessor::handleRemoveRow(const std::vector<std::string> &args)
{
  if (args.empty())
  {
    showError("Usage: removerow <row_number>");
    return;
  }

  size_t rowIndex = std::strtoul(args[0].c_str(), nullptr, 10) - 1; // Convert to 0-based
  if (rowIndex >= currentTable.getRowCount())
  {
    showError("Row number out of range");
    return;
  }

  RemoveRowCommand *cmd = new RemoveRowCommand(&currentTable, rowIndex);
  history.executeCommand(cmd);
  showMessage("Row removed");
}

void CommandProcessor::handleAddColumn(const std::vector<std::string> &args)
{
  if (args.empty())
  {
    showError("Usage: addcolumn <name>");
    return;
  }

  Column newColumn(args[0]);
  AddColumnCommand *cmd = new AddColumnCommand(&currentTable, newColumn);
  history.executeCommand(cmd);
  showMessage("Column added: " + args[0]);
}

void CommandProcessor::handleRemoveColumn(const std::vector<std::string> &args)
{
  if (args.empty())
  {
    showError("Usage: removecolumn <column>");
    return;
  }

  try
  {
    size_t columnIndex = parseColumnReference(args[0]);
    currentTable.removeColumn(columnIndex);
    showMessage("Column removed");
  }
  catch (const InvalidColumnException &e)
  {
    showError(e.what());
  }
}

void CommandProcessor::handleEditCell(const std::vector<std::string> &args)
{
  if (args.size() < 3)
  {
    showError("Usage: edit <row> <column> <value>");
    return;
  }

  size_t rowIndex = std::strtoul(args[0].c_str(), nullptr, 10) - 1; // Convert to 0-based
  size_t columnIndex = parseColumnReference(args[1]);
  std::string value = args[2];

  if (rowIndex >= currentTable.getRowCount())
  {
    showError("Row number out of range");
    return;
  }

  EditCellCommand *cmd = new EditCellCommand(&currentTable, rowIndex, columnIndex, value);
  history.executeCommand(cmd);
  showMessage("Cell edited");
}

void CommandProcessor::handleUndo(const std::vector<std::string> &args)
{
  (void)args;

  if (history.canUndo())
  {
    history.undo();
    showMessage("Last operation undone");
  }
  else
  {
    showMessage("Nothing to undo");
  }
}

void CommandProcessor::handleExit(const std::vector<std::string> &args)
{
  (void)args;

  if (currentTable.getModified())
  {
    confirmSaveChanges();
  }
  showMessage("Goodbye!");
}

void CommandProcessor::handleHelp(const std::vector<std::string> &args)
{
  (void)args;

  std::cout << "Available commands:\n";
  std::cout << "  open <filename>           - Load CSV file\n";
  std::cout << "  save                      - Save current file\n";
  std::cout << "  saveas <filename>         - Save as new file\n";
  std::cout << "  print                     - Display table\n";
  std::cout << "  sort <column> [asc|desc]  - Sort by column\n";
  std::cout << "  filter <col> <op> <val>   - Filter rows (==, !=, <, <=, >, >=)\n";
  std::cout << "  addrow <type> [args]      - Add row (copy <num>, min, max, mode)\n";
  std::cout << "  removerow <number>        - Remove row\n";
  std::cout << "  addcolumn <name>          - Add column\n";
  std::cout << "  removecolumn <column>     - Remove column\n";
  std::cout << "  edit <row> <col> <value>  - Edit cell\n";
  std::cout << "  undo                      - Undo last operation\n";
  std::cout << "  help                      - Show this help\n";
  std::cout << "  exit                      - Exit program\n";
}

bool CommandProcessor::confirmSaveChanges()
{
  std::cout << "Table has unsaved changes. Save before continuing? (y/n): ";
  std::string response;
  std::getline(std::cin, response);

  if (!response.empty() && (response[0] == 'y' || response[0] == 'Y'))
  {
    try
    {
      handleSave(std::vector<std::string>());
      return true;
    }
    catch (const CSVException &e)
    {
      showError("Failed to save: " + std::string(e.what()));
      return false;
    }
  }

  return true;
}

size_t CommandProcessor::parseColumnReference(const std::string &ref)
{
  // Try parsing as number first
  if (StringUtils::isNumber(ref))
  {
    size_t index = std::strtoul(ref.c_str(), nullptr, 10) - 1; // Convert to 0-based
    if (index < currentTable.getColumnCount())
    {
      return index;
    }
  }

  // Try parsing as column name
  try
  {
    return currentTable.getColumnIndex(ref);
  }
  catch (const InvalidColumnException &)
  {
    throw InvalidColumnException("Invalid column reference: " + ref);
  }
}

void CommandProcessor::showError(const std::string &message)
{
  std::cout << "Error: " + message << std::endl;
}

void CommandProcessor::showMessage(const std::string &message)
{
  std::cout << message << std::endl;
}