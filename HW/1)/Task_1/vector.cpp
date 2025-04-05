#include "vector.h"
#include <iostream>

// а) създаване на вектор;
void createVector(Vector &vector)
{
  std::cout << "Enter x,y,z to create a vector: ";
  std::cin >> vector.x >> vector.y >> vector.z;
}

// б) извеждане на вектор на екрана;
void printVector(const Vector &vector)
{
  std::cout << "(" << vector.x << "," << vector.y << "," << vector.z << ")" << std::endl;
}

// в) намиране на сумата на два вектора;
Vector addVectors(const Vector &vector1, const Vector &vector2)
{
  Vector res;
  res.x = vector1.x + vector2.x;
  res.y = vector1.y + vector2.y;
  res.z = vector1.z + vector2.z;
  return res;
}

// г) намиране на разликата на два вектора;
Vector subtractVectors(const Vector &vector1, const Vector &vector2)
{
  Vector res;
  res.x = vector1.x - vector2.x;
  res.y = vector1.y - vector2.y;
  res.z = vector1.z - vector2.z;
  return res;
}

// д) намиране на произведението на вектор с число;
Vector multiplyVectorByScalar(const Vector &vector, double scalar)
{
  Vector res;
  res.x = vector.x * scalar;
  res.y = vector.y * scalar;
  res.z = vector.z * scalar;
  return res;
}

// е) намиране на скаларното произведение на два вектора;
double findScalarProduct(const Vector &vector1, const Vector &vector2)
{
  return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}
