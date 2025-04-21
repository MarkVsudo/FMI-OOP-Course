// Разглеждаме следната структура

// struct Order
// {
//     double grossPrice;
//     double vat;
//     int customerID;
// };
// която описва за един магазин направена поръчка.

// В двоичен файл storeOrders.bin е запсана информацията за магазин и поръчките, които са направени, посредством тази структура. Искаме да разберем, кой потребител е направил най-много поръчки, кой е направил най-скъпата поръчка, и сумарно кой е платил най-много. Тази информация отново трябва да се запише в двоичен файл topCustomers.bin

// Да има възможност да се въвежда информация за нови поръчки през конзолата, докато програмата работи и след това те да бъдат записвани във файла storeOrders.bin

#include <iostream>
#include <fstream>

struct Order
{
  double grossPrice;
  double vat;
  int customerID;
};

void readOrdersData(Order *orders, const unsigned n)
{
  for (unsigned i = 0; i < n; i++)
  {
    std::cout << "Order " << i + 1 << std::endl;
    std::cout << "Gross price: ";
    std::cin >> orders[i].grossPrice;
    std::cout << "VAT: ";
    std::cin >> orders[i].vat;
    std::cout << "Customer ID: ";
    std::cin >> orders[i].customerID;
  }
}

// customer with most orders
// customer with the most expensive order
// biggest spender

bool hasMoreOrders(Order &order1, Order &order2)
{
}

Order *customersMeetingCriteria(bool (*pred)(const Order &), const Order *orders, const unsigned n)
{
  for (unsigned i = 0; i < n; i++)
  {
    if (pred(orders[i]))
    {
    }
  }
}

int main()
{

  unsigned n;
  do
  {
    std::cout << "Enter amount of orders: ";
    std::cin >> n;
  } while (n < 0);

  Order *orders = new Order[n];

  readOrdersData(orders, n);

  std::ofstream storeOrdersOutFile("storeOrders.bin", std::ios::binary);

  if (!storeOrdersOutFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    delete[] orders;
    return -1;
  }

  storeOrdersOutFile.write((char *)orders, sizeof(Order) * n);
  storeOrdersOutFile.close();

  delete[] orders;

  std::ifstream storeOrdersInFile("storeOrders.bin", std::ios::binary);
  if (!storeOrdersInFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return -2;
  }

  Order *loadedOrders = new Order[n];
  storeOrdersInFile.read((char *)loadedOrders, sizeof(Order) * n);
  storeOrdersInFile.close();

  std::cout << "-- Order data read from binary file -- \n";
  for (unsigned i = 0; i < n; i++)
  {
    std::cout << "Order " << i + 1 << std::endl;
    std::cout << "Gross price: " << loadedOrders[i].grossPrice << std::endl;
    std::cout << "VAT: " << loadedOrders[i].vat << std::endl;
    std::cout << "Customer ID: " << loadedOrders[i].customerID << std::endl;
  }

  delete[] loadedOrders;

  return 0;
}