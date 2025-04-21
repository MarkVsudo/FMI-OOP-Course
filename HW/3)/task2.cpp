#include <iostream>
#include <cstring>

struct Date
{
  Date() : day(1), month(1), year(1) {}
  Date(int d, int m, int y) : day(d), month(m), year(y) {}

  void printDate() const
  {
    std::cout << day << "/" << month << "/" << year << std::endl;
  }

  int day;
  int month;
  int year;
};

const char *GENDER_STRS[] = {"Male", "Female", "Other"};

enum Gender
{
  MALE = 1,
  FEMALE,
  OTHER
};
class Person
{
public:
  Person(const char *fName, const char *mName, const char *lName, const Date &date, const Gender gender)
      : date(date), gender(gender)
  {
    setFName(fName);
    setMName(mName);
    setLName(lName);
  }

  void printData() const
  {
    std::cout << "First name: " << fName << std::endl;
    std::cout << "Middle name: " << mName << std::endl;
    std::cout << "Last name: " << lName << std::endl;
    date.printDate();
    std::cout << "Gender: " << GENDER_STRS[gender - 1] << std::endl;
  }

  void editFName(const char *newFName)
  {
    if (newFName == nullptr || strlen(newFName) == 0)
    {
      std::cerr << "Cannot add an empty first name!\n";
      return;
    }

    strncpy(this->fName, newFName, 31);
    this->fName[31] = '\0';
  }

  void editMName(const char *newMName)
  {
    if (newMName == nullptr || strlen(newMName) == 0)
    {
      std::cerr << "Cannot add an empty middle name!\n";
      return;
    }

    strncpy(this->mName, newMName, 31);
    this->mName[31] = '\0';
  }

  void editLName(const char *newLName)
  {
    if (newLName == nullptr || strlen(newLName) == 0)
    {
      std::cerr << "Cannot add an empty last name!\n";
      return;
    }

    strncpy(this->lName, newLName, 31);
    this->lName[31] = '\0';
  }

  void setFName(const char *fName)
  {
    if (fName == nullptr)
    {
      std::cerr << "Cannot add an empty first name!\n";
      return;
    }

    strncpy(this->fName, fName, 31);
    this->fName[31] = '\0';
  }

  void setMName(const char *mName)
  {
    if (mName == nullptr)
    {
      std::cerr << "Cannot add an empty middle name!\n";
      return;
    }

    strncpy(this->mName, mName, 31);
    this->mName[31] = '\0';
  }

  void setLName(const char *lName)
  {
    if (lName == nullptr)
    {
      std::cerr << "Cannot add an empty last name!\n";
      return;
    }

    strncpy(this->lName, lName, 31);
    this->lName[31] = '\0';
  }

private:
  char fName[32];
  char mName[32];
  char lName[32];
  const Date date;
  const Gender gender;
};

class Car
{
public:
  // Конструктор на колата
  Car(const char *brand, const char *model, const Date &productionDate, unsigned int color, Person *owner = nullptr)
      : productionDate(productionDate), color(color), owner(owner)
  {
    // Задаваме марка и модел (с ограничение на дължината на низовете)
    setBrand(brand);
    setModel(model);
  }

  // Метод за извеждане на данни за колата
  void printData() const
  {
    std::cout << "Brand: " << brand << std::endl;
    std::cout << "Model: " << model << std::endl;
    productionDate.printDate();
    std::cout << "Color: " << std::hex << color << std::dec << std::endl; // Извеждаме цвета в RGB формат
    if (owner)
    {
      std::cout << "Owner:\n";
      owner->printData();
    }
    else
    {
      std::cout << "No owner.\n";
    }
  }

private:
  // Помощни методи за задаване на марка и модел с проверка за дължина
  void setBrand(const char *b)
  {
    if (b && strlen(b) > 0)
    {
      strncpy(brand, b, sizeof(brand) - 1);
      brand[sizeof(brand) - 1] = '\0'; // осигуряваме завършване на низа с нулев терминатор
    }
  }

  void setModel(const char *m)
  {
    if (m && strlen(m) > 0)
    {
      strncpy(model, m, sizeof(model) - 1);
      model[sizeof(model) - 1] = '\0'; // осигуряваме завършване на низа с нулев терминатор
    }
  }

private:
  const Date productionDate; // Дата на производство (не може да се променя)
  unsigned int color;        // Цвят (RGB формат)
  Person *owner;             // Собственик (може да бъде nullptr)
  char brand[32];            // Марка на колата (фиксирана дължина)
  char model[32];            // Модел на колата (фиксирана дължина)
};

int main()
{
  Date date(17, 6, 2005);
  Person person("Mark", "Ognyanov", "Veskov", date, Gender::MALE);

  person.printData();
  person.editFName("Ioan");
  person.editMName("Petrov");
  person.editLName("Dimitrov");
  person.printData();

  return 0;
}