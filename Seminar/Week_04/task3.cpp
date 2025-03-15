// Прочитаме текстов файл X.txt. В него се съдържат забранени думи, които не искаме да се появяват повече и искаме да ги заменим с други "позволени" такива. Тези думи могат да бъдат прочетени от файл Y като на всеки ред ще се съдържат по 2 думи, забранената и тази, с която ще я замести. Като резултат искаме да генерираме нов файл X-censored.txt в който се съдържна новия по-добър текст. X и Y се четат от стандартния вход.

// Можем да приемем, че няма дума по-дълга от 50 символа, както и че думите са разделени с " ".

// *Искаме пълна проверка на входните данни.

#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable : 4996)

bool validateFileName(const char *fileName)
{
  const char *FORBIDDEN = "?*\"<>";

  while (*fileName != '\0')
  {
    for (int i = 0; FORBIDDEN[i] != '\0'; i++)
    {
      if (*fileName == FORBIDDEN[i])
        return false;
    }

    fileName++;
  }

  return true;
}

int main()
{
  char originalTextFileName[256];
  std::cin >> originalTextFileName;
  if (!validateFileName(originalTextFileName))
  {
    std::cout << "Failed to validate file name: " << originalTextFileName;
    return -1;
  }

  char censorListFileName[256];
  std::cin >> censorListFileName;
  if (!validateFileName(censorListFileName))
  {
    std::cout << "Failed to validate file name: " << censorListFileName;
    return -2;
  }

  std::ifstream inCensorList(censorListFileName);
  if (!inCensorList.is_open())
  {
    std::cout << "File does not exist...";
    return -3;
  }

  char badWords[16][51];
  char goodWords[16][51];

  int count = 0;

  while (inCensorList >> badWords[count] >> goodWords[count])
  {
    count++;
  }
  inCensorList.close();

  int newFileNameSize = strlen(originalTextFileName) + strlen("-censored");
  char *newFileName = new char[newFileNameSize + 1]{};
  strncat(newFileName, originalTextFileName, strlen(originalTextFileName) - 4);
  strcat(newFileName, "-censored.txt");

  std::ofstream outModifiedText(newFileName);
  if (!outModifiedText.is_open())
  {
    delete[] newFileName;
    std::cout << "Could not open file";
    return -4;
  }

  std::ifstream inOriginalText(originalTextFileName);
  if (!inOriginalText.is_open())
  {
    delete[] newFileName;
    std::cout << "File does not exist...";
    return -5;
  }

  char buffer[51];
  while (!inOriginalText.eof())
  {
    inOriginalText >> buffer;

    bool foundBadWord = false;
    for (int i = 0; i < count; i++)
    {
      if (strcmp(buffer, badWords[i]) == 0)
      {
        foundBadWord = true;
        outModifiedText << goodWords[i] << " ";
      }
    }

    if (!foundBadWord)
    {
      outModifiedText << buffer << " ";
    }
  }

  delete[] newFileName;
}