#pragma once

#include <iostream>
#include <exception>
#include "table.h"
#include "myArray.h"
#include "myString.h"
#include "utils.h"

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
  MyArray<String> tokenize(const String &line);

  // Функции за показване на помощ
  void showHelp();

  // Функции за обработка на различните команди
  void handleOpen(const MyArray<String> &tokens);
  void handleSave(const MyArray<String> &tokens);
  void handleSort(const MyArray<String> &tokens);
  void handleFilter(const MyArray<String> &tokens);
  void handleRemoveColumn(const MyArray<String> &tokens);
  void handleDuplicateColumn(const MyArray<String> &tokens);
  void handleSetCell(const MyArray<String> &tokens);
  void handleAddRow(const MyArray<String> &tokens);
  void handleExit();
};
