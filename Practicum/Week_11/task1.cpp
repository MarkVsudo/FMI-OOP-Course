#include <iostream>
#include <cstring>
#include <stdexcept>

class Vehicle
{
public:
  Vehicle() : color(nullptr), make(nullptr), year(2000), passengers(1), speed(10) {}

  Vehicle(char *color,
          char *make,
          unsigned short year,
          unsigned short passengers,
          unsigned short speed)
  {
    setColor(color);
    setMake(make);
    setYear(year);
    setPassengers(passengers);
    setSpeed(speed);
  }

  ~Vehicle()
  {
    delete[] color;
    delete[] make;
  }

  Vehicle(const Vehicle &other)
  {
    setColor(other.color);
    setMake(other.make);
    setYear(other.year);
    setPassengers(other.passengers);
    setSpeed(other.speed);
  }

  Vehicle &operator=(const Vehicle &other)
  {
    if (this != &other)
    {
      setColor(other.color);
      setMake(other.make);
      setYear(other.year);
      setPassengers(other.passengers);
      setSpeed(other.speed);
    }

    return *this;
  }

  void setColor(const char *color)
  {
    if (this->color)
    {
      delete[] this->color;
    }
    size_t colorSize = strlen(color);
    this->color = new char[colorSize + 1];
    strcpy(this->color, color);
    this->color[colorSize] = '\0';
  }

  void setMake(const char *make)
  {
    if (this->make)
    {
      delete[] this->make;
    }
    size_t makeSize = strlen(make);
    this->make = new char[makeSize + 1];
    strcpy(this->make, make);
    this->make[makeSize] = '\0';
  }

  void setYear(unsigned short year)
  {
    this->year = year;
  }

  void setPassengers(unsigned short passengers)
  {
    if (passengers < 1)
      throw std::invalid_argument("Passangers cannot be less than 1");

    this->passengers = passengers;
  }

  void setSpeed(unsigned short speed)
  {
    if (speed < 10)
      throw std::invalid_argument("Top speed cannot be less than 10");

    this->speed = speed;
  }

  const char *getColor() const { return color; }
  const char *getMake() const { return make; }
  unsigned short getYear() const { return year; }
  unsigned short getPassengers() const { return passengers; }
  unsigned short getSpeed() const { return speed; }

private:
  char *color;
  char *make;
  unsigned short year;
  unsigned short passengers;
  unsigned short speed;
};

class Bicycle : public Vehicle
{
public:
private:
  unsigned short gears;
  bool lights;
  bool ring;
};

class Car : public Vehicle
{
public:
private:
  char *model;
  unsigned short doors;
  unsigned short power;
};

int main()
{

  return 0;
}