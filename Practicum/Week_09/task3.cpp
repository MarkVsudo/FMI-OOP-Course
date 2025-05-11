#include <iostream>
#include <stdexcept>

class Matrix
{
public:
  Matrix()
  {
    rowsCount = 2;
    colsCount = 2;

    matrix = new int *[rowsCount];
    for (int i = 0; i < rowsCount; ++i)
    {
      matrix[i] = new int[colsCount];
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j] = 0;
      }
    }
  }

  Matrix(int rowsCount, int colsCount)
      : rowsCount(rowsCount), colsCount(colsCount)
  {
    if (rowsCount <= 0 || colsCount <= 0)
      throw std::invalid_argument("Matrix dimensions must be positive");

    matrix = new int *[rowsCount];
    for (int i = 0; i < rowsCount; ++i)
    {
      matrix[i] = new int[colsCount];
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j] = 0;
      }
    }
  }

  Matrix(const Matrix &other)
  {
    this->rowsCount = other.rowsCount;
    this->colsCount = other.colsCount;

    matrix = new int *[rowsCount];
    for (int i = 0; i < rowsCount; ++i)
    {
      matrix[i] = new int[colsCount];
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j] = other.matrix[i][j];
      }
    }
  }

  Matrix(Matrix &&other) noexcept
  {
    matrix = other.matrix;
    rowsCount = other.rowsCount;
    colsCount = other.colsCount;

    other.matrix = nullptr;
    other.rowsCount = 0;
    other.colsCount = 0;
  }

  Matrix &operator=(Matrix &&other) noexcept
  {
    if (this != &other)
    {
      for (int i = 0; i < rowsCount; ++i)
        delete[] matrix[i];
      delete[] matrix;

      matrix = other.matrix;
      rowsCount = other.rowsCount;
      colsCount = other.colsCount;

      other.matrix = nullptr;
      other.rowsCount = 0;
      other.colsCount = 0;
    }
    return *this;
  }

  Matrix &operator=(const Matrix &other)
  {
    if (this != &other)
    {
      for (int i = 0; i < rowsCount; ++i)
      {
        delete[] matrix[i];
      }
      delete[] matrix;

      rowsCount = other.rowsCount;
      colsCount = other.colsCount;

      matrix = new int *[rowsCount];
      for (int i = 0; i < rowsCount; ++i)
      {
        matrix[i] = new int[colsCount];
      }

      for (int i = 0; i < rowsCount; ++i)
      {
        for (int j = 0; j < colsCount; ++j)
        {
          matrix[i][j] = other.matrix[i][j];
        }
      }
    }

    return *this;
  }

  ~Matrix()
  {
    for (int i = 0; i < rowsCount; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  Matrix &operator+=(const Matrix &other)
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      throw std::invalid_argument("Matrices must be the same size");

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j] += other.matrix[i][j];
      }
    }

    return *this;
  }

  Matrix operator+(const Matrix &other) const
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      throw std::invalid_argument("Matrices must be the same size");

    Matrix result(rowsCount, colsCount);

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
      }
    }

    return result;
  }

  Matrix &operator-=(const Matrix &other)
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      throw std::invalid_argument("Matrices must be the same size");

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j] -= other.matrix[i][j];
      }
    }

    return *this;
  }

  Matrix &operator++()
  {
    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j]++;
      }
    }

    return *this;
  }

  Matrix operator++(int)
  {
    Matrix temp = *this; // Step 1: Save current state
    ++(*this);           // Step 2: Use prefix to increment
    return temp;         // Step 3: Return old value
  }

  Matrix &operator--()
  {
    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j]--;
      }
    }

    return *this;
  }

  Matrix operator--(int)
  {
    Matrix temp = *this;
    --(*this);
    return temp;
  }

  Matrix &operator*=(int num)
  {
    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j] *= num;
      }
    }

    return *this;
  }

  Matrix operator*(int num) const
  {
    Matrix result(rowsCount, colsCount);

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        result.matrix[i][j] = this->matrix[i][j] * num;
      }
    }

    return result;
  }

  Matrix &operator*=(const Matrix &other)
  {
    if (colsCount != other.rowsCount)
      throw std::invalid_argument("Cannot multiply matrices with the given sizes");

    Matrix result(rowsCount, other.colsCount);

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < other.colsCount; ++j)
      {
        result.matrix[i][j] = 0;
        for (int k = 0; k < colsCount; ++k)
        {
          result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        }
      }
    }

    for (int i = 0; i < rowsCount; ++i)
      delete[] matrix[i];
    delete[] matrix;

    rowsCount = result.rowsCount;
    colsCount = result.colsCount;

    matrix = new int *[rowsCount];
    for (int i = 0; i < rowsCount; ++i)
    {
      matrix[i] = new int[colsCount];
      for (int j = 0; j < colsCount; ++j)
      {
        matrix[i][j] = result.matrix[i][j];
      }
    }

    return *this;
  }

  Matrix operator*(const Matrix &other) const
  {
    if (colsCount != other.rowsCount)
      throw std::invalid_argument("Cannot multiply matrices with the given sizes");

    Matrix result(rowsCount, other.colsCount);

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < other.colsCount; ++j)
      {
        result.matrix[i][j] = 0;
        for (int k = 0; k < colsCount; ++k)
        {
          result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        }
      }
    }

    return result;
  }

  bool operator==(const Matrix &other) const
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      return false;

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        if (this->matrix[i][j] != other.matrix[i][j])
          return false;
      }
    }

    return true;
  }

  bool operator!=(const Matrix &other) const
  {
    return !(*this == other);
  }

  int *operator[](int index)
  {
    if (index < 0 || index >= rowsCount)
      throw std::out_of_range("Index out of range");

    return matrix[index];
  }

  const int *operator[](int index) const
  {
    if (index < 0 || index >= rowsCount)
      throw std::out_of_range("Index out of range");

    return matrix[index];
  }

  bool operator<(const Matrix &other) const
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      throw std::invalid_argument("Matrices must have the same size to compare");

    return sumElements() < other.sumElements();
  }

  bool operator>=(const Matrix &other) const
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      throw std::invalid_argument("Matrices must have the same size to compare");

    return sumElements() >= other.sumElements();
  }

  bool operator>(const Matrix &other) const
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      throw std::invalid_argument("Matrices must have the same size to compare");

    return sumElements() > other.sumElements();
  }

  bool operator<=(const Matrix &other) const
  {
    if (rowsCount != other.rowsCount || colsCount != other.colsCount)
      throw std::invalid_argument("Matrices must have the same size to compare");

    return sumElements() <= other.sumElements();
  }

  Matrix operator()() const
  {
    Matrix resultMatrix(colsCount, rowsCount);

    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        resultMatrix.matrix[j][i] = this->matrix[i][j];
      }
    }

    return resultMatrix;
  }

  // ? explicit operator
  operator bool() const
  {
    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        if (this->matrix[i][j] != 0)
          return true;
      }
    }

    return false;
  }

  void print() const
  {
    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        std::cout << matrix[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  int sumElements() const
  {
    int sum = 0;
    for (int i = 0; i < rowsCount; ++i)
    {
      for (int j = 0; j < colsCount; ++j)
      {
        sum += matrix[i][j];
      }
    }
    return sum;
  }

  int **matrix;
  int rowsCount;
  int colsCount;
};

int main()
{

  return 0;
}