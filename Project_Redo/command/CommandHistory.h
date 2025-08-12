//=== src/command/CommandHistory.h ===
#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

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

#endif