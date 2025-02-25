// Напишете структура Person, която да има полета за

// име (до 25 символа)
// възраст
// пол
// Създайте масив от обекти.

// Изведете:

// - всички мъже, после всички жени
// - най-старата жена
// - най-младия мъж, чието име започва с 'А'

#include <iostream>

enum class Gender
{
  Male,
  Female,
  Other
};

struct Person
{
  char name[25 + 1];
  int age;
  Gender gender;
};

void printPerson(Person person)
{
  const char *genderStr = (person.gender == Gender::Male) ? "Male" : (person.gender == Gender::Female) ? "Female"
                                                                                                       : "Other";

  std::cout << "Name: " << person.name << " | Age: " << person.age << " | Gender: " << genderStr << "\n";
}

void printMalesAndFemales(Person people[], unsigned size)
{
  for (unsigned i = 0; i < size; i++)
  {
    if (people[i].gender == Gender::Male)
      printPerson(people[i]);
  }

  for (unsigned i = 0; i < size; i++)
  {
    if (people[i].gender == Gender::Female)
      printPerson(people[i]);
  }
}

int findOldestFemale(Person people[], unsigned size)
{
  int index = -1;

  for (unsigned i = 0; i < size; i++)
  {
    if (people[i].gender == Gender::Female)
    {
      if (index == -1 || people[i].age > people[index].age)
      {
        index = i;
      }
    }
  }

  return index;
}

int youngestManStartingWithA(Person people[], unsigned size)
{
  int index = -1;

  for (unsigned i = 0; i < size; i++)
  {
    if (people[i].gender == Gender::Male && (people[i].name[0] == 'A' || people[i].name[0] == 'a'))
    {
      if (index == -1 || people[i].age < people[index].age)
      {
        index = i;
      }
    }
  }

  return index;
}

int main()
{

  Person people[5]{
      {"Ivanka", 21, Gender::Female},
      {"Ivan", 15, Gender::Male},
      {"Anton", 33, Gender::Male},
      {"Petka", 29, Gender::Female},
      {"Ahmed", 19, Gender::Male},
  };

  printMalesAndFemales(people, 5);

  int oldestFemaleIndex = findOldestFemale(people, 5);
  if (oldestFemaleIndex == -1)
  {
    std::cout << "No women found.\n";
  }
  else
  {
    std::cout << "-- Oldest woman --\n";
    printPerson(people[oldestFemaleIndex]);
  }

  int youngestManAIndex = youngestManStartingWithA(people, 5);
  if (youngestManAIndex == -1)
  {
    std::cout << "No men found starting with the letter 'A'.\n";
  }
  else
  {
    std::cout << "-- Youngest man starting with 'A' --\n";
    printPerson(people[youngestManAIndex]);
  }

  return 0;
}