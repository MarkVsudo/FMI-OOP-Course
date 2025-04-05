// Задача 1. Да се дефинира тип структура Vector, който определя вектор в тримерното пространство
// и да се реализират функции за:
// а) създаване на вектор;
// б) извеждане на вектор на екрана;
// в) намиране на сумата на два вектора;
// г) намиране на разликата на два вектора;
// д) намиране на произведението на вектор с число;
// е) намиране на скаларното произведение на два вектора;
// Да се напише програма, която създава няколко вектора и намира и извежда сумата, разликата и различните произведения на векторите.

#include <iostream>

// 3d vector -> (x,y,z)
struct Vector
{
  double x, y, z;
};

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

int main()
{

  Vector vector1, vector2;

  // Създаване на два вектора
  createVector(vector1);
  printVector(vector1);

  createVector(vector2);
  printVector(vector2);

  // Намиране на сумата на двата вектора
  Vector sum = addVectors(vector1, vector2);
  std::cout << "Sum of vectors: ";
  printVector(sum);

  // Намиране на разликата на двата вектора
  Vector diff = subtractVectors(vector1, vector2);
  std::cout << "Difference of vectors: ";
  printVector(diff);

  // Намиране на произведението на вектор с число
  double scalar = 3.0;
  Vector multipliedVector = multiplyVectorByScalar(vector1, scalar);
  std::cout << "Vector multiplied by scalar " << scalar << ": ";
  printVector(multipliedVector);

  // Намиране на скаларното произведение
  double scalarProdRes = findScalarProduct(vector1, vector2);
  std::cout << "Scalar product of vectors: " << scalarProdRes << std::endl;

  return 0;
}