// Разглеждаме двоичен файл numbers.bin. В него се съдържат целочислени стойности от тип int. Искаме да върнем това число, което е най-голямото от тях.

#include <iostream>
#include <fstream>
#include <climits>

int main()
{
  std::ofstream outFile("numbers.bin", std::ios::binary);
  if (!outFile)
  {
    std::cerr << "Error opening file for writing...\n";
    return -1;
  }

  int n;
  std::cout << "Enter n: ";
  std::cin >> n;

  std::cout << "Enter " << n << " numbers: ";
  for (int i = 0; i < n; i++)
  {
    int number;
    std::cin >> number;
    outFile.write((char *)(&number), sizeof(number));
  }
  outFile.close();

  std::ifstream inFile("numbers.bin", std::ios::binary);
  if (!inFile)
  {
    std::cerr << "Error opening file for reading...\n";
    return -2;
  }

  int maxNumber = INT_MIN;
  int number;
  while (inFile.read((char *)(&number), sizeof(number)))
  {
    if (number > maxNumber)
    {
      maxNumber = number;
    }
  }

  inFile.close();
  std::cout << "The largest number is: " << maxNumber << std::endl;

  return 0;
}
