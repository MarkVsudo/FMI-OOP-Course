// Задача 3. Структурата Fruit, определяща плод, е дефинирана по следния начин:
// struct Fruit
// {
//   char name[32]; // име на плод
//   color cl;      // цвят на плод
//   yn annual;     // едногодишен плод
//   yn perennial;  // многогодишен плод
//   yn tropical;   // тропически плод
// };
// където:
// - color е изброен тип за цвят (напр. brown, green, orange, red, yellow и т.н.)
// - yn е изброен тип с две стойности Yes и No
// Напишете програма, която:
// а) създава едномерен масив от указатели към структури, задаващи плодове и прочита данните от клавиатурата;
// б) сортира по име, цвят и продължителност на плододаване плодовете, зададени чрез масива;
// в) извежда данните за плодовете, зададени чрез масива, след сортирането им;
// г) извежда многогодишните, тропически плодове с даден цвят, сортирани в низходящ ред по име на плода.
// За целта да се дефинират подходящи функции. Постарайте се да гарантирате коректност на данните.

#include <iostream>

enum Color
{
  BROWN = 1,
  GREEN,
  ORANGE,
  RED,
  YELLOW
};

const char *FRUIT_COLORS[5] = {
    "Brown",
    "Green",
    "Orange",
    "Red",
    "Yellow"};

enum YN
{
  YES = 1,
  NO = 0
};

struct Fruit
{
  char name[32]; // име на плод
  Color cl;      // цвят на плод
  YN annual;     // едногодишен плод
  YN perennial;  // многогодишен плод
  YN tropical;   // тропически плод
};

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

unsigned strLen(const char *str)
{
  unsigned count = 0;

  while (str[count] != '\0')
  {
    count++;
  }

  return count;
}
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

int main()
{
  unsigned n;

  do
  {
    std::cout << "Enter amount of fruits: ";
    std::cin >> n;
  } while (n < 1);

  Fruit *fruits = new Fruit[n];

  for (unsigned i = 0; i < n; i++)
  {
    std::cout << "-- Fruit " << i + 1 << " --" << std::endl;
    readFruitData(fruits[i]);
  }

  sortFruits(fruits, n);
  printFruitsData(fruits, n);

  // get perennial, tropical fruits of a given color, sorted in descending order by fruit name
  int colorOption;
  do
  {
    std::cout << "Fruit color (1 - 5): " << std::endl;
    std::cout << "1 -> Brown\n2 -> Green\n3 -> Orange\n4 -> Red\n5 -> Yellow\n";
    std::cin >> colorOption;
  } while (colorOption < 1 || colorOption > 5);

  unsigned fruitsMeetingCriteriaCount = 0;
  Fruit *fruitsMeetingCriteria = getFruitsByCriteria(fruits, n, (Color)colorOption, fruitsMeetingCriteriaCount);

  if (fruitsMeetingCriteria)
  {
    std::cout << "-- Perennial, tropical, " << FRUIT_COLORS[colorOption - 1] << " fruits sorted in descending order by fruit name --" << std::endl;
    printFruitsData(fruitsMeetingCriteria, fruitsMeetingCriteriaCount);
    delete[] fruitsMeetingCriteria;
  }
  else
  {
    std::cout << "No fruits found meeting the criteria" << std::endl;
  }

  delete[] fruits;

  return 0;
}