#include <iostream>
#include <cstring>
#include <fstream>
// #include <stdexcept>
#pragma warning(disable : 4996)

class User
{
public:
  User() : username(nullptr), license("1234567890"), age(19)
  {
  }

  User(const char *username, const char *license, unsigned age)
  {
    setUsername(username);
    setLicense(license);
    setAge(age);
  }

  User(const User &other)
  {
    setUsername(other.username);
    setLicense(other.license);
    age = other.age;
  }

  User &operator=(const User &other)
  {
    if (this != &other)
    {
      setUsername(other.username);
      setLicense(other.license);
      age = other.age;
    }
    return *this;
  }

  ~User()
  {
    delete[] username;
  }

  void printUser() const
  {
    std::cout << "Username: " << username << std::endl;
    std::cout << "License: " << license << std::endl;
    std::cout << "Age: " << age << std::endl;
  }

  void writeToStream(std::ostream &os) const
  {
    size_t nameLen = strlen(username);
    os.write((const char *)(&nameLen), sizeof(nameLen)); // записваме дължина
    os.write(username, nameLen);                         // записваме самия username

    os.write(license, 10);                       // записваме 10 символа от лиценза
    os.write((const char *)(&age), sizeof(age)); // записваме възраст
  }

  void readFromStream(std::istream &is)
  {
    size_t nameLen = 0;
    is.read((char *)(&nameLen), sizeof(nameLen));

    char *tempUsername = new char[nameLen + 1];
    is.read(tempUsername, nameLen);
    tempUsername[nameLen] = '\0';
    setUsername(tempUsername);
    delete[] tempUsername;

    char tempLicense[11] = {};
    is.read(tempLicense, 10);
    tempLicense[10] = '\0'; // just in case
    setLicense(tempLicense);

    unsigned tempAge;
    is.read((char *)(&tempAge), sizeof(tempAge));
    setAge(tempAge);
  }

  const char *getUsername() const
  {
    return username;
  }

  const char *getLicense() const
  {
    return license;
  }

  unsigned getAge() const
  {
    return age;
  }

  void setUsername(const char *username)
  {
    if (!username)
      return;

    delete[] this->username;

    unsigned len = strlen(username) + 1;
    this->username = new char[len];
    strncpy(this->username, username, len - 1);
    this->username[len - 1] = '\0';
  }

  void setLicense(const char *license)
  {
    if (strlen(license) != 10)
    {
      throw std::invalid_argument("License must be exactly 10 characters.");
    }
    strncpy(this->license, license, 10);
    this->license[10] = '\0';
  }

  void setAge(unsigned age)
  {
    if (age < 18)
    {
      throw std::invalid_argument("Age must be 18 or older.");
    }
    this->age = age;
  }

private:
  char *username;
  char license[11];
  unsigned age;
};

class RentableCar
{
public:
  RentableCar() : RentableCar(150, 50)
  {
  }

  RentableCar(unsigned horsePowers, unsigned fuelCapacity)
      : id(idCounter++), horsePowers(horsePowers), fuelCapacity(fuelCapacity), renter(nullptr)
  {
  }

  // ✅ Copy constructor
  RentableCar(const RentableCar &other)
      : id(idCounter++), // give it a new unique ID
        horsePowers(other.horsePowers),
        fuelCapacity(other.fuelCapacity),
        renter(other.renter)
  {
  }

  // ✅ Assignment operator
  RentableCar &operator=(const RentableCar &other)
  {
    if (this != &other)
    {
      // don't copy the ID; keep the original one
      horsePowers = other.horsePowers;
      fuelCapacity = other.fuelCapacity;
      renter = other.renter;
    }
    return *this;
  }

  RentableCar(const RentableCar &other)
      : id(idCounter++),
        horsePowers(other.horsePowers),
        fuelCapacity(other.fuelCapacity),
        renter(other.renter)
  {
  }

  RentableCar &operator=(const RentableCar &other)
  {
    if (this != &other)
    {
    }

    return *this;
  }

  ~RentableCar()
  {
  }

  bool isRented() const
  {
    return renter != nullptr;
  }

  void rent(const User *renter)
  {
    if (!renter)
    {
      throw std::invalid_argument("Renter cannot be nullptr");
    }

    if (isRented())
    {
      throw std::logic_error("Cannot rent already rented car");
    }

    this->renter = renter;
  }

  unsigned returnToDealer()
  {
    if (!isRented())
    {
      throw std::logic_error("Cannot return unrented car");
    }

    unsigned profit = 10 * horsePowers + 5 * fuelCapacity + 2 * renter->getAge();
    renter = nullptr;

    return profit;
  }

  void printRenter() const
  {
    if (isRented())
    {
      std::cout << "Renter of car " << id << std::endl;
      renter->printUser();
    }
    else
    {
      std::cout << "The car does not have a renter" << std::endl;
    }
  }

  void printCar() const
  {
    std::cout << "Id: " << id << std::endl;
    std::cout << "Horse power: " << horsePowers << std::endl;
    std::cout << "Fuel capacity: " << fuelCapacity << std::endl;
  }

  unsigned getId() const
  {
    return id;
  }

  unsigned getHorsePower() const
  {
    return horsePowers;
  }

  unsigned getFuelCapacity() const
  {
    return fuelCapacity;
  }

  const User *getUser() const
  {
    return renter;
  }

  void
  printId() const
  {
    std::cout << "Car ID: " << id << std::endl;
  }

private:
  static unsigned idCounter;
  unsigned id;
  unsigned horsePowers;
  unsigned fuelCapacity;
  const User *renter = nullptr;
};

unsigned RentableCar::idCounter = 0;

class CarRentalService
{
public:
  CarRentalService(unsigned cap)
      : cap(cap), size(0), profit(0), rentableCars(nullptr)
  {
  }
  CarRentalService(const CarRentalService &other)
      : cap(other.cap), size(other.size), profit(other.profit)
  {
    rentableCars = new RentableCar[cap];
    for (unsigned i = 0; i < size; ++i)
    {
      rentableCars[i] = other.rentableCars[i]; // uses RentableCar's operator=
    }
  }

  CarRentalService &operator=(const CarRentalService &other)
  {
    if (this != &other)
    {
      delete[] rentableCars;

      cap = other.cap;
      size = other.size;
      profit = other.profit;

      rentableCars = new RentableCar[cap];
      for (unsigned i = 0; i < size; ++i)
      {
        rentableCars[i] = other.rentableCars[i];
      }
    }
    return *this;
  }

  ~CarRentalService()
  {
    delete[] rentableCars;
  }

  void addCar(const RentableCar &car)
  {
    if (size == cap)
    {
      throw std::logic_error("Cannot add more cars");
    }

    RentableCar *newRentableCars = new RentableCar[size + 1];

    for (unsigned i = 0; i < size; ++i)
    {
      newRentableCars[i] = rentableCars[i];
    }

    newRentableCars[size] = car;

    delete[] rentableCars;
    rentableCars = newRentableCars;
    ++size;
  }

  void removeCar(unsigned id)
  {
    for (int i = 0; i < size; i++)
    {
      if (rentableCars[i].getId() == id && rentableCars[i].isRented())
      {
        throw std::logic_error("Cannot remove a rented car");
      }
    }

    RentableCar *newRentableCars = new RentableCar[size - 1];
    for (int i = 0, j = 0; i < size; i++)
    {
      if (rentableCars[i].getId() != id)
      {
        newRentableCars[j++] = rentableCars[i];
      }
    }

    delete[] rentableCars;
    rentableCars = newRentableCars;
    size--;
  }

  void rentCar(unsigned id, const User *renter)
  {
    for (int i = 0; i < size; i++)
    {
      if (rentableCars[i].getId() == id && rentableCars[i].isRented())
      {
        throw std::logic_error("This car is already rented");
      }
    }

    for (int i = 0; i < size; i++)
    {
      if (rentableCars[i].getId() == id && !rentableCars[i].isRented())
      {
        rentableCars[i].rent(renter);
      }
    }
  }

  RentableCar *findCar(unsigned id)
  {
    for (unsigned i = 0; i < size; ++i)
    {
      if (rentableCars[i].getId() == id)
      {
        return &rentableCars[i];
      }
    }
    return nullptr;
  }

  void returnCar(unsigned id)
  {
    RentableCar *car = findCar(id);
    if (!car)
    {
      throw std::logic_error("Car with the given ID not found.");
    }
    if (!car->isRented())
    {
      throw std::logic_error("Car is not currently rented.");
    }

    unsigned carProfit = car->returnToDealer();
    profit += carProfit;
    std::cout << "Car returned. Earned profit: " << carProfit << std::endl;
  }

  void printCars() const
  {
    for (int i = 0; i < size; i++)
    {
      rentableCars[i].printCar();
    }
  }

private:
  RentableCar *rentableCars;
  unsigned cap;
  unsigned size;
  unsigned profit;
};

int main()
{

  User u1("JohnDoe", "AB123456CD", 18);
  RentableCar car1(450, 55);
  car1.rent(&u1);
  car1.printRenter();
  std::cout << "Profit: " << car1.returnToDealer() << std::endl;
  car1.printRenter();

  CarRentalService rentalService(3);
  rentalService.addCar(car1);
  rentalService.printCars();
  rentalService.printCars();

  return 0;
}
