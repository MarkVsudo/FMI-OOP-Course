#pragma once

struct Address
{
  char street[64];          // 64 B
  char city[32];            // 32 B
  unsigned postalCode;      // 4 B
  unsigned number;          // 4 B
  unsigned short entrance;  // 2 B
  unsigned short floor;     // 2 B
  unsigned short apartment; // 2 B
  char letter;              // 1 B
};

void readAddressData(Address &address);

void printAddressData(const Address &address);
