// Задача 2. Като се използва Vector (Задача 1), да се напише програма, която въвежда n вектора от тримерното пространство (n ≥ 3) и проверява дали съществуват три вектора от тях, които са взаимно перпендикулярни.

#include <iostream>
#include <cmath>

struct Vector
{
  double x, y, z;
};

void createVector(Vector &vector)
{
  std::cout << "Enter x, y, z for the vector: ";
  std::cin >> vector.x >> vector.y >> vector.z;
}

void printVector(const Vector &vector)
{
  std::cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}

double findScalarProduct(const Vector &vector1, const Vector &vector2)
{
  return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

// Check if three vectors are mutually perpendicular
bool areThreeVectorsPerpendicular(const Vector &v1, const Vector &v2, const Vector &v3)
{
  const double EPSILON = 1e-9;
  return (std::fabs(findScalarProduct(v1, v2)) < EPSILON &&
          std::fabs(findScalarProduct(v1, v3)) < EPSILON &&
          std::fabs(findScalarProduct(v2, v3)) < EPSILON);
}

int main()
{
  int n;
  do
  {
    std::cout << "Enter the number of vectors (n >= 3): ";
    std::cin >> n;
  } while (n < 3);

  Vector *vectors = new Vector[n];

  // Input vectors
  for (int i = 0; i < n; i++)
  {
    std::cout << "Vector " << i + 1 << ":" << std::endl;
    createVector(vectors[i]);
  }

  delete[] vectors;

  return 0;
}
