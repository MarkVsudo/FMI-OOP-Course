#include <iostream>
#include <fstream>
#include <cstring>

class Game
{
public:
  void setTitle(const char *title)
  {
    strncpy(this->title, title, sizeof(this->title) - 1);
    this->title[sizeof(this->title) - 1] = '\0';
  }

  void setPrice(double price)
  {
    this->price = (price < 0) ? 0 : price;
  }

  void setAvailability(bool isAvailable)
  {
    this->isAvailable = isAvailable;
  }

  const char *getTitle() const
  {
    return title;
  }

  double getPrice() const
  {
    return price;
  }

  bool getAvailability() const
  {
    return isAvailable;
  }

  bool isFree() const
  {
    const double EPSILON = 1e-9;
    return (price >= -EPSILON && price <= EPSILON);
  }

  void print() const
  {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "Available: " << std::boolalpha << isAvailable << std::endl;
  }

  void saveToFile(std::ofstream &outFile) const
  {
    outFile << title << "\n"
            << price << "\n"
            << isAvailable << "\n";
  }

private:
  char title[64];
  double price;
  bool isAvailable;
};

class GamePlatform
{
public:
  GamePlatform() : size(0) {}

  void addGame()
  {
    if (size == MAX_GAMES)
    {
      std::cout << "You've reached the limit of games!" << std::endl;
      return;
    }

    Game newGame;
    char title[64];
    double price;
    bool isAvailable;

    std::cout << "Enter title: ";
    std::cin.ignore();
    std::cin.getline(title, sizeof(title));

    std::cout << "Enter price: ";
    std::cin >> price;

    std::cout << "Is the game available? (1 -> Yes, 0 -> No): ";
    std::cin >> isAvailable;

    newGame.setTitle(title);
    newGame.setPrice(price);
    newGame.setAvailability(isAvailable);

    games[size++] = newGame;

    std::cout << "Game added!\n";
  }

  void printGameByIndex(int index) const
  {
    if (index < 0 || index >= size)
    {
      std::cout << "Invalid index!" << std::endl;
      return;
    }

    std::cout << "Game at index " << index << std::endl;
    games[index].print();
  }

  void printAllGames() const
  {
    if (size == 0)
    {
      std::cout << "No games found!" << std::endl;
    }
    else
    {
      for (int i = 0; i < size; i++)
      {
        std::cout << "-- Game " << i + 1 << " --" << std::endl;
        games[i].print();
      }
    }
  }

  void printCheapestAndPriciest() const
  {
    int cheapestIndex = 0, priciestIndex = 0;

    for (int i = 1; i < size; i++)
    {
      if (games[cheapestIndex].getPrice() > games[i].getPrice())
      {
        cheapestIndex = i;
      }
      else if (games[priciestIndex].getPrice() < games[i].getPrice())
      {
        priciestIndex = i;
      }
    }

    std::cout << "Cheapest game is at index " << cheapestIndex << std::endl;
    games[cheapestIndex].print();
    std::cout << "Priciest game is at index " << priciestIndex << std::endl;
    games[priciestIndex].print();
  }

  void printFreeGames() const
  {
    int count = 0;
    for (int i = 0; i < size; i++)
    {
      if (games[i].isFree())
      {
        games[i].print();
        count++;
      }

      if (i == size - 1 && count == 0)
      {
        std::cout << "No free games found!" << std::endl;
      }
    }
  }

  void removeGame(int index)
  {
    if (index < 0 || index >= size)
    {
      std::cout << "Invalid index!" << std::endl;
      return;
    }

    for (int i = index; i < size - 1; i++)
    {
      games[i] = games[i + 1];
    }

    size--;
    std::cout << "Game removed at index " << index << std::endl;
  }

  void saveGamePlatformToFile() const
  {
    std::ofstream binaryOutFile("gamePlatformData.dat", std::ios::binary);
    if (!binaryOutFile)
    {
      std::cerr << "Error opening binary file for writing!" << std::endl;
      return;
    }

    binaryOutFile.write((char *)games, size * sizeof(Game));
    binaryOutFile.close();

    std::ofstream txtOutFile("gamePlatformData.txt");
    if (!txtOutFile)
    {
      std::cerr << "Error opening text file for writing!" << std::endl;
      return;
    }

    for (int i = 0; i < size; i++)
    {
      games[i].saveToFile(txtOutFile);
    }
    txtOutFile.close();
  }

  // TODO: Възможност за изчитане на данните от текстов и от двоичен файл и запазване в платформата за игри.

private:
  const int MAX_GAMES = 64;
  Game games[64];
  int size;
};

int main()
{
  GamePlatform gamePlatform;

  while (true)
  {
    int option;
    std::cout << "-- Select an option from the following --\n0) Exit\n1) Add game\n2) Print game at index\n3) Print all games\n4) Print cheapest and priciest game\n5) Print free games\n6) Remove game\n7) Save game platform to files\n";
    std::cin >> option;
    switch (option)
    {
    case 0:
      std::cout << "Exiting...\n";
      return 0;
    case 1:
      gamePlatform.addGame();
      break;
    case 2:
    {
      int index;
      std::cout << "Enter an index: ";
      std::cin >> index;
      gamePlatform.printGameByIndex(index);
      break;
    }
    case 3:
      gamePlatform.printAllGames();
      break;
    case 4:
      gamePlatform.printCheapestAndPriciest();
      break;
    case 5:
      gamePlatform.printFreeGames();
      break;
    case 6:
    {
      int index;
      std::cout << "Enter an index: ";
      std::cin >> index;
      gamePlatform.removeGame(index);
      break;
    }
    case 7:
      gamePlatform.saveGamePlatformToFile();
      break;
    case 8:
      break;
    default:
      std::cout << "Invalid option!" << std::endl;
    }
  }

  return 0;
}