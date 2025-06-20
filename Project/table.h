#pragma once
#include <iostream>
#include <fstream>
#include "myArray.h"
#include "myString.h"
#include "column.h"
#include "cell.h"
#include "dataType.h"
#include "utils.h"

class Table
{
private:
  MyArray<Column> columns_;
  String filename_;
  bool hasChanges_;
  char delimiter_;

  // За undo функционалност
  MyArray<Column> backupColumns_;
  bool hasBackup_;

public:
  // Конструктори и деструктор
  Table();
  ~Table();

  // Парсване и работа със CSV данни
  MyArray<String> parseLine(const String &line);
  void addDataRow(const MyArray<String> &tokens);
  void determineColumnTypes();

  // Зареждане и запазване на файлове
  bool loadFromCSV(const String &filename, bool hasHeaders = true, char delimiter = ',');
  bool saveToCSV(const String &filename = String(""));

  // Показване на данни
  void print() const;

  // Операции за сортиране и филтриране
  void sort(const String &columnName, bool ascending = true);
  void filter(const String &columnName, const String &op, const String &value);

  // Операции с редове и колони
  void removeDuplicateRows();
  void removeColumn(const String &columnName);
  void duplicateColumn(const String &columnName, const String &newName = String(""));
  void setCellValue(const String &columnName, size_t row, const String &value);
  void addRow(const String &type, int sourceRow = -1);

  // Undo функционалност
  void undo();

  // Проверка за незапазени промени
  bool hasUnsavedChanges() const;

private:
  // Помощни функции
  void createBackup();
  int findColumnIndex(const String &name);

  // Функции за сортиране
  void sortByColumn(int colIndex, bool ascending);
  void swapElements(size_t &a, size_t &b);
  void quickSort(MyArray<size_t> &indices, int low, int high, int colIndex, bool ascending);
  int partition(MyArray<size_t> &indices, int low, int high, int colIndex, bool ascending);
  bool compareIndices(size_t a, size_t b, int colIndex, bool ascending);

  // Функции за филтриране
  void filterByCondition(int colIndex, const String &op, const String &value);
};
