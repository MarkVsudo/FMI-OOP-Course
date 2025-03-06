#include "address.h"
#include <iostream>

void readAddressData(Address &address)
{
  std::cout << "-- Enter address data --" << std::endl;

  std::cout << "City: ";
  std::cin.getline(address.city, 32);

  do
  {
    std::cout << "Postal code: ";
    std::cin >> address.postalCode;
  } while (address.postalCode < 0);

  std::cin.ignore();
  std::cout << "Street: ";
  std::cin.getline(address.street, 64);

  do
  {
    std::cout << "Number: ";
    std::cin >> address.number;
  } while (address.number < 0);

  std::cout << "Letter: ";
  std::cin >> address.letter;

  do
  {
    std::cout << "Entrance: ";
    std::cin >> address.entrance;
  } while (address.entrance < 1);

  do
  {
    std::cout << "Floor: ";
    std::cin >> address.floor;
  } while (address.floor < 0);

  do
  {
    std::cout << "Apartment: ";
    std::cin >> address.apartment;
  } while (address.apartment < 1);
}

void printAddressData(const Address &address)
{
  std::cout << "Address: \"" << address.city << "\", " << address.postalCode << ", \"" << address.street << "\", " << address.number << " " << address.letter << ", ent. " << address.entrance << ", floor " << address.floor << ", ap. " << address.apartment << std::endl;
}