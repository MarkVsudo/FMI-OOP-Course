//=== src/io/CommandProcessor.h ===
#pragma once

#include "Table.h"
#include "CommandHistory.h"
#include "InputParser.h"
#include <string>
#include <vector>

class CommandProcessor
{
private:
  Table currentTable;
  CommandHistory history;
  char csvDelimiter;

public:
  CommandProcessor() : csvDelimiter(',') {}

  bool processCommand(const std::string &input);
  void run();

private:
  void handleOpen(const std::vector<std::string> &args);
  void handleSave(const std::vector<std::string> &args);
  void handleSaveAs(const std::vector<std::string> &args);
  void handlePrint(const std::vector<std::string> &args);
  void handleSort(const std::vector<std::string> &args);
  void handleFilter(const std::vector<std::string> &args);
  void handleAddRow(const std::vector<std::string> &args);
  void handleRemoveRow(const std::vector<std::string> &args);
  void handleAddColumn(const std::vector<std::string> &args);
  void handleRemoveColumn(const std::vector<std::string> &args);
  void handleEditCell(const std::vector<std::string> &args);
  void handleUndo(const std::vector<std::string> &args);
  void handleExit(const std::vector<std::string> &args);
  void handleHelp(const std::vector<std::string> &args);

  bool confirmSaveChanges();
  size_t parseColumnReference(const std::string &ref);
  void showError(const std::string &message);
  void showMessage(const std::string &message);
};
