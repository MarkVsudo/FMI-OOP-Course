// 1. Напишете функция, която приема име на текстов файл и принтира на стандартния изход съдържанието му.

#include <iostream>
#include <fstream>

int main()
{
  std::ifstream inputFile("text.txt");

  if (!inputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return -1;
  }

  char buffer[256];

  char line[100];
  while (inputFile.getline(line, sizeof(line)))
  {
    std::cout << line << std::endl;
  }

  inputFile.close();

  return 0;
}