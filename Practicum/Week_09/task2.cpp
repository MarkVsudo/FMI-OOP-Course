#include <iostream>
#include <stdexcept>

class NVector
{
public:
  NVector(double *arr, unsigned size)
  {
    this->size = size;
    this->arr = new double[size];
    for (unsigned i = 0; i < size; i++)
    {
      this->arr[i] = arr[i];
    }
  }

  NVector(const NVector &other)
  {
    this->size = other.size;
    this->arr = new double[size];
    for (unsigned i = 0; i < size; i++)
    {
      this->arr[i] = other.arr[i];
    }
  }

  ~NVector()
  {
    delete[] arr;
  }

  NVector &operator=(const NVector &other)
  {
    if (this != &other)
    {
      delete[] arr;
      this->size = other.size;
      this->arr = new double[size];
      for (unsigned i = 0; i < size; i++)
      {
        this->arr[i] = other.arr[i];
      }
    }
    return *this;
  }

  NVector operator+(const NVector &other) const
  {
    if (this->size != other.size)
      throw std::invalid_argument("Vectors must be of the same size");

    double *result = new double[size];
    for (unsigned i = 0; i < size; i++)
    {
      result[i] = this->arr[i] + other.arr[i];
    }

    NVector newVector(result, size);
    return newVector;
  }

  NVector operator-(const NVector &other) const
  {
    if (this->size != other.size)
      throw std::invalid_argument("Vectors must be of the same size");

    double *result = new double[size];
    for (unsigned i = 0; i < size; i++)
    {
      result[i] = this->arr[i] - other.arr[i];
    }

    NVector newVector(result, size);
    return newVector;
  }

  NVector multiplyWithScalar(double scalar) const
  {
    double *result = new double[size];
    for (unsigned i = 0; i < size; i++)
    {
      result[i] = this->arr[i] * scalar;
    }
    NVector newVector(result, size);
    return newVector;
  }

  bool areParallel(const NVector &other) const
  {
    if (this->size != other.size)
      throw std::invalid_argument("Vectors must be of the same size");

    const double EPSILON = 1e-9;
    double k = 0;
    bool ratioInitialized = false;

    for (unsigned i = 0; i < size; ++i)
    {
      double a = this->arr[i];
      double b = other.arr[i];

      if (a == 0 && b == 0)
      {
        continue;
      }
      else if (a == 0 || b == 0)
      {
        return false;
      }
      else
      {
        double currentRatio = b / a;
        if (!ratioInitialized)
        {
          k = currentRatio;
          ratioInitialized = true;
        }
        else if (std::abs(currentRatio - k) > EPSILON)
        {
          return false;
        }
      }
    }

    return true;
  }

  bool arePerpendicular(const NVector &other) const
  {
    double dotProduct = 0;

    for (unsigned i = 0; i < size; i++)
    {
      double a = this->arr[i];
      double b = other.arr[i];

      dotProduct += a * b;
    }

    const double EPSILON = 1e-9;
    return std::abs(dotProduct) < EPSILON;
  }

  double getVectorLength() const
  {
    double length = 0;

    for (unsigned i = 0; i < size; i++)
    {
      length += this->arr[i] * this->arr[i];
    }

    return std::sqrt(length);
  }

  double getRandVectorElem() const
  {
    int randomIndex = std::rand() % size;
    return this->arr[randomIndex];
  }

  friend std::ostream &operator<<(std::ostream &out, const NVector &vec)
  {
    out << "[";
    for (unsigned i = 0; i < vec.size; ++i)
    {
      out << vec.arr[i];
      if (i < vec.size - 1)
        out << ", ";
    }
    out << "]";
    return out;
  }

  friend std::istream &operator>>(std::istream &in, NVector &vec)
  {
    delete[] vec.arr;

    std::cout << "Enter size: ";
    in >> vec.size;
    vec.arr = new double[vec.size];

    std::cout << "Enter " << vec.size << " elements:\n";
    for (unsigned i = 0; i < vec.size; ++i)
    {
      in >> vec.arr[i];
    }

    return in;
  }

private:
  double *arr;
  unsigned size;
};

int main()
{

  return 0;
}