#include <iostream>

int getWordsCountStr(const char *str)
{
  int count = 0;
  bool inWord = false;

  for (int i = 0; str[i] != '\0'; i++)
  {
    if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
    {
      if (!inWord)
      {
        count++;
        inWord = true;
      }
    }
    else
    {
      inWord = false;
    }
  }

  return count;
}

int main()
{
  char str[] = "Good  morning,     Vietnam!";

  std::cout << getWordsCountStr(str);

  return 0;
}
