#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector
{
public:
  MyVector() : data(nullptr), size(0), cap(2)
  {
    data = new T[cap];
  }

  explicit MyVector(size_t initialCapacity) : size(0), cap(initialCapacity)
  {
    data = new T[cap];
  }

  ~MyVector()
  {
    delete[] data;
  }

  MyVector(const MyVector &other)
      : data(new T[other.cap]),
        size(other.size),
        cap(other.cap)
  {
    for (size_t i = 0; i < size; ++i)
    {
      data[i] = other.data[i];
    }
  }

  MyVector &operator=(const MyVector &other)
  {
    if (this != &other)
    {

      T *newData = new T[other.cap];

      for (size_t i = 0; i < other.size; ++i)
      {
        newData[i] = other.data[i];
      }

      delete[] data;

      data = newData;
      size = other.size;
      cap = other.cap;
    }
    return *this;
  }

  void pushBack(const T &el)
  {
    if (size >= cap)
      resize();

    data[size++] = el;
  }

  void popBack()
  {
    if (size == 0)
      throw std::out_of_range("Vector is empty!");

    size--;
  }

  void insert(size_t index, const T &el)
  {
    if (index > size)
      throw std::invalid_argument("Invalid index!");

    if (size >= cap)
      resize();

    for (size_t i = size; i > index; --i)
    {
      data[i] = data[i - 1];
    }

    data[index] = el;
    size++;
  }

  void remove(size_t index)
  {
    if (index >= size)
      throw std::out_of_range("Invalid index!");

    for (size_t i = index; i < size - 1; ++i)
    {
      data[i] = data[i + 1];
    }

    size--;
  }

  size_t count() const
  {
    return size;
  }

  bool isEmpty() const
  {
    return size <= 0;
  }

  T &back() const
  {
    if (size <= 0 || !data)
      throw std::logic_error("Vector is still empty!");

    return data[size];
  }

  T &operator[](size_t index)
  {
    if (index >= size)
      throw std::invalid_argument("Invalid index!");

    return data[index];
  }

  void clear()
  {
    size = 0;
  }

  void print() const
  {
    if (isEmpty())
    {
      std::cout << "Vector is empty" << std::endl;
      return;
    }

    for (size_t i = 0; i < size; ++i)
    {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }

private:
  void resize()
  {
    cap *= 2;
    T *temp = new T[cap];
    for (size_t i = 0; i < size; ++i)
    {
      temp[i] = data[i];
    }
    delete[] data;
    data = temp;
  }

  T *data;
  size_t size;
  size_t cap;
};

int main()
{

  try
  {
    MyVector<int> vec1;
    vec1.pushBack(5);
    vec1.insert(0, 1);
    vec1.print();
    vec1.remove(0);
    vec1.print();
    int last = vec1.back();
    std::cout << "Last elem: " << last << std::endl;
    std::cout << vec1[0] << std::endl;
    vec1.clear();
    vec1.print();
  }
  catch (const std::exception &e)
  {
    std::cerr << "An error occurred: " << e.what() << std::endl;
  }

  return 0;
}