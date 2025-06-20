#include "table.h"

Table::Table() : hasChanges_(false), delimiter_(','), hasBackup_(false) {}

Table::~Table() = default;

// Парсване на ред от CSV
MyArray<String> Table::parseLine(const String &line)
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
    else if (!inQuotes && c == delimiter_)
    {
      tokens.pushBack(current);
      current.clear();
    }
    else
    {
      current.pushBack(c);
    }
  }

  tokens.pushBack(current);
  return tokens;
}

// Добавяне на ред с данни
void Table::addDataRow(const MyArray<String> &tokens)
{
  // Разширяване на броя колони ако е необходимо
  while (columns_.size() < tokens.size())
  {
    String colName = String("Column") + intToString(columns_.size() + 1);
    columns_.pushBack(Column(colName));
  }

  for (size_t i = 0; i < tokens.size(); ++i)
  {
    DataType type = determineDataType(tokens[i]);
    columns_[i].addCell(Cell(tokens[i], type));
  }
}

// Определяне на типовете за всички колони
void Table::determineColumnTypes()
{
  for (size_t colIdx = 0; colIdx < columns_.size(); ++colIdx)
  {
    Column &col = columns_[colIdx];
    if (col.size() == 0)
      continue;

    DataType commonType = col.getCell(0).getType();
    bool allSameType = true;

    for (size_t i = 1; i < col.size(); ++i)
    {
      if (col.getCell(i).getType() != commonType)
      {
        allSameType = false;
        break;
      }
    }

    if (allSameType)
    {
      col.setType(commonType);
    }
    else
    {
      col.setType(DataType::TEXT);
      // Конвертиране на всички клетки към текст
      for (size_t i = 0; i < col.size(); ++i)
      {
        Cell cell = col.getCell(i);
        cell.setType(DataType::TEXT);
        col.setCell(i, cell);
      }
    }
  }
}

// Зареждане от CSV файл
bool Table::loadFromCSV(const String &filename, bool hasHeaders, char delimiter)
{
  std::ifstream file(filename.c_str());
  if (!file.is_open())
  {
    std::cerr << "Error: Cannot open file " << filename.c_str() << std::endl;
    return false;
  }

  filename_ = filename;
  delimiter_ = delimiter;
  columns_.clear();

  char line[4096];
  bool firstLine = true;

  while (file.getline(line, sizeof(line)))
  {
    String lineStr(line);
    MyArray<String> tokens = parseLine(lineStr);

    if (firstLine)
    {
      if (hasHeaders)
      {
        // Създаване на колони с имена от заглавията
        for (size_t i = 0; i < tokens.size(); ++i)
        {
          columns_.pushBack(Column(tokens[i]));
        }
      }
      else
      {
        // Създаване на колони с номерирани имена
        for (size_t i = 0; i < tokens.size(); ++i)
        {
          String colName = String("Column") + intToString(i + 1);
          columns_.pushBack(Column(colName));
        }
        // Добавяне на данните от първия ред
        addDataRow(tokens);
      }
      firstLine = false;
    }
    else
    {
      addDataRow(tokens);
    }
  }

  // Определяне на типовете данни за всяка колона
  determineColumnTypes();

  hasChanges_ = false;
  file.close();
  return true;
}

// Запазване в CSV файл
bool Table::saveToCSV(const String &filename)
{
  String saveFile = filename.empty() ? filename_ : filename;
  if (saveFile.empty())
  {
    std::cerr << "Error: No filename specified" << std::endl;
    return false;
  }

  std::ofstream file(saveFile.c_str());
  if (!file.is_open())
  {
    std::cerr << "Error: Cannot create file " << saveFile.c_str() << std::endl;
    return false;
  }

  // Записване на заглавията
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (i > 0)
      file << delimiter_;
    file << columns_[i].getName().c_str();
  }
  file << std::endl;

  // Записване на данните
  size_t maxRows = 0;
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (columns_[i].size() > maxRows)
      maxRows = columns_[i].size();
  }

  for (size_t row = 0; row < maxRows; ++row)
  {
    for (size_t col = 0; col < columns_.size(); ++col)
    {
      if (col > 0)
        file << delimiter_;
      if (row < columns_[col].size())
      {
        file << columns_[col].getCell(row).getValue().c_str();
      }
    }
    file << std::endl;
  }

  if (!filename.empty())
  {
    filename_ = filename;
  }
  hasChanges_ = false;
  file.close();
  return true;
}

// Печатане на таблицата
void Table::print() const
{
  if (columns_.empty())
  {
    std::cout << "Table is empty" << std::endl;
    return;
  }

  // Печатане на заглавията
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (i > 0)
      std::cout << "\t";
    std::cout << columns_[i].getName().c_str();
  }
  std::cout << std::endl;

  // Печатане на данните
  size_t maxRows = 0;
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (columns_[i].size() > maxRows)
      maxRows = columns_[i].size();
  }

  for (size_t row = 0; row < maxRows; ++row)
  {
    for (size_t col = 0; col < columns_.size(); ++col)
    {
      if (col > 0)
        std::cout << "\t";
      if (row < columns_[col].size())
      {
        std::cout << columns_[col].getCell(row).getValue().c_str();
      }
    }
    std::cout << std::endl;
  }
}

// Сортиране
void Table::sort(const String &columnName, bool ascending)
{
  createBackup();

  int colIndex = findColumnIndex(columnName);
  if (colIndex == -1)
  {
    colIndex = stringToInt(columnName) - 1;
    if (colIndex < 0)
    {
      std::cerr << "Error: Column not found: " << columnName.c_str() << std::endl;
      return;
    }
  }

  if (colIndex < 0 || colIndex >= static_cast<int>(columns_.size()))
  {
    std::cerr << "Error: Invalid column index" << std::endl;
    return;
  }

  sortByColumn(colIndex, ascending);
  hasChanges_ = true;
}

// Филтриране
void Table::filter(const String &columnName, const String &op, const String &value)
{
  createBackup();

  int colIndex = findColumnIndex(columnName);
  if (colIndex == -1)
  {
    colIndex = stringToInt(columnName) - 1;
    if (colIndex < 0)
    {
      std::cerr << "Error: Column not found: " << columnName.c_str() << std::endl;
      return;
    }
  }

  if (colIndex < 0 || colIndex >= static_cast<int>(columns_.size()))
  {
    std::cerr << "Error: Invalid column index" << std::endl;
    return;
  }

  filterByCondition(colIndex, op, value);
  hasChanges_ = true;
}

// Премахване на дублиращи се редове
void Table::removeDuplicateRows()
{
  createBackup();

  if (columns_.empty())
    return;

  size_t maxRows = 0;
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (columns_[i].size() > maxRows)
      maxRows = columns_[i].size();
  }

  MyArray<bool> toRemove;
  toRemove.reserve(maxRows);
  for (size_t i = 0; i < maxRows; ++i)
  {
    toRemove.pushBack(false);
  }

  for (size_t i = 0; i < maxRows; ++i)
  {
    if (toRemove[i])
      continue;

    for (size_t j = i + 1; j < maxRows; ++j)
    {
      if (toRemove[j])
        continue;

      bool identical = true;
      for (size_t col = 0; col < columns_.size(); ++col)
      {
        if (i >= columns_[col].size() || j >= columns_[col].size())
        {
          identical = false;
          break;
        }
        if (columns_[col].getCell(i) != columns_[col].getCell(j))
        {
          identical = false;
          break;
        }
      }

      if (identical)
      {
        toRemove[j] = true;
      }
    }
  }

  // Премахване на маркираните редове
  for (int row = maxRows - 1; row >= 0; --row)
  {
    if (toRemove[row])
    {
      for (size_t col = 0; col < columns_.size(); ++col)
      {
        columns_[col].removeCell(row);
      }
    }
  }

  hasChanges_ = true;
}

// Премахване на колона
void Table::removeColumn(const String &columnName)
{
  createBackup();

  int colIndex = findColumnIndex(columnName);
  if (colIndex == -1)
  {
    colIndex = stringToInt(columnName) - 1;
    if (colIndex < 0)
    {
      std::cerr << "Error: Column not found: " << columnName.c_str() << std::endl;
      return;
    }
  }

  if (colIndex < 0 || colIndex >= static_cast<int>(columns_.size()))
  {
    std::cerr << "Error: Invalid column index" << std::endl;
    return;
  }

  columns_.erase(colIndex);
  hasChanges_ = true;
}

// Дублиране на колона
void Table::duplicateColumn(const String &columnName, const String &newName)
{
  createBackup();

  int colIndex = findColumnIndex(columnName);
  if (colIndex == -1)
  {
    colIndex = stringToInt(columnName) - 1;
    if (colIndex < 0)
    {
      std::cerr << "Error: Column not found: " << columnName.c_str() << std::endl;
      return;
    }
  }

  if (colIndex < 0 || colIndex >= static_cast<int>(columns_.size()))
  {
    std::cerr << "Error: Invalid column index" << std::endl;
    return;
  }

  Column newCol = columns_[colIndex];
  String finalName = newName;
  if (finalName.empty())
  {
    finalName = columns_[colIndex].getName() + String("_copy");
    int counter = 1;
    while (findColumnIndex(finalName) != -1)
    {
      finalName = columns_[colIndex].getName() + String("_copy") + intToString(counter++);
    }
  }

  newCol.setName(finalName);
  columns_.pushBack(newCol);
  hasChanges_ = true;
}

// Промяна на стойност в клетка
void Table::setCellValue(const String &columnName, size_t row, const String &value)
{
  createBackup();

  int colIndex = findColumnIndex(columnName);
  if (colIndex == -1)
  {
    colIndex = stringToInt(columnName) - 1;
    if (colIndex < 0)
    {
      std::cerr << "Error: Column not found: " << columnName.c_str() << std::endl;
      return;
    }
  }

  if (colIndex < 0 || colIndex >= static_cast<int>(columns_.size()))
  {
    std::cerr << "Error: Invalid column index" << std::endl;
    return;
  }

  DataType cellType = determineDataType(value);
  Cell newCell(value, cellType);
  columns_[colIndex].setCell(row, newCell);
  hasChanges_ = true;
}

// Добавяне на ред
void Table::addRow(const String &type, int sourceRow)
{
  createBackup();

  if (type == String("copy") && sourceRow >= 0)
  {
    for (size_t col = 0; col < columns_.size(); ++col)
    {
      if (sourceRow < static_cast<int>(columns_[col].size()))
      {
        columns_[col].addCell(columns_[col].getCell(sourceRow));
      }
      else
      {
        columns_[col].addCell(Cell());
      }
    }
  }
  else if (type == String("min"))
  {
    for (size_t col = 0; col < columns_.size(); ++col)
    {
      columns_[col].addCell(columns_[col].getMinValue());
    }
  }
  else if (type == String("max"))
  {
    for (size_t col = 0; col < columns_.size(); ++col)
    {
      columns_[col].addCell(columns_[col].getMaxValue());
    }
  }
  else if (type == String("mode"))
  {
    for (size_t col = 0; col < columns_.size(); ++col)
    {
      columns_[col].addCell(columns_[col].getMostFrequentValue());
    }
  }

  hasChanges_ = true;
}

// Undo функционалност
void Table::undo()
{
  if (hasBackup_)
  {
    columns_ = backupColumns_;
    hasBackup_ = false;
    hasChanges_ = true;
    std::cout << "Operation undone" << std::endl;
  }
  else
  {
    std::cout << "Nothing to undo" << std::endl;
  }
}

// Връща дали има незапазени промени
bool Table::hasUnsavedChanges() const { return hasChanges_; }

// Създаване на backup за undo
void Table::createBackup()
{
  backupColumns_ = columns_;
  hasBackup_ = true;
}

// Намиране на индекс на колона по име
int Table::findColumnIndex(const String &name)
{
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (columns_[i].getName() == name)
    {
      return static_cast<int>(i);
    }
  }
  return -1;
}

// Сортиране по колона
void Table::sortByColumn(int colIndex, bool ascending)
{
  if (columns_.empty() || colIndex >= static_cast<int>(columns_.size()))
    return;

  size_t maxRows = 0;
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (columns_[i].size() > maxRows)
      maxRows = columns_[i].size();
  }

  // Създаване на индекси за сортиране
  MyArray<size_t> indices;
  indices.reserve(maxRows);
  for (size_t i = 0; i < maxRows; ++i)
  {
    indices.pushBack(i);
  }

  // Сортиране на индексите с QuickSort
  if (!indices.empty())
  {
    quickSort(indices, 0, static_cast<int>(indices.size()) - 1, colIndex, ascending);
  }

  // Пренареждане на всички колони според новия ред
  for (size_t col = 0; col < columns_.size(); ++col)
  {
    MyArray<Cell> newCells;
    newCells.reserve(maxRows);

    for (size_t i = 0; i < indices.size(); ++i)
    {
      size_t newIndex = indices[i];
      if (newIndex < columns_[col].size())
      {
        newCells.pushBack(columns_[col].getCell(newIndex));
      }
      else
      {
        newCells.pushBack(Cell());
      }
    }

    for (size_t i = 0; i < newCells.size(); ++i)
    {
      columns_[col].setCell(i, newCells[i]);
    }
  }
}

// Помощна функция за разменяне
void Table::swapElements(size_t &a, size_t &b)
{
  size_t temp = a;
  a = b;
  b = temp;
}

// QuickSort имплементация за сортиране на индекси
// Инспирирано от https://stackoverflow.com/questions/5787964/c-quick-sort-algorithm
void Table::quickSort(MyArray<size_t> &indices, int low, int high, int colIndex, bool ascending)
{
  if (low < high)
  {
    int pi = partition(indices, low, high, colIndex, ascending);
    quickSort(indices, low, pi - 1, colIndex, ascending);
    quickSort(indices, pi + 1, high, colIndex, ascending);
  }
}

int Table::partition(MyArray<size_t> &indices, int low, int high, int colIndex, bool ascending)
{
  size_t pivot = indices[high];
  int i = low - 1;

  for (int j = low; j < high; ++j)
  {
    bool shouldSwap = compareIndices(indices[j], pivot, colIndex, ascending);

    if (shouldSwap)
    {
      ++i;
      swapElements(indices[i], indices[j]);
    }
  }

  swapElements(indices[i + 1], indices[high]);
  return i + 1;
}

// Сравнява два индекса според стойностите в определена колона
bool Table::compareIndices(size_t a, size_t b, int colIndex, bool ascending)
{
  if (a >= columns_[colIndex].size())
    return !ascending;
  if (b >= columns_[colIndex].size())
    return ascending;

  bool result = columns_[colIndex].getCell(a) < columns_[colIndex].getCell(b);
  return ascending ? result : !result;
}

// Филтрира таблицата според условие върху определена колона
void Table::filterByCondition(int colIndex, const String &op, const String &value)
{
  if (columns_.empty() || colIndex >= static_cast<int>(columns_.size()))
    return;

  DataType valueType = determineDataType(value);
  Cell filterCell(value, valueType);

  size_t maxRows = 0;
  for (size_t i = 0; i < columns_.size(); ++i)
  {
    if (columns_[i].size() > maxRows)
      maxRows = columns_[i].size();
  }

  MyArray<bool> toKeep;
  toKeep.reserve(maxRows);
  for (size_t i = 0; i < maxRows; ++i)
  {
    toKeep.pushBack(false);
  }

  for (size_t row = 0; row < maxRows; ++row)
  {
    if (row >= columns_[colIndex].size())
      continue;

    const Cell &cell = columns_[colIndex].getCell(row);
    bool keep = false;

    try
    {
      if (op == String("=="))
        keep = (cell == filterCell);
      else if (op == String("!="))
        keep = (cell != filterCell);
      else if (op == String("<"))
        keep = (cell < filterCell);
      else if (op == String("<="))
        keep = (cell <= filterCell);
      else if (op == String(">"))
        keep = (cell > filterCell);
      else if (op == String(">="))
        keep = (cell >= filterCell);
    }
    catch (...)
    {
      // При грешка в сравнението, не запазваме реда
      keep = false;
    }

    toKeep[row] = keep;
  }

  // Премахване на нежеланите редове
  for (int row = maxRows - 1; row >= 0; --row)
  {
    if (!toKeep[row])
    {
      for (size_t col = 0; col < columns_.size(); ++col)
      {
        if (row < static_cast<int>(columns_[col].size()))
        {
          columns_[col].removeCell(row);
        }
      }
    }
  }
}
