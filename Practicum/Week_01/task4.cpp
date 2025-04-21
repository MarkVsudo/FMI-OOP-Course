#include <iostream>

enum Drink
{
  WHISKEY = 1 << 0, // 00000001
  VODKA = 1 << 1,   // 00000010
  COLA = 1 << 2,    // 00000100
  FANTA = 1 << 3,   // 00001000
  WATER = 1 << 4,   // 00010000
  WINE = 1 << 5,    // 00100000
  RUM = 1 << 6,     // 01000000
  JUICE = 1 << 7    // 10000000
};

bool likesDrink(unsigned char preferences, Drink drink)
{
  return (preferences & drink) != 0;
}

void addDrink(unsigned char &preferences, Drink drink)
{
  preferences |= drink;
}

void removeDrink(unsigned char &preferences, Drink drink)
{
  preferences &= ~drink;
}

void printLikedDrinks(unsigned char preferences)
{
  std::cout << "Liked drinks: ";
  if (likesDrink(preferences, WHISKEY))
    std::cout << "Whiskey, ";
  if (likesDrink(preferences, VODKA))
    std::cout << "Vodka, ";
  if (likesDrink(preferences, COLA))
    std::cout << "Coke, ";
  if (likesDrink(preferences, FANTA))
    std::cout << "Fanta, ";
  if (likesDrink(preferences, WATER))
    std::cout << "Water, ";
  if (likesDrink(preferences, WINE))
    std::cout << "Wine, ";
  if (likesDrink(preferences, RUM))
    std::cout << "Rum, ";
  if (likesDrink(preferences, JUICE))
    std::cout << "Juice, ";
  std::cout << std::endl;
}

int main()
{
  unsigned char preferences = 0b00000000;

  addDrink(preferences, WHISKEY);
  addDrink(preferences, COLA);
  addDrink(preferences, WATER);

  printLikedDrinks(preferences);

  std::cout << "Likes whiskey? " << (likesDrink(preferences, WHISKEY) ? "Yes" : "No") << std::endl;
  std::cout << "Likes vodka? " << (likesDrink(preferences, VODKA) ? "Yes" : "No") << std::endl;

  removeDrink(preferences, COLA);
  printLikedDrinks(preferences);

  return 0;
}