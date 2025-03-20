// 4. Напишете програма, която чете три цели числа от стандартния вход. Напишете функция, която приема трите числа и име на файл, в който ще запишете сумата и произведението им.

#include <iostream>
#include <fstream>

void writeNumsCalcToFile(const char *outputFileName, int a, int b, int c)
{
  std::ofstream outputFile(outputFileName);

  if (!outputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return;
  }

  int numsSum = a + b + c;
  int numsProduct = a * b * c;

  outputFile << "Sum of numbers: " << numsSum << std::endl;
  outputFile << "Product of numbers: " << numsProduct << std::endl;

  outputFile.close();
}

int main()
{
  int a, b, c;
  std::cout << "Enter three whole numbers: ";
  std::cin >> a >> b >> c;

  const char *outputFileName = "outputFile.txt";

  writeNumsCalcToFile(outputFileName, a, b, c);

  return 0;
}