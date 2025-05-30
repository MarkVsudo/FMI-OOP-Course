#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

class Car
{
public:
  Car() : name(nullptr), power(0), thisId(++ID) {}

  Car(const char *name, unsigned power)
      : name(nullptr), thisId(++ID)
  {
    setName(name);
    setPower(power);
  }

  ~Car()
  {
    delete[] name;
  }

  Car(const Car &other) : name(nullptr)
  {
    this->thisId = other.thisId;
    setName(other.name);
    setPower(other.power);
  }

  Car &operator=(const Car &other)
  {
    if (this != &other)
    {
      this->thisId = other.thisId;
      setName(other.name);
      setPower(other.power);
    }

    return *this;
  }

  void print() const
  {
    std::cout << "ID: " << thisId << std::endl;
    std::cout << "Name: " << (name ? name : "Unknown") << std::endl;
    std::cout << "Power: " << power << std::endl;
  }

  void setName(const char *name)
  {
    if (name)
    {
      delete[] this->name;
      size_t len = strlen(name);
      this->name = new char[len + 1];
      strcpy(this->name, name);
      this->name[len] = '\0';
    }
  }

  void setPower(unsigned power)
  {
    if (power < 0)
      throw std::invalid_argument("Power cannot be less than 0");

    this->power = power;
  }

  const char *getName() const { return name; }
  unsigned getPower() const { return power; }

  static int ID;

private:
  char *name;
  unsigned power;
  int thisId;
};

int Car::ID = -1;

class CarOwner
{
public:
  CarOwner() : carID(-1), numberPlate(0)
  {
    name[0] = '\0';
  }

  CarOwner(const char *ownerName, int carID, unsigned short numberPlate)
  {
    setName(ownerName);
    this->carID = carID;
    this->numberPlate = numberPlate;
  }

  void setName(const char *ownerName)
  {
    strncpy(name, ownerName, 23);
    name[23] = '\0';
  }

  const char *getName() const { return name; }
  int getCarID() const { return carID; }
  unsigned short getNumberPlate() const { return numberPlate; }

private:
  char name[24];
  int carID;
  unsigned short numberPlate;
};

class CarDB
{
public:
  CarDB() : size(0), capacity(2), carCount(0), carCap(4)
  {
    owners = new CarOwner[capacity];
    cars = new Car *[carCap];
  }

  ~CarDB()
  {
    delete[] owners;
    for (int i = 0; i < carCount; ++i)
      delete cars[i];
    delete[] cars;
  }

  void addCar(const Car &car)
  {
    if (carCount == carCap)
      expandCars();

    cars[carCount++] = new Car(car);
  }

  void addOwner(const char *name, int carID, unsigned short plate)
  {
    if (!isValidCarID(carID))
    {
      std::cout << "Invalid car ID.\n";
      return;
    }

    if (isNumberPlateTaken(plate))
    {
      std::cout << "Error: Number plate already exists.\n";
      return;
    }

    if (size == capacity)
    {
      expand();
    }

    owners[size++] = CarOwner(name, carID, plate);
  }

  void listOwners() const
  {
    for (int i = 0; i < size; ++i)
    {
      std::cout << "Owner: " << owners[i].getName()
                << ", Car ID: " << owners[i].getCarID()
                << ", Plate: " << owners[i].getNumberPlate()
                << std::endl;
    }
  }

  void generateReport()
  {
    std::ofstream out("car-report.txt");
    if (!out.is_open())
    {
      std::cerr << "Failed to open file for report." << std::endl;
      return;
    }

    // 1. Най-популярна кола
    const int MAX_CARS = 1024;
    int carOwnerCounts[MAX_CARS] = {0}; // индекс = carID, стойност = брой притежатели

    for (int i = 0; i < size; ++i)
    {
      int id = owners[i].getCarID();
      if (id >= 0 && id < MAX_CARS)
        carOwnerCounts[id]++;
    }

    int mostPopularCarID = -1;
    int mostPopularCount = 0;
    for (int i = 0; i < carCount; ++i)
    {
      if (carOwnerCounts[i] > mostPopularCount)
      {
        mostPopularCount = carOwnerCounts[i];
        mostPopularCarID = i;
      }
    }

    if (mostPopularCarID != -1 && cars[mostPopularCarID])
      out << "Най-популярна кола: " << cars[mostPopularCarID]->getName() << "\n";
    else
      out << "Най-популярна кола: няма данни\n";

    // 2. Средна мощност на всички притежавани коли
    int totalPower = 0;
    int uniqueUsedCarIDs[MAX_CARS] = {-1};
    int usedCarCount = 0;

    for (int i = 0; i < size; ++i)
    {
      int id = owners[i].getCarID();
      bool alreadyCounted = false;
      for (int j = 0; j < usedCarCount; ++j)
      {
        if (uniqueUsedCarIDs[j] == id)
        {
          alreadyCounted = true;
          break;
        }
      }
      if (!alreadyCounted && id >= 0 && id < carCount)
      {
        uniqueUsedCarIDs[usedCarCount++] = id;
        totalPower += cars[id]->getPower();
      }
    }

    double avgPower = usedCarCount > 0 ? (double)totalPower / usedCarCount : 0.0;
    out << "Средна мощност: " << avgPower << "\n";

    // 3. Списък на собственици с обща мощност
    for (int i = 0; i < size; ++i)
    {
      int id = owners[i].getCarID();
      if (id >= 0 && id < carCount && cars[id])
      {
        out << owners[i].getName() << " - " << cars[id]->getPower() << "\n";
      }
    }

    out.close();
  }

private:
  CarOwner *owners;
  int size;
  int capacity;
  Car **cars;
  int carCount;
  int carCap;

  bool isNumberPlateTaken(unsigned short plate) const
  {
    for (int i = 0; i < size; ++i)
      if (owners[i].getNumberPlate() == plate)
        return true;
    return false;
  }

  bool isValidCarID(int id) const
  {
    return id >= 0 && id <= Car::ID;
  }

  // Car *mostPopularCar() const
  // {
  //   const int arrLen = size;
  //   int foundCar[arrLen] = {0};
  //   for (int i = 0; i < size; ++i)
  //   {
  //   }
  // }

  int avgPower() const
  {
    if (!owners)
    {
      std::cout << "No cars registered to calculate average power!" << std::endl;
      return 0;
    }

    int power = 0;
    for (int i = 0; i < size; ++i)
    {
      // if(owners[i].getCarID() == )
    }
    return power;
  }

  void expand()
  {
    capacity *= 2;
    CarOwner *newArr = new CarOwner[capacity];
    for (int i = 0; i < size; ++i)
      newArr[i] = owners[i];
    delete[] owners;
    owners = newArr;
  }

  void expandCars()
  {
    carCap *= 2;
    Car **newCars = new Car *[carCap];

    for (int i = 0; i < carCount; ++i)
      newCars[i] = cars[i];

    delete[] cars;
    cars = newCars;
  }
};

int main()
{
  try
  {
    Car car1("Lamborgini Murcielago", 670);
    Car car2("Mercedes-AMG", 503);
    Car car3("Pagani Zonda R", 740);
    Car car4("Bugatti Veyron", 1020);

    car1.print();
    car2.print();
    car3.print();
    car4.print();

    std::cout << "Last id:" << Car::ID;
  }
  catch (std::exception &e)
  {
    std::cerr << "An error occurred: " << e.what() << std::endl;
  }

  return 0;
}