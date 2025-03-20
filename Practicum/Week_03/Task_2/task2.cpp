// 2. Напишете функция, която приема име на текстов файл и принтира броя на редовете в него.

#include <iostream>
#include <fstream>

int countLines(const char *filename)
{
  std::ifstream inputFile(filename);

  if (!inputFile)
  {
    std::cerr << "Error opening file: " << filename << std::endl;
    return -1;
  }

  char buffer[256];
  unsigned count = 0;

  while (inputFile.getline(buffer, sizeof(buffer)))
  {
    count++;
  }

  return count;
}

int main()
{
  const char *filename = "text.txt";

  int lineCount = countLines(filename);
  if (lineCount >= 0)
  {
    std::cout << "Number of lines: " << lineCount << std::endl;
  }

  return 0;
}
