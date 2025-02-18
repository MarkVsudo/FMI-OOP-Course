#include <iostream>

void fillArr(int *arr, int length)
{
  for (int i = 0; i < length; i++)
  {
    std::cout << "arr[" << i << "]: ";
    std::cin >> arr[i];
  }
}

void printArr(int *arr, int length)
{
  for (int i = 0; i < length; i++)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int *findDivisibles(int *arr1, int *arr2, int length1, int length2, int K, int &newArrLength)
{
  newArrLength = 0;
  for (int i = 0; i < length1; i++)
    if (arr1[i] % K == 0)
      newArrLength++;

  for (int i = 0; i < length2; i++)
    if (arr2[i] % K == 0)
      newArrLength++;

  int *newArr = new int[newArrLength];

  int index = 0;
  for (int i = 0; i < length1; i++)
    if (arr1[i] % K == 0)
      newArr[index++] = arr1[i];

  for (int i = 0; i < length2; i++)
    if (arr2[i] % K == 0)
      newArr[index++] = arr2[i];

  return newArr;
}

int main()
{
  int length1, length2;

  std::cout << "Enter lengths for array 1 and array 2: ";
  std::cin >> length1 >> length2;

  int *arr1 = new int[length1];
  int *arr2 = new int[length2];

  fillArr(arr1, length1);
  fillArr(arr2, length2);

  int K;
  std::cout << "Enter a number: ";
  std::cin >> K;

  int newArrLength = 0;
  int *newArr = findDivisibles(arr1, arr2, length1, length2, K, newArrLength);

  printArr(newArr, newArrLength);

  delete[] arr1;
  delete[] arr2;
  delete[] newArr;

  return 0;
}
