#include <iostream>
#include <cstring>
#include <stdexcept>

class Vehicle
{
public:
  Vehicle() : color(nullptr), make(nullptr), year(2000), passengers(1), speed(10) {}

  Vehicle(const char *color,
          const char *make,
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

  virtual ~Vehicle()
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
  Bicycle()
      : Vehicle(), gears(1), lights(false), ring(false) {}

  Bicycle(const char *color, const char *make,
          unsigned short year, unsigned short passengers, unsigned short speed,
          unsigned short gears, bool lights, bool ring)
      : Vehicle(color, make, year, passengers, speed)
  {
    setGears(gears);
    this->lights = lights;
    this->ring = ring;
  }

  Bicycle(const Bicycle &other)
      : Vehicle(other)
  {
    this->gears = other.gears;
    this->lights = other.lights;
    this->ring = other.ring;
  }

  Bicycle &operator=(const Bicycle &other)
  {
    if (this != &other)
    {
      Vehicle::operator=(other);
      this->gears = other.gears;
      this->lights = other.lights;
      this->ring = other.ring;
    }
    return *this;
  }

  ~Bicycle() override = default;

  void setGears(unsigned short gears)
  {
    if (gears < 1)
      throw std::invalid_argument("Bicycle must have at least 1 gear");
    this->gears = gears;
  }

  void setLights(bool hasLights) { this->lights = hasLights; }
  void setRing(bool hasRing) { this->ring = hasRing; }

  unsigned short getGears() const { return gears; }
  bool hasLights() const { return lights; }
  bool hasRing() const { return ring; }

private:
  unsigned short gears;
  bool lights;
  bool ring;
};

class Car : public Vehicle
{
public:
  Car() : Vehicle(), model(nullptr), doors(0), power(0) {}

  Car(const char *color, const char *make, unsigned short year, unsigned short passengers, unsigned short speed, const char *model, unsigned short doors, unsigned short power) : Vehicle(color, make, year, passengers, speed)
  {
    setModel(model);
    this->doors = doors;
    this->power = power;
  }

  ~Car() override
  {
    delete[] model;
  };

  Car(const Car &other) : Vehicle(other)
  {
    setModel(other.model);
    this->doors = other.doors;
    this->power = other.power;
  }

  Car &operator=(const Car &other)
  {
    if (this != &other)
    {
      Vehicle::operator=(other);
      setModel(other.model);
      this->doors = other.doors;
      this->power = other.power;
    }
    return *this;
  }

  void setModel(const char *model)
  {
    if (this->model)
    {
      delete[] this->model;
    }
    size_t modelSize = strlen(model);
    this->model = new char[modelSize + 1];
    strcpy(this->model, model);
    this->model[modelSize] = '\0';
  }

  void setDoors(unsigned short doors)
  {
    this->doors = doors;
  }

  void setPower(unsigned short power)
  {
    this->power = power;
  }

private:
  char *model;
  unsigned short doors;
  unsigned short power;
};

int main()
{

  return 0;
}