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
#include "vector.h"

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