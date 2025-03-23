// извличане n-то число от двоичен файл, като двоичния файл не се зарежда в паметта (гарантирано е, че n < броя на числата)

#include <iostream>
#include <fstream>

int main()
{
  int size;
  std::cout << "Enter a number: ";
  std::cin >> size;
  int *nums = new int[size];

  for (int i = 0; i < size; i++)
  {
    std::cout << "nums[" << i << "] -> ";
    std::cin >> nums[i];
  }

  std::ofstream numsOutputFile("numbers.bin", std::ios::binary);
  if (!numsOutputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    delete[] nums;
    return -1;
  }

  numsOutputFile.write((char *)(nums), size * sizeof(int));
  numsOutputFile.close();
  delete[] nums;

  std::ifstream numsInputFile("numbers.bin", std::ios::binary);
  if (!numsInputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return -2;
  }

  int n;
  std::cout << "Enter a number between 1 and " << size << ": ";
  std::cin >> n;

  numsInputFile.seekg((n - 1) * sizeof(nums[0]));

  int nthNumber;

  numsInputFile.read((char *)(&nthNumber), sizeof(nthNumber));

  numsInputFile.close();

  std::cout << "Number " << n << " is -> " << nthNumber;

  return 0;
}
