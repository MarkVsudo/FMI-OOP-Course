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
#include "fruit.h"

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