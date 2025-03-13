// Във файл numbers.txt са записани число N, последвано от N цели числа.Прочетете файла и запишете числата след N в динамичен масив.

#include <iostream>
#include <fstream>

int main()
{

  std::ifstream inFile("numbers.txt");

  if (!inFile.is_open())
  {
    std::cout << "Couldn't open file...";
    return -1;
  }

  int N;
  inFile >> N;
  std::cout << "First num: " << N << std::endl;

  if (N <= 0)
  {
    std::cout << "No numbers in the file ...";
    return -2;
  }

  int *nums = new int[N];

  int num, index = 0;
  while (inFile >> num)
  {
    nums[index++] = num;
  }

  for (size_t i = 0; i < N; i++)
  {
    std::cout << nums[i] << " ";
  }

  delete[] nums;

  return 0;
}