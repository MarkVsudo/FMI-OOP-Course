#include "fruit.h"
#include <iostream>

const char *FRUIT_COLORS[5] = {
    "Brown",
    "Green",
    "Orange",
    "Red",
    "Yellow"};

void readFruitData(Fruit &fruit)
{
  std::cout << "Fruit name: ";
  std::cin.ignore();
  std::cin.getline(fruit.name, 32);

  int colorOption;
  do
  {
    std::cout << "Fruit color (1 - 5): " << std::endl;
    std::cout << "1 -> Brown\n2 -> Green\n3 -> Orange\n4 -> Red\n5 -> Yellow\n";
    std::cin >> colorOption;
  } while (colorOption < 1 || colorOption > 5);
  fruit.cl = (Color)colorOption;

  int isAnnual;
  do
  {
    std::cout << "Annual fruit (YES -> 1 | NO -> 0): ";
    std::cin >> isAnnual;
  } while (isAnnual != 0 && isAnnual != 1);
  fruit.annual = (YN)isAnnual;

  if (isAnnual == 1)
  {
    fruit.perennial = YN::NO;
  }
  else
  {
    fruit.perennial = YN::YES;
  }

  int isTropical;
  do
  {
    std::cout << "Tropical fruit (YES -> 1 | NO -> 0): ";
    std::cin >> isTropical;
  } while (isTropical != 0 && isTropical != 1);
  fruit.tropical = (YN)isTropical;
}

void printFruitsData(const Fruit *fruits, const unsigned size)
{
  for (unsigned i = 0; i < size; i++)
  {
    std::cout << "-- Fruit " << i + 1 << " --" << std::endl;
    std::cout << "Fruit name: " << fruits[i].name << std::endl;
    std::cout << "Fruit color: " << FRUIT_COLORS[fruits[i].cl - 1] << std::endl;
    std::cout << "Annual fruit: " << (fruits[i].annual == 1 ? "Yes" : "No") << std::endl;
    std::cout << "Perennial fruit: " << (fruits[i].perennial == 1 ? "Yes" : "No") << std::endl;
    std::cout << "Tropical fruit: " << (fruits[i].tropical == 1 ? "Yes" : "No") << std::endl;
  }
}
// б) сортира по име, цвят и продължителност на плододаване плодовете, зададени чрез масива;

// Sorting criteria priority: name -> colour (if names are the same) -> fruits duration (if names and colours are the same)

void swapFruits(Fruit &fruit1, Fruit &fruit2)
{
  Fruit temp = fruit1;
  fruit1 = fruit2;
  fruit2 = temp;
}

void sortFruits(Fruit *fruits, const unsigned size)
{
  for (unsigned i = 0; i < size - 1; i++)
  {
    for (unsigned j = 0; j < size - i - 1; j++)
    {
      unsigned k = 0;
      while (fruits[j].name[k] != '\0' && fruits[j + 1].name[k] != '\0' && fruits[j].name[k] == fruits[j + 1].name[k])
      {
        k++;
      }

      if (fruits[j].name[k] > fruits[j + 1].name[k])
      {
        swapFruits(fruits[j], fruits[j + 1]);
      }
      else if (fruits[j].name[k] == fruits[j + 1].name[k] && fruits[j].cl > fruits[j + 1].cl)
      {
        swapFruits(fruits[j], fruits[j + 1]);
      }
      else if (fruits[j].name[k] == fruits[j + 1].name[k] && fruits[j].cl == fruits[j + 1].cl)
      {
        short duration_j = (fruits[j].annual == YN::YES) ? 0 : 1;
        short duration_j1 = (fruits[j + 1].annual == YN::YES) ? 0 : 1;

        if (duration_j > duration_j1)
        {
          swapFruits(fruits[j], fruits[j + 1]);
        }
      }
    }
  }
}

// perennial, tropical, with colour, descending by name
Fruit *getFruitsByCriteria(const Fruit *fruits, const unsigned size, const Color chosenColor, unsigned &fruitsMeetingCriteriaCount)
{
  fruitsMeetingCriteriaCount = 0;

  for (unsigned i = 0; i < size; i++)
  {
    if (fruits[i].perennial && fruits[i].tropical && fruits[i].cl == chosenColor)
    {
      fruitsMeetingCriteriaCount++;
    }
  }

  if (fruitsMeetingCriteriaCount == 0)
  {
    return nullptr;
  }

  Fruit *fruitsMeetingCriteria = new Fruit[fruitsMeetingCriteriaCount];

  for (unsigned i = 0, j = 0; i < size && j < fruitsMeetingCriteriaCount; i++)
  {
    if (fruits[i].perennial && fruits[i].tropical && fruits[i].cl == chosenColor)
    {
      fruitsMeetingCriteria[j++] = fruits[i];
    }
  }

  // sort by name in descending order
  for (unsigned i = 0; i < fruitsMeetingCriteriaCount - 1; i++)
  {
    for (unsigned j = 0; j < fruitsMeetingCriteriaCount - i - 1; j++)
    {
      unsigned k = 0;
      while (fruitsMeetingCriteria[j].name[k] != '\0' && fruitsMeetingCriteria[j + 1].name[k] != '\0' && fruitsMeetingCriteria[j].name[k] == fruitsMeetingCriteria[j + 1].name[k])
      {
        k++;
      }

      if (fruitsMeetingCriteria[j].name[k] < fruitsMeetingCriteria[j + 1].name[k])
      {
        swapFruits(fruitsMeetingCriteria[j], fruitsMeetingCriteria[j + 1]);
      }
    }
  }

  return fruitsMeetingCriteria;
}