#pragma once

#include <iostream>
#include <exception>
#include "table.h"
#include "myArray.h"
#include "myString.h"
#include "utils.h" // For stringToInt, isSpaceChar functions

class CSVManager
{
private:
  Table table_;
  bool running_;

public:
  // Конструктор
  CSVManager();

  // Основна функция за изпълнение
  void run();

private:
  // Помощни функции за парсване и обработка на команди
  Vector<String> tokenize(const String &line);

  // Функции за показване на помощ
  void showHelp();

  // Функции за обработка на различните команди
  void handleOpen(const Vector<String> &tokens);
  void handleSave(const Vector<String> &tokens);
  void handleSort(const Vector<String> &tokens);
  void handleFilter(const Vector<String> &tokens);
  void handleRemoveColumn(const Vector<String> &tokens);
  void handleDuplicateColumn(const Vector<String> &tokens);
  void handleSetCell(const Vector<String> &tokens);
  void handleAddRow(const Vector<String> &tokens);
  void handleExit();
};
