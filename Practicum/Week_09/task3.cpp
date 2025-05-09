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
  {
    this->rowsCount = rowsCount;
    this->colsCount = colsCount;

    matrix = new int *[rowsCount];
    for (int i = 0; i < rowsCount; ++i)
    {
      matrix[i] = new int[colsCount];
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

  Matrix operator+=(const Matrix &other) const
  {
  }

  Matrix operator+(const Matrix &other) const
  {
  }

  Matrix operator-=(const Matrix &other) const
  {
  }

  Matrix &operator++()
  {
  }

  Matrix operator++(int)
  {
  }

  Matrix &operator--()
  {
  }

  Matrix operator--(int)
  {
  }

  Matrix operator*=(int num) const
  {
  }

  Matrix operator*(int num) const
  {
  }

  Matrix operator*=(const Matrix &other) const
  {
  }

  Matrix operator*(const Matrix &other) const
  {
  }

  bool operator==(const Matrix &other) const
  {
  }

  bool operator!=(const Matrix &other) const
  {
  }

  int *operator[](int index)
  {
    return matrix[index];
  }

  const int *operator[](int index) const
  {
    return matrix[index];
  }

  bool operator<(const Matrix &other) const
  {
  }

  bool operator>=(const Matrix &other) const
  {
  }

  bool operator>(const Matrix &other) const
  {
  }

  bool operator<=(const Matrix &other) const
  {
  }

  Matrix operator()() const
  {
  }

  operator bool() const
  {
  }

private:
  int **matrix;
  int rowsCount;
  int colsCount;
};

int main()
{

  return 0;
}