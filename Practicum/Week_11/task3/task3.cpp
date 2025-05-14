#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>

class Prize
{
protected:
  double price;
  int points;

public:
  Prize(double p, int pts) : price(p), points(pts) {}
  virtual ~Prize() {}

  double getPrice() const { return price; }
  int getPoints() const { return points; }

  virtual void visualize() const = 0;
};

void displayFromFile(const char *filename)
{
  std::ifstream file(filename);
  if (!file)
  {
    throw std::runtime_error("Cannot open file for visualization.");
  }

  char line[256];
  while (file.getline(line, 256))
  {
    std::cout << line << std::endl;
  }
  file.close();
}

class Penguin : public Prize
{
public:
  Penguin() : Prize(9.99, 50) {}

  void visualize() const override
  {
    displayFromFile("penguin.txt");
  }
};

class Pacman : public Prize
{
public:
  Pacman() : Prize(14.99, 150) {}

  void visualize() const override
  {
    displayFromFile("pacman.txt");
  }
};

class ComputerBoy : public Prize
{
public:
  ComputerBoy() : Prize(29.99, 500) {}

  void visualize() const override
  {
    displayFromFile("computerboy.txt");
  }
};

class Squidward : public Prize
{
public:
  Squidward() : Prize(49.99, 1000) {}

  void visualize() const override
  {
    displayFromFile("squidward.txt");
  }
};

class Sylvester : public Prize
{
public:
  Sylvester() : Prize(69.99, 1500) {}

  void visualize() const override
  {
    displayFromFile("sylvester.txt");
  }
};

int main()
{
  try
  {
    Penguin penguin;
    Pacman pacman;
    ComputerBoy cb;
    Squidward squid;
    Sylvester syl;

    std::cout << "Penguin (" << penguin.getPoints() << " pts):\n";
    penguin.visualize();
    std::cout << "\n";

    std::cout << "Pacman (" << pacman.getPoints() << " pts):\n";
    pacman.visualize();
    std::cout << "\n";

    std::cout << "ComputerBoy (" << cb.getPoints() << " pts):\n";
    cb.visualize();
    std::cout << "\n";

    std::cout << "Squidward (" << squid.getPoints() << " pts):\n";
    squid.visualize();
    std::cout << "\n";

    std::cout << "Sylvester (" << syl.getPoints() << " pts):\n";
    syl.visualize();
    std::cout << "\n";
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
