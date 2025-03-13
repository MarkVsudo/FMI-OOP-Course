// Напишете програма, която отпечатва на екрана собствения си код.
#include <iostream>
#include <fstream>

int main()
{
  std::ifstream inFile("task1.cpp");

  if (!inFile)
  {
    std::cerr << "Couldn't open file..." << std::endl;
    return -1;
  }

  char buffer[1024];

  while (inFile.getline(buffer, sizeof(buffer)))
  {
    std::cout << buffer << std::endl;
  }

  inFile.close();

  return 0;
}
