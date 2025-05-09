#include <iostream>
#include <stdexcept>

class ComplexNumber
{
public:
  ComplexNumber(double real = 0, double imaginary = 0)
      : real(real), imaginary(imaginary) {}

  ComplexNumber(const ComplexNumber &other)
      : real(other.real), imaginary(other.imaginary) {}

  ComplexNumber operator+(const ComplexNumber &other) const
  {
    return ComplexNumber(real + other.real, imaginary + other.imaginary);
  }

  ComplexNumber operator-(const ComplexNumber &other) const
  {
    return ComplexNumber(real - other.real, imaginary - other.imaginary);
  }

  ComplexNumber operator*(const ComplexNumber &other) const
  {
    return ComplexNumber(
        real * other.real - imaginary * other.imaginary,
        real * other.imaginary + imaginary * other.real);
  }

  ComplexNumber operator/(const ComplexNumber &other) const
  {
    if (other.real == 0 && other.imaginary == 0)
      throw std::invalid_argument("Cannot divide by zero");

    double denominator = other.real * other.real + other.imaginary * other.imaginary;
    return ComplexNumber(
        (real * other.real + imaginary * other.imaginary) / denominator,
        (imaginary * other.real - real * other.imaginary) / denominator);
  }

  bool operator==(const ComplexNumber &other) const
  {
    return real == other.real && imaginary == other.imaginary;
  }

  bool operator<(const ComplexNumber &other) const
  {
    return (real < other.real) || (real == other.real && imaginary < other.imaginary);
  }

  ComplexNumber &operator=(const ComplexNumber &other)
  {
    if (this != &other)
    {
      real = other.real;
      imaginary = other.imaginary;
    }
    return *this;
  }

  ComplexNumber conjugate() const
  {
    return ComplexNumber(real, -imaginary);
  }

  void setReal(double r) { real = r; }
  void setImaginary(double i) { imaginary = i; }
  double getReal() const { return real; }
  double getImaginary() const { return imaginary; }

  friend std::ostream &operator<<(std::ostream &os, const ComplexNumber &cn)
  {
    os << cn.real;
    if (cn.imaginary >= 0)
      os << "+";
    os << cn.imaginary << "i";
    return os;
  }

  friend std::istream &operator>>(std::istream &is, ComplexNumber &cn)
  {
    char sign;
    is >> cn.real >> sign >> cn.imaginary;
    if (sign == '-')
      cn.imaginary = -cn.imaginary;
    if (is.peek() == 'i')
      is.ignore();
    return is;
  }

private:
  double real;
  double imaginary;
};

int main()
{
  ComplexNumber z1(2, 3), z2(1, -4);

  std::cout << "z1 = " << z1 << "\n";
  std::cout << "z2 = " << z2 << "\n";

  std::cout << "z1 + z2 = " << (z1 + z2) << "\n";
  std::cout << "z1 - z2 = " << (z1 - z2) << "\n";
  std::cout << "z1 * z2 = " << (z1 * z2) << "\n";
  std::cout << "z1 / z2 = " << (z1 / z2) << "\n";

  std::cout << "Conjugate of z1 = " << z1.conjugate() << "\n";

  std::cout << "Comparison (z1 < z2): " << (z1 < z2 ? "true" : "false") << "\n";
  return 0;
}
