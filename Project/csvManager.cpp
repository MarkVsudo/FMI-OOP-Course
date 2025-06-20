#include "csvManager.h"

CSVManager::CSVManager() : running_(true) {}

void CSVManager::run()
{
  std::cout << "CSV Table Manager" << std::endl;
  std::cout << "Type 'help' for available commands" << std::endl;

  while (running_)
  {
    std::cout << "> ";
    char line[1024];
    std::cin.getline(line, sizeof(line));

    String lineStr(line);
    if (lineStr.empty())
      continue;

    MyArray<String> tokens = tokenize(lineStr);
    if (tokens.empty())
      continue;

    String command = tokens[0];

    try
    {
      if (command == String("help"))
      {
        showHelp();
      }
      else if (command == String("open"))
      {
        handleOpen(tokens);
      }
      else if (command == String("save"))
      {
        handleSave(tokens);
      }
      else if (command == String("print"))
      {
        table_.print();
      }
      else if (command == String("sort"))
      {
        handleSort(tokens);
      }
      else if (command == String("filter"))
      {
        handleFilter(tokens);
      }
      else if (command == String("remove_duplicates"))
      {
        table_.removeDuplicateRows();
        std::cout << "Duplicate rows removed" << std::endl;
      }
      else if (command == String("remove_column"))
      {
        handleRemoveColumn(tokens);
      }
      else if (command == String("duplicate_column"))
      {
        handleDuplicateColumn(tokens);
      }
      else if (command == String("set_cell"))
      {
        handleSetCell(tokens);
      }
      else if (command == String("add_row"))
      {
        handleAddRow(tokens);
      }
      else if (command == String("undo"))
      {
        table_.undo();
      }
      else if (command == String("exit"))
      {
        handleExit();
      }
      else
      {
        std::cout << "Unknown command: " << command.c_str() << std::endl;
        std::cout << "Type 'help' for available commands" << std::endl;
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}

MyArray<String> CSVManager::tokenize(const String &line)
{
  MyArray<String> tokens;
  String current;
  bool inQuotes = false;
  char quoteChar = '\0';

  for (size_t i = 0; i < line.length(); ++i)
  {
    char c = line[i];

    if (!inQuotes && (c == '"' || c == '\''))
    {
      inQuotes = true;
      quoteChar = c;
    }
    else if (inQuotes && c == quoteChar)
    {
      inQuotes = false;
      quoteChar = '\0';
    }
    else if (!inQuotes && isSpaceChar(c))
    {
      if (!current.empty())
      {
        tokens.pushBack(current);
        current.clear();
      }
    }
    else
    {
      current.pushBack(c);
    }
  }

  if (!current.empty())
  {
    tokens.pushBack(current);
  }

  return tokens;
}

void CSVManager::showHelp()
{
  std::cout << "\nAvailable commands:\n";
  std::cout << "  help - Show this help message\n";
  std::cout << "  open <filename> [headers] [delimiter] - Load CSV file\n";
  std::cout << "    headers: true/false (default: true)\n";
  std::cout << "    delimiter: single character (default: ,)\n";
  std::cout << "  save [filename] - Save current table\n";
  std::cout << "  print - Display current table\n";
  std::cout << "  sort <column> [asc/desc] - Sort by column (default: asc)\n";
  std::cout << "  filter <column> <operator> <value> - Filter rows\n";
  std::cout << "    operators: ==, !=, <, <=, >, >=\n";
  std::cout << "  remove_duplicates - Remove duplicate rows\n";
  std::cout << "  remove_column <column> - Remove column\n";
  std::cout << "  duplicate_column <column> [new_name] - Duplicate column\n";
  std::cout << "  set_cell <column> <row> <value> - Set cell value\n";
  std::cout << "  add_row <type> [source_row] - Add new row\n";
  std::cout << "    types: copy, min, max, mode\n";
  std::cout << "  undo - Undo last operation\n";
  std::cout << "  exit - Exit program\n";
  std::cout << std::endl;
}

void CSVManager::handleOpen(const MyArray<String> &tokens)
{
  if (tokens.size() < 2)
  {
    std::cout << "Usage: open <filename> [headers] [delimiter]" << std::endl;
    return;
  }

  String filename = tokens[1];
  bool hasHeaders = true;
  char delimiter = ',';

  if (tokens.size() > 2)
  {
    String headerStr = tokens[2];
    hasHeaders = (headerStr == String("true") || headerStr == String("1"));
  }

  if (tokens.size() > 3)
  {
    if (tokens[3].length() == 1)
    {
      delimiter = tokens[3][0];
    }
    else
    {
      std::cout << "Warning: Delimiter must be a single character, using default ','" << std::endl;
    }
  }

  if (table_.loadFromCSV(filename, hasHeaders, delimiter))
  {
    std::cout << "File loaded successfully: " << filename.c_str() << std::endl;
  }
  else
  {
    std::cout << "Failed to load file: " << filename.c_str() << std::endl;
  }
}

void CSVManager::handleSave(const MyArray<String> &tokens)
{
  String filename;
  if (tokens.size() > 1)
  {
    filename = tokens[1];
  }

  if (table_.saveToCSV(filename))
  {
    std::cout << "File saved successfully" << std::endl;
  }
  else
  {
    std::cout << "Failed to save file" << std::endl;
  }
}

void CSVManager::handleSort(const MyArray<String> &tokens)
{
  if (tokens.size() < 2)
  {
    std::cout << "Usage: sort <column> [asc/desc]" << std::endl;
    return;
  }

  String column = tokens[1];
  bool ascending = true;

  if (tokens.size() > 2)
  {
    String direction = tokens[2];
    ascending = (direction != String("desc") && direction != String("descending"));
  }

  table_.sort(column, ascending);
  std::cout << "Table sorted by column: " << column.c_str() << std::endl;
}

void CSVManager::handleFilter(const MyArray<String> &tokens)
{
  if (tokens.size() < 4)
  {
    std::cout << "Usage: filter <column> <operator> <value>" << std::endl;
    std::cout << "Operators: ==, !=, <, <=, >, >=" << std::endl;
    return;
  }

  String column = tokens[1];
  String op = tokens[2];
  String value = tokens[3];

  // Проверка за валиден оператор
  if (op != String("==") && op != String("!=") && op != String("<") &&
      op != String("<=") && op != String(">") && op != String(">="))
  {
    std::cout << "Invalid operator: " << op.c_str() << std::endl;
    std::cout << "Valid operators: ==, !=, <, <=, >, >=" << std::endl;
    return;
  }

  table_.filter(column, op, value);
  std::cout << "Table filtered" << std::endl;
}

void CSVManager::handleRemoveColumn(const MyArray<String> &tokens)
{
  if (tokens.size() < 2)
  {
    std::cout << "Usage: remove_column <column>" << std::endl;
    return;
  }

  String column = tokens[1];
  table_.removeColumn(column);
  std::cout << "Column removed: " << column.c_str() << std::endl;
}

void CSVManager::handleDuplicateColumn(const MyArray<String> &tokens)
{
  if (tokens.size() < 2)
  {
    std::cout << "Usage: duplicate_column <column> [new_name]" << std::endl;
    return;
  }

  String column = tokens[1];
  String newName;
  if (tokens.size() > 2)
  {
    newName = tokens[2];
  }

  table_.duplicateColumn(column, newName);
  std::cout << "Column duplicated: " << column.c_str() << std::endl;
}

void CSVManager::handleSetCell(const MyArray<String> &tokens)
{
  if (tokens.size() < 4)
  {
    std::cout << "Usage: set_cell <column> <row> <value>" << std::endl;
    return;
  }

  String column = tokens[1];
  try
  {
    int rowNum = stringToInt(tokens[2]);
    if (rowNum <= 0)
    {
      std::cout << "Row number must be positive: " << tokens[2].c_str() << std::endl;
      return;
    }

    size_t row = static_cast<size_t>(rowNum - 1); // Потребителят въвежда 1-базирани индекси
    String value = tokens[3];

    table_.setCellValue(column, row, value);
    std::cout << "Cell value updated" << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Invalid row number: " << tokens[2].c_str() << std::endl;
  }
}

void CSVManager::handleAddRow(const MyArray<String> &tokens)
{
  if (tokens.size() < 2)
  {
    std::cout << "Usage: add_row <type> [source_row]" << std::endl;
    std::cout << "Types: copy, min, max, mode" << std::endl;
    return;
  }

  String type = tokens[1];
  int sourceRow = -1;

  if (type == String("copy"))
  {
    if (tokens.size() < 3)
    {
      std::cout << "Usage: add_row copy <source_row>" << std::endl;
      return;
    }
    try
    {
      int rowNum = stringToInt(tokens[2]);
      if (rowNum <= 0)
      {
        std::cout << "Source row number must be positive: " << tokens[2].c_str() << std::endl;
        return;
      }
      sourceRow = rowNum - 1; // Потребителят въвежда 1-базирани индекси
    }
    catch (const std::exception &e)
    {
      std::cout << "Invalid source row number: " << tokens[2].c_str() << std::endl;
      return;
    }
  }

  if (type != String("copy") && type != String("min") &&
      type != String("max") && type != String("mode"))
  {
    std::cout << "Invalid row type: " << type.c_str() << std::endl;
    std::cout << "Valid types: copy, min, max, mode" << std::endl;
    return;
  }

  table_.addRow(type, sourceRow);
  std::cout << "Row added (" << type.c_str() << ")" << std::endl;
}

void CSVManager::handleExit()
{
  if (table_.hasUnsavedChanges())
  {
    std::cout << "You have unsaved changes. Save before exit? (y/n): ";
    char response[256];
    std::cin.getline(response, sizeof(response));
    String responseStr(response);

    if (responseStr == String("y") || responseStr == String("yes") || responseStr == String("Y"))
    {
      if (table_.saveToCSV())
      {
        std::cout << "Changes saved successfully" << std::endl;
      }
      else
      {
        std::cout << "Failed to save changes" << std::endl;
        std::cout << "Exit anyway? (y/n): ";
        std::cin.getline(response, sizeof(response));
        String exitResponse(response);
        if (exitResponse != String("y") && exitResponse != String("yes") && exitResponse != String("Y"))
        {
          return; // Не излизаме
        }
      }
    }
  }

  std::cout << "Goodbye!" << std::endl;
  running_ = false;
}
