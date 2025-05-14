#include <iostream>
#include <stdexcept>
#include <cstring>

class Computer
{
public:
  Computer() : CPUPower(0), GPUModel(nullptr), PSUPower(0), RAMCount(0) {}

  Computer(double CPUPower, const char *GPUModel, int PSUPower, int RAMCount)
      : GPUModel(nullptr)
  {
    setCPUPower(CPUPower);
    setGPUModel(GPUModel);
    setPSUPower(PSUPower);
    setRAMCount(RAMCount);
  }

  virtual ~Computer()
  {
    delete[] GPUModel;
  }

  Computer(const Computer &other) : GPUModel(nullptr)
  {
    setCPUPower(other.CPUPower);
    setGPUModel(other.GPUModel);
    setPSUPower(other.PSUPower);
    setRAMCount(other.RAMCount);
  }

  Computer &operator=(const Computer &other)
  {
    if (this != &other)
    {
      setCPUPower(other.CPUPower);
      setGPUModel(other.GPUModel);
      setPSUPower(other.PSUPower);
      setRAMCount(other.RAMCount);
    }
    return *this;
  }

  virtual void printDeviceType() const = 0;
  virtual void getPeripheralDevices() const = 0;

  void setCPUPower(double CPUPower)
  {
    if (CPUPower < 0)
      throw std::invalid_argument("CPU power cannot be less than 0");
    this->CPUPower = CPUPower;
  }

  void setGPUModel(const char *GPUModel)
  {
    if (GPUModel)
    {
      delete[] this->GPUModel;
      size_t len = strlen(GPUModel);
      this->GPUModel = new char[len + 1];
      strcpy(this->GPUModel, GPUModel);
    }
  }

  void setPSUPower(int PSUPower)
  {
    if (PSUPower < 0)
      throw std::invalid_argument("PSU power cannot be less than 0");
    this->PSUPower = PSUPower;
  }

  void setRAMCount(int RAMCount)
  {
    if (RAMCount < 0)
      throw std::invalid_argument("RAM count cannot be less than 0");
    this->RAMCount = RAMCount;
  }

protected:
  double CPUPower;
  char *GPUModel;
  int PSUPower;
  int RAMCount;
};

class PC : public Computer
{
public:
  PC(double CPUPower, const char *GPUModel, int PSUPower, int RAMCount)
      : Computer(CPUPower, GPUModel, PSUPower, RAMCount) {}

  void printDeviceType() const override
  {
    std::cout << "Type: PC" << std::endl;
  }

  void getPeripheralDevices() const override
  {
    const char *devices[] = {"Mouse", "Keyboard", "Microphone", "Headphones"};
    std::cout << "Peripherals: ";
    int i = 0;
    while (i < 4)
    {
      std::cout << devices[i] << " ";
      ++i;
    }
    std::cout << std::endl;
  }
};

class Laptop : public Computer
{
public:
  Laptop(double CPUPower, const char *GPUModel, int PSUPower, int RAMCount)
      : Computer(CPUPower, GPUModel, PSUPower, RAMCount) {}

  void printDeviceType() const override
  {
    std::cout << "Type: Laptop" << std::endl;
  }

  void getPeripheralDevices() const override
  {
    const char *devices[] = {"Mouse Pad", "Keyboard", "Monitor"};
    std::cout << "Peripherals: ";
    int i = 0;
    while (i < 3)
    {
      std::cout << devices[i] << " ";
      ++i;
    }
    std::cout << std::endl;
  }
};

class GamingConsole : public Computer
{
public:
  GamingConsole(double CPUPower, const char *GPUModel, int PSUPower, int RAMCount)
      : Computer(CPUPower, GPUModel, PSUPower, RAMCount) {}

  void printDeviceType() const override
  {
    std::cout << "Type: Gaming Console" << std::endl;
  }

  void getPeripheralDevices() const override
  {
    const char *devices[] = {"Joystick", "Monitor"};
    std::cout << "Peripherals: ";
    int i = 0;
    while (i < 2)
    {
      std::cout << devices[i] << " ";
      ++i;
    }
    std::cout << std::endl;
  }
};

int main()
{
  try
  {
    PC myPC(3.5, "NVIDIA GTX 1080", 600, 16);
    Laptop myLaptop(2.3, "Intel Iris", 120, 8);
    GamingConsole myConsole(3.0, "AMD Radeon", 200, 12);

    myPC.printDeviceType();
    myPC.getPeripheralDevices();

    myLaptop.printDeviceType();
    myLaptop.getPeripheralDevices();

    myConsole.printDeviceType();
    myConsole.getPeripheralDevices();
  }
  catch (const std::exception &e)
  {
    std::cerr << "An error occurred: " << e.what() << std::endl;
  }

  return 0;
}
