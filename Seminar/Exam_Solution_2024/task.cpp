#include <iostream>
#include <fstream>
#include <stdexcept>

// Абстрактен базов клас
template <typename T>
class DataSource
{
public:
  virtual ~DataSource() {}

  virtual bool next(T &out) = 0;
  virtual int nextN(T *arr, int count) = 0;
  virtual bool hasNext() const = 0;
  virtual bool reset() = 0;

  T operator()()
  {
    T temp;
    if (!next(temp))
      throw std::out_of_range("No more elements");
    return temp;
  }

  DataSource<T> &operator>>(T &out)
  {
    if (!next(out))
      throw std::out_of_range("No more elements to extract");
    return *this;
  }

  operator bool() const
  {
    return hasNext();
  }
};

// 1. DefaultDataSource – връща безкрайно много подразбиращо се конструирани елементи
template <typename T>
class DefaultDataSource : public DataSource<T>
{
public:
  bool next(T &out) override
  {
    out = T();
    return true;
  }

  int nextN(T *arr, int count) override
  {
    for (int i = 0; i < count; ++i)
      arr[i] = T();
    return count;
  }

  bool hasNext() const override { return true; }
  bool reset() override { return true; }
};

// 2. FileDataSource – чете елементи от файл
template <typename T>
class FileDataSource : public DataSource<T>
{
  std::ifstream file;
  const char *filename;

public:
  FileDataSource(const char *fname) : filename(fname), file(fname) {}

  bool next(T &out) override
  {
    return (file >> out);
  }

  int nextN(T *arr, int count) override
  {
    int i = 0;
    while (i < count && file >> arr[i])
      ++i;
    return i;
  }

  bool hasNext() const override
  {
    return file && !file.eof();
  }

  bool reset() override
  {
    file.close();
    file.open(filename);
    return file.is_open();
  }
};

// 3. ArrayDataSource – връща елементи от масив
template <typename T, int MaxSize = 100>
class ArrayDataSource : public DataSource<T>
{
  T data[MaxSize];
  int size;
  int index;

public:
  ArrayDataSource() : size(0), index(0) {}

  bool next(T &out) override
  {
    if (index < size)
    {
      out = data[index++];
      return true;
    }
    return false;
  }

  int nextN(T *arr, int count) override
  {
    int i = 0;
    while (i < count && index < size)
      arr[i++] = data[index++];
    return i;
  }

  bool hasNext() const override
  {
    return index < size;
  }

  bool reset() override
  {
    index = 0;
    return true;
  }

  // Добавяне на елемент
  ArrayDataSource &operator+=(const T &value)
  {
    if (size < MaxSize)
      data[size++] = value;
    return *this;
  }

  ArrayDataSource operator+(const T &value) const
  {
    ArrayDataSource result = *this;
    result += value;
    return result;
  }

  // Връщане назад
  ArrayDataSource &operator--()
  {
    if (index > 0)
      --index;
    return *this;
  }
};

// 4. AlternateDataSource – обикаля по източници на кръг
template <typename T, int MaxSources = 10>
class AlternateDataSource : public DataSource<T>
{
  DataSource<T> *sources[MaxSources];
  int count;
  int current;

public:
  AlternateDataSource(DataSource<T> **srcs, int n) : count(n), current(0)
  {
    for (int i = 0; i < n; ++i)
      sources[i] = srcs[i];
  }

  bool next(T &out) override
  {
    int tried = 0;
    while (tried < count)
    {
      if (sources[current]->next(out))
      {
        current = (current + 1) % count;
        return true;
      }
      current = (current + 1) % count;
      ++tried;
    }
    return false;
  }

  int nextN(T *arr, int cnt) override
  {
    int i = 0;
    while (i < cnt && next(arr[i]))
      ++i;
    return i;
  }

  bool hasNext() const override
  {
    for (int i = 0; i < count; ++i)
      if (sources[i]->hasNext())
        return true;
    return false;
  }

  bool reset() override
  {
    bool all = true;
    for (int i = 0; i < count; ++i)
      all = all && sources[i]->reset();
    current = 0;
    return all;
  }
};

// 5. GeneratorDataSource – генерира елементи чрез функция-подобен обект
template <typename T, typename Generator>
class GeneratorDataSource : public DataSource<T>
{
  Generator gen;

public:
  GeneratorDataSource(Generator g) : gen(g) {}

  bool next(T &out) override
  {
    out = gen();
    return true;
  }

  int nextN(T *arr, int count) override
  {
    for (int i = 0; i < count; ++i)
      arr[i] = gen();
    return count;
  }

  bool hasNext() const override { return true; }
  bool reset() override { return false; }
};

// === ТЕСТ ===
int main()
{
  ArrayDataSource<int> arr;
  arr += 10;
  arr += 20;
  arr += 30;

  std::cout << "ArrayDataSource:\n";
  int x;
  while (arr >> x)
  {
    std::cout << x << " ";
  }
  std::cout << "\n";

  arr.reset();
  --arr; // връщаме 1 назад
  arr >> x;
  std::cout << "След reset и --: " << x << "\n";

  DefaultDataSource<int> def;
  std::cout << "DefaultDataSource: " << def() << " " << def() << "\n";

  // GeneratorDataSource < int, struct
  // {
  //   int operator()() { return rand() % 100; }
  // } > genSrc({});
  // std::cout << "GeneratorDataSource: " << genSrc() << " " << genSrc() << "\n";

  DataSource<int> *sources[2] = {&arr, &def};
  AlternateDataSource<int, 2> alt(sources, 2);

  std::cout << "AlternateDataSource:\n";
  for (int i = 0; i < 5; ++i)
    std::cout << alt() << " ";

  return 0;
}
