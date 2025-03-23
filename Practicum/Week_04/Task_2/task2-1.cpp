// записване на масив от цели числа в двоичен файл

#include <iostream>
#include <fstream>

int main()
{
  // записване на масив от цели числа в двоичен файл
  int nums[5] = {1, 2, 3, 4, 5};

  std::ofstream numbersArrayOutputFile("numbersArray.bin", std::ios::binary);
  if (!numbersArrayOutputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return -1;
  }
  numbersArrayOutputFile.write((char *)(nums), sizeof(nums));
  numbersArrayOutputFile.close();

  std::ifstream numbersArrayInputFile("numbersArray.bin", std::ios::binary);
  if (!numbersArrayInputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return -2;
  }
  numbersArrayInputFile.read((char *)(nums), sizeof(nums));
  numbersArrayInputFile.close();

  for (int i = 0; i < 5; i++)
  {
    std::cout << nums[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
