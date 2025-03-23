// Имате двоичния файл people.dat. В него се пази последователно следната информация за произволен брой хора:

// име, което е максимално 23 символа
// каква заплата изкарват от тип unsigned

// Да се имплементират следните функционалности:
// Отпечатване на хората, които изкарват над средната заплата
// Добавяне на човек във файла people.dat

#include <iostream>
#include <fstream>

struct Person
{
  char name[24];
  unsigned salary;
};

void printAboveAverage()
{
  std::ifstream inputFile("people.dat", std::ios::binary | std::ios::ate);
  if (!inputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return;
  }

  size_t fileSize = inputFile.tellg();

  size_t peopleCount = fileSize / sizeof(Person);
  if (peopleCount == 0)
  {
    std::cout << "No people in the file." << std::endl;
    inputFile.close();
    return;
  }

  Person *peopleArr = new Person[peopleCount];

  inputFile.seekg(0);
  inputFile.read((char *)peopleArr, fileSize);
  inputFile.close();

  unsigned totalSalary = 0;
  for (size_t i = 0; i < peopleCount; i++)
  {
    totalSalary += peopleArr[i].salary;
  }

  unsigned avgSalary = totalSalary / peopleCount;
  for (size_t i = 0; i < peopleCount; i++)
  {
    if (peopleArr[i].salary > avgSalary)
    {
      std::cout << peopleArr[i].name << " - " << peopleArr[i].salary << std::endl;
    }
  }

  delete[] peopleArr;
}

void addPerson()
{
  std::ofstream outputFile("people.dat", std::ios::binary | std::ios::app);
  if (!outputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return;
  }

  Person person;

  std::cout << "Enter a name (23 chars max): ";
  std::cin.getline(person.name, 24);

  std::cout << "Enter salary: ";
  std::cin >> person.salary;

  outputFile.write((char *)(&person), sizeof(Person));
  outputFile.close();

  std::cout << "Added: " << person.name << ", Salary: " << person.salary << std::endl;
}

int main()
{
  std::cout << "-- People with above the average salary --\n";
  printAboveAverage();

  addPerson();

  std::cout << "-- People with above the average salary --\n";
  printAboveAverage();

  return 0;
}