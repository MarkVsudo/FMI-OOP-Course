// Напишете структура Item, която да има полета за

// price
// quantity
// Създайте масив от обекти.

// Изведете:

// - общата сума на всички предмети
// - количеството на най-скъпия предмет

#include <iostream>

struct Item
{
  double price;
  unsigned quantity;
};

double sumOfItems(Item items[], unsigned size)
{
  double result = 0;

  for (unsigned i = 0; i < size; i++)
  {
    result += items[i].price * items[i].quantity;
  }

  return result;
}

unsigned amountPriciestItem(Item items[], unsigned size)
{
  unsigned index = 0;

  for (unsigned i = 1; i < size; i++)
  {
    if (items[i].price > items[index].price)
      index = i;
  }

  return items[index].quantity;
}

int main()
{
  Item items[3];

  items[0] = {2.50, 5};
  items[1] = {20, 3};
  items[2] = {7.50, 7};

  std::cout << sumOfItems(items, 3) << "\n";
  std::cout << amountPriciestItem(items, 3) << "\n";

  return 0;
}