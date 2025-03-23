// Напишете програма, която приема файл и показва каква е големината му.

#include <iostream>
#include <fstream>

int main()
{
  std::ifstream inputFile("data.txt", std::ios::binary | std::ios::ate);

  if (!inputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return 1;
  }

  size_t fileSize = inputFile.tellg();
  inputFile.close();

  std::cout << "File size: " << fileSize << " bytes" << std::endl;

  return 0;
}
