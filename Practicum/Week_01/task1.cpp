#include <iostream>

char *getNumsFromStr(const char *str)
{
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] >= '0' && str[i] <= '9')
    {
      count++;
    }
  }

  char *newStr = new char[count + 1];

  int index = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] >= '0' && str[i] <= '9')
    {
      newStr[index++] = str[i];
    }
  }

  newStr[index] = '\0';

  return newStr;
}

int main()
{
  char str[] = ")Lso!c6d%9ucpB*CED5su2DH%&7t4)*";

  char *newStr = getNumsFromStr(str);

  std::cout << newStr;

  delete[] newStr;

  return 0;
}