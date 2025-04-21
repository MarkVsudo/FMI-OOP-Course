#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

struct Triangle
{
  double a, b, c;
};

void readTriangleData(Triangle &tri)
{
  cout << "Enter sides of triangle (a, b, c): ";
  cin >> tri.a >> tri.b >> tri.c;
}

void printTriangleData(const Triangle &tri)
{
  cout << "Triangle sides: a = " << tri.a << " b = " << tri.b << " c = " << tri.c << endl;
}

double calcTriPerimeter(const Triangle &tri)
{
  return tri.a + tri.b + tri.c;
}

double calcTriArea(const Triangle &tri)
{
  double s = calcTriPerimeter(tri) / 2;
  return sqrt(s * (s - tri.a) * (s - tri.b) * (s - tri.c));
}

void getTriangleTypeBySides(const Triangle &tri)
{
  if (tri.a == tri.b && tri.b == tri.c)
    cout << "Ravnostranen" << endl;
  else if (tri.a == tri.b || tri.a == tri.c || tri.b == tri.c)
    cout << "Ravnobedren" << endl;
  else
    cout << "Raznostranen" << endl;
}

void getTriangleTypeByAngles(const Triangle &tri)
{
  double a2 = tri.a * tri.a,
         b2 = tri.b * tri.b,
         c2 = tri.c * tri.c;

  if (a2 + b2 == c2 || a2 + c2 == b2 || b2 + c2 == a2)
    cout << "Pravougulen" << endl;
  else if (a2 + b2 > c2 && a2 + c2 > b2 && b2 + c2 > a2)
    cout << "Ostrougulen" << endl;
  else
    cout << "Tupougulen" << endl;
}

int main()
{
  Triangle tri;

  readTriangleData(tri);
  printTriangleData(tri);

  cout << "Perimeter: " << calcTriPerimeter(tri) << endl;
  cout << "Area: " << calcTriArea(tri) << endl;

  getTriangleTypeBySides(tri);
  getTriangleTypeByAngles(tri);

  return 0;
}
