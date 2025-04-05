#include "utils.h"
#include <iostream>
#include <cstdlib>

unsigned getStrLength(const char *str)
{
  unsigned count = 0;

  while (str[count] != '\0')
  {
    count++;
  }

  return count;
}

unsigned randNum(unsigned min, unsigned max)
{
  return min + (rand() % (max - min + 1));
}