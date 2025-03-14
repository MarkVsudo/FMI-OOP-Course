// Напишете проргама, която прочита информация от даден файл и след това записва съдържанието на файла в обратен ред.
// Пример:

// input.txt:
// 12345
// 678910
// asdfgh

// output.txt:
// 54321
// 019876
// hgfdsa

#include <iostream>
#include <fstream>

unsigned getStrLength(const char *str)
{
  unsigned length = 0;
  while (str[length] != '\0')
  {
    length++;
  }
  return length;
}

void reverseStr(char *str, unsigned length)
{
  for (unsigned i = 0; i < length / 2; i++)
  {
    char temp = str[i];
    str[i] = str[length - 1 - i];
    str[length - 1 - i] = temp;
  }
}

int main()
{

  std::ifstream inFile("input.txt");

  if (!inFile)
  {
    std::cerr << "Couldn't open input file..." << std::endl;
    return -1;
  }

  std::ofstream outFile("output.txt");

  if (!outFile)
  {
    std::cerr << "Couldn't open output file..." << std::endl;
    return -2;
  }

  char buffer[1024];

  while (inFile.getline(buffer, sizeof(buffer)))
  {
    reverseStr(buffer, getStrLength(buffer));
    outFile << buffer << std::endl;
  }

  outFile.close();
  inFile.close();

  return 0;
}