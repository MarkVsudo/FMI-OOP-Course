// Създайте структура, която представлява комплексно число. Също така, реализирайте следните функции:

// получаване на комплексно спрегнатото на комплексно число
// събиране на 2 комплексни числа
// изваждане на 2 комплексни числа
// умножение на 2 комплексни числа
// деление на 2 комплексни числа
// сравнение за равенство на 2 комплексни числа
// принтиране на комплексно число

#include <iostream>
#include <cmath>

struct ComplexNumber
{
  double real;
  double imaginary;
};

ComplexNumber calcComplexConjugate(ComplexNumber complexNumber)
{
  return {complexNumber.real, -complexNumber.imaginary};
}

ComplexNumber calcComplexSum(ComplexNumber complexNumber1, ComplexNumber complexNumber2)
{
  return {complexNumber1.real + complexNumber2.real, complexNumber1.imaginary + complexNumber2.imaginary};
}

ComplexNumber calcComplexSubtraction(ComplexNumber complexNumber1, ComplexNumber complexNumber2)
{
  return {complexNumber1.real - complexNumber2.real, complexNumber1.imaginary - complexNumber2.imaginary};
}

ComplexNumber calcComplexProduct(ComplexNumber complexNumber1, ComplexNumber complexNumber2)
{
  return {
      (complexNumber1.real * complexNumber2.real) - (complexNumber1.imaginary * complexNumber2.imaginary),
      (complexNumber1.real * complexNumber2.imaginary) + (complexNumber1.imaginary * complexNumber2.real)};
}

ComplexNumber calcComplexDivision(ComplexNumber complexNumber1, ComplexNumber complexNumber2)
{
  double denominator = pow(complexNumber2.real, 2) + pow(complexNumber2.imaginary, 2);

  return {
      (complexNumber1.real * complexNumber2.real + complexNumber1.imaginary * complexNumber2.imaginary) / denominator,
      (complexNumber1.imaginary * complexNumber2.real - complexNumber1.real * complexNumber2.imaginary) / denominator};
}

bool checkComplexEquality(ComplexNumber complexNumber1, ComplexNumber complexNumber2)
{
  return (complexNumber1.real == complexNumber2.real) && (complexNumber1.imaginary == complexNumber2.imaginary);
}

void printComplexNumber(ComplexNumber complexNumber)
{
  if (complexNumber.imaginary >= 0)
    std::cout << complexNumber.real << " + " << complexNumber.imaginary << "i" << std::endl;
  else
    std::cout << complexNumber.real << " - " << -complexNumber.imaginary << "i" << std::endl;
}

int main()
{

  ComplexNumber complexNumber1 = {2, 3};
  ComplexNumber complexNumber2 = {1, -2};

  std::cout << "-- Complex Conjugate --" << std::endl;
  printComplexNumber(complexNumber1);
  printComplexNumber(calcComplexConjugate(complexNumber1));
  std::cout << "---" << std::endl;
  printComplexNumber(complexNumber2);
  printComplexNumber(calcComplexConjugate(complexNumber2));

  std::cout << "-- Complex Sum --" << std::endl;
  printComplexNumber(calcComplexSum(complexNumber1, complexNumber2));

  std::cout << "-- Complex Subtraction --" << std::endl;
  printComplexNumber(calcComplexSubtraction(complexNumber1, complexNumber2));

  std::cout << "-- Complex Product --" << std::endl;
  printComplexNumber(calcComplexProduct(complexNumber1, complexNumber2));

  std::cout << "-- Complex Division --" << std::endl;
  printComplexNumber(calcComplexDivision(complexNumber1, complexNumber2));

  std::cout << "-- Complex Equality --" << std::endl;
  printComplexNumber(complexNumber1);
  std::cout << "and ";
  printComplexNumber(complexNumber2);
  std::cout << "are" << (checkComplexEquality(complexNumber1, complexNumber2) ? " " : " not ") << "equal";

  return 0;
}