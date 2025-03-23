// прочитане на двоичен файл с цели числа и да се съхрани в подходящ масив
#include <iostream>
#include <fstream>

int main()
{
  int nums[] = {1, 2, 3, 4, 5};

  std::ofstream numbersOutputFile("numbers.bin", std::ios::binary);
  if (!numbersOutputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return -3;
  }
  numbersOutputFile.write((char *)(nums), sizeof(nums));
  numbersOutputFile.close();

  std::ifstream numbersInputFile("numbers.bin", std::ios::binary | std::ios::ate);
  if (!numbersInputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return -4;
  }

  size_t numbersFileSize = numbersInputFile.tellg();
  size_t arrSize = numbersFileSize / sizeof(int);

  int *numsArrFromFile = new int[arrSize];

  numbersInputFile.seekg(0);
  numbersInputFile.read((char *)(numsArrFromFile), numbersFileSize);
  numbersInputFile.close();

  if (!numbersInputFile)
  {
    std::cerr << "Error reading file!" << std::endl;
    delete[] numsArrFromFile;
    return -5;
  }

  for (size_t i = 0; i < arrSize; i++)
  {
    std::cout << numsArrFromFile[i] << " ";
  }
  std::cout << std::endl;

  delete[] numsArrFromFile;

  return 0;
}
