// Напишете функция, която приема символен низ и връща броя на думите в него. (Думите са разделени с произволен брой интервали, табулации и препинателни знаци)
// Пример:
// Вход:

//   Good  morning,     Vietnam!
// Изход:

// 3

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
