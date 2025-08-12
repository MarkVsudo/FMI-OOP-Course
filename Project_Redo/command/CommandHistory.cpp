//=== src/command/CommandHistory.cpp ===
#include "CommandHistory.h"

void CommandHistory::executeCommand(Command *command)
{
  command->execute();

  delete lastCommand;
  lastCommand = command->clone();
  delete command;
}

void CommandHistory::undo()
{
  if (lastCommand)
  {
    lastCommand->undo();
    delete lastCommand;
    lastCommand = nullptr;
  }
}