#include <iostream>
#include <cstring>

class Game
{
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

private:
  char title[64];
  double price;
  bool isAvailable;
};

int main()
{

  return 0;
}