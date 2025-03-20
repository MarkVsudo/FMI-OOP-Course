// 7. Създайте структура City, която описва град и има име (до 63 символа) и брой жители. Създайте и структура District, която съдържа в себе си до 20 града и пази текущия си размер.

// Напишете функция, която записва във файл една област.
// Напишете друга функция, която прочита област от файл, след което сортира градовете в областта според броя на жителите им във възходящ ред и записва резултата в друг файл.

#include <iostream>
#include <cstring>
#include <fstream>

struct City
{
  char name[64];
  int population;
};

struct District
{
  City cities[20];
  int currSize = 0;

  void addCity(const char *cityName, int population)
  {
    if (currSize < 20)
    {
      strncpy(cities[currSize].name, cityName, sizeof(cities[currSize].name) - 1);
      cities[currSize].name[sizeof(cities[currSize].name) - 1] = '\0';
      cities[currSize].population = population;
      currSize++;
    }
    else
    {
      std::cerr << "You've exceeded the limit for cities -> 20!" << std::endl;
    }
  }
};

void writeDistrictToFile(const char *outputFileName, const District &district)
{
  std::ofstream outputFile(outputFileName, std::ios::binary);

  if (!outputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return;
  }

  outputFile.write((char *)&district, sizeof(district));

  outputFile.close();
}

void readDistrictFromFile(const char *inputFileName)
{
  std::ifstream inputFile(inputFileName, std::ios::binary);
  if (!inputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return;
  }

  District district;
  inputFile.read((char *)&district, sizeof(District));

  for (int i = 0; i < district.currSize; i++)
  {
    std::cout << "City: " << district.cities[i].name << std::endl;
    std::cout << "Population: " << district.cities[i].population << std::endl;
  }

  inputFile.close();
}

void sortCitiesAsc(const char *inputFileName, const char *outputFileName)
{
  std::ifstream inputFile(inputFileName, std::ios::binary);
  if (!inputFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return;
  }

  std::ofstream outputFile(outputFileName, std::ios::binary);
  if (!outputFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return;
  }

  District district;
  inputFile.read((char *)&district, sizeof(District));
  inputFile.close();

  for (int i = 0; i < district.currSize - 1; i++)
  {
    for (int j = 0; j < district.currSize - i - 1; j++)
    {
      if (district.cities[j].population > district.cities[j + 1].population)
      {
        City temp = district.cities[j];
        district.cities[j] = district.cities[j + 1];
        district.cities[j + 1] = temp;
      }
    }
  }

  outputFile.write((char *)&district, sizeof(District));
  outputFile.close();
}
int main()
{
  District district;

  district.addCity("Sofia", 1200000);
  district.addCity("Plovdiv", 340000);

  const char *districtsFileName = "districts.bin";
  const char *ascOrderDistrictsFileName = "ascOrderDistricts.bin";

  writeDistrictToFile(districtsFileName, district);
  std::cout << "-- Not sorted cities --" << std::endl;
  readDistrictFromFile(districtsFileName);
  std::cout << "-- Sorted cities --" << std::endl;
  sortCitiesAsc(districtsFileName, ascOrderDistrictsFileName);
  readDistrictFromFile(ascOrderDistrictsFileName);
  return 0;
}