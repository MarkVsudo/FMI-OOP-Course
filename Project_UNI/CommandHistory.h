//=== src/command/CommandHistory.h ===
#pragma once
#include "Command.h"

class CommandHistory
{
private:
  Command *lastCommand;

public:
  CommandHistory() : lastCommand(nullptr) {}
  ~CommandHistory() { delete lastCommand; }

  void executeCommand(Command *command);
  void undo();
  bool canUndo() const { return lastCommand != nullptr; }
};
