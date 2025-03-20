// 5. Напишете функция, която приема имената на два текстови файла, в които са записани цели числа в сортиран вид. Числата са разделени с интервал. Запишете в нов файл числата от двата дайла в сортиран вид. Числата отново да са разделени с интервал.

// НЕ Е позволено да използвате масив, за да пазите временно числата.
// Пример:
// Файл 1:
// 2 4 5 8
// Файл 2:
// 1 7 10 15 16
// Резултат:

// 1 2 4 5 7 8 10 15 16

#include <iostream>
#include <fstream>

void mergeSortedFiles(const char *inputFileName1, const char *inputFileName2, const char *outputFileName)
{
  std::ifstream inputFile1(inputFileName1);
  if (!inputFile1)
  {
    std::cerr << "Error opening file 1 for reading!" << std::endl;
    return;
  }

  std::ifstream inputFile2(inputFileName2);
  if (!inputFile2)
  {
    std::cerr << "Error opening file 2 for reading!" << std::endl;
    return;
  }

  std::ofstream outputFile(outputFileName);
  if (!outputFile)
  {
    std::cerr << "Error opening output file for writing!" << std::endl;
    return;
  }

  int num1, num2;
  if (inputFile1 >> num1 && inputFile2 >> num2)
  {
    // While both files have numbers
    while (inputFile1 && inputFile2)
    {
      if (num1 < num2)
      {
        outputFile << num1 << " ";
        inputFile1 >> num1;
      }
      else
      {
        outputFile << num2 << " ";
        inputFile2 >> num2;
      }
    }

    // For remaining numbers
    while (inputFile1)
    {
      outputFile << num1 << " ";
      inputFile1 >> num1;
    }

    while (inputFile2)
    {
      outputFile << num2 << " ";
      inputFile2 >> num2;
    }
  }

  outputFile.close();
  inputFile1.close();
  inputFile2.close();
}

int main()
{

  const char *inputFileName1 = "inputFile1.txt";
  const char *inputFileName2 = "inputFile2.txt";
  const char *outputFileName = "outputFile.txt";

  mergeSortedFiles(inputFileName1, inputFileName2, outputFileName);

  return 0;
}