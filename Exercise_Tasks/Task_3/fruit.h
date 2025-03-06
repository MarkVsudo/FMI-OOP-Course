#pragma once

enum Color
{
  BROWN = 1,
  GREEN,
  ORANGE,
  RED,
  YELLOW
};

extern const char *FRUIT_COLORS[5];

enum YN
{
  YES = 1,
  NO = 0
};

struct Fruit
{
  char name[32];
  Color cl;
  YN annual;
  YN perennial;
  YN tropical;
};

void readFruitData(Fruit &fruit);

void printFruitsData(const Fruit *fruits, const unsigned size);

void swapFruits(Fruit &fruit1, Fruit &fruit2);

void sortFruits(Fruit *fruits, const unsigned size);

Fruit *getFruitsByCriteria(const Fruit *fruits, const unsigned size, const Color chosenColor, unsigned &fruitsMeetingCriteriaCount);