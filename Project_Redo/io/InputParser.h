//=== src/io/InputParser.h ===
#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <string>
#include <vector>

struct ParsedCommand
{
  std::string command;
  std::vector<std::string> arguments;
};

class InputParser
{
public:
  static ParsedCommand parseCommand(const std::string &input);

private:
  static std::vector<std::string> tokenize(const std::string &input);
  static std::string trim(const std::string &str);
};

#endif