// 3. Напишете функция, която приема имена на два текстов файла и копира съдържанието на първия файл във втория.

#include <iostream>
#include <fstream>

void copyFileData(const char *inputFileName, const char *outputFileName)
{
  std::ifstream inputFile(inputFileName);
  if (!inputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return;
  }

  std::ofstream outputFile(outputFileName);
  if (!outputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return;
  }

  char buffer[512];
  while (inputFile.getline(buffer, sizeof(buffer)))
  {
    outputFile << buffer << std::endl;
  }

  inputFile.close();
  outputFile.close();

  std::cout << "Copied...\n";
}

int main()
{
  const char *inputFileName = "inputFile.txt";
  const char *outputFileName = "outputFile.txt";

  copyFileData(inputFileName, outputFileName);

  return 0;
}