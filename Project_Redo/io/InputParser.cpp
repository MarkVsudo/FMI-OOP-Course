//=== src/io/InputParser.cpp ===
#include "InputParser.h"
#include "../utils/StringUtils.h"

ParsedCommand InputParser::parseCommand(const std::string &input)
{
  std::vector<std::string> tokens = tokenize(input);

  ParsedCommand result;
  if (!tokens.empty())
  {
    result.command = StringUtils::toLowerCase(tokens[0]);
    for (size_t i = 1; i < tokens.size(); ++i)
    {
      result.arguments.push_back(tokens[i]);
    }
  }

  return result;
}

std::vector<std::string> InputParser::tokenize(const std::string &input)
{
  std::vector<std::string> tokens;
  std::string current;
  bool inQuotes = false;
  char quoteChar = '\0';

  for (size_t i = 0; i < input.length(); ++i)
  {
    char c = input[i];

    if (!inQuotes && (c == '"' || c == '\''))
    {
      inQuotes = true;
      quoteChar = c;
    }
    else if (inQuotes && c == quoteChar)
    {
      inQuotes = false;
    }
    else if (!inQuotes && (c == ' ' || c == '\t'))
    {
      if (!current.empty())
      {
        tokens.push_back(StringUtils::trim(current));
        current.clear();
      }
    }
    else
    {
      current += c;
    }
  }

  if (!current.empty())
  {
    tokens.push_back(StringUtils::trim(current));
  }

  return tokens;
}

std::string InputParser::trim(const std::string &str)
{
  return StringUtils::trim(str);
}