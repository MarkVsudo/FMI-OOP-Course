// Създайте структура, която представлява точка в двумерното пространство. Също така, реализирайте следните функции:

// четене от стандартния вход
// принтиране на стандартния изход
// разстояние между две точки

#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

struct Point
{
  double x, y;
};

void readPoint(Point &point)
{
  cout << "Enter x and y for a point: ";
  cin >> point.x >> point.y;
}

void printPoint(const Point &point)
{
  cout << "(" << point.x << ", " << point.y << ")" << endl;
}

double distanceFromPointToPoint(const Point &point1, const Point &point2)
{
  double distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) +
                         (point1.y - point2.y) * (point1.y - point2.y));

  return distance;
}

int main()
{
  Point point1;
  Point point2;

  readPoint(point1);
  readPoint(point2);

  printPoint(point1);
  printPoint(point2);

  cout << "Distance between points: " << distanceFromPointToPoint(point1, point2) << endl;

  return 0;
}