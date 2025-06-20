#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// ============================================================
// Абстрактен шаблонен клас DataContainer<T>
// ============================================================
template <typename T>
class DataContainer
{
public:
  virtual bool insert(const T &) = 0;
  virtual bool remove(T &) = 0;
  virtual bool peek(T &) const = 0;
  virtual bool empty() const = 0;
  virtual bool reset() = 0;
  virtual DataContainer<T> *clone() const = 0;

  virtual ~DataContainer() {}

  virtual operator bool() const
  {
    return !empty();
  }

  DataContainer<T> &operator<<(const T &value)
  {
    insert(value);
    return *this;
  }

  DataContainer<T> &operator>>(T &value)
  {
    remove(value);
    return *this;
  }
};

// ============================================================
// FixedArrayContainer<T, N> - без опашково поведение
// ============================================================
template <typename T, size_t N>
class FixedArrayContainer : public DataContainer<T>
{
  T data[N];
  size_t count;
  size_t index;

public:
  FixedArrayContainer() : count(0), index(0) {}

  bool insert(const T &value) override
  {
    if (count >= N)
      return false;
    data[count++] = value;
    return true;
  }

  bool remove(T &value) override
  {
    if (index >= count)
      return false;
    value = data[index++];
    return true;
  }

  bool peek(T &value) const override
  {
    if (index >= count)
      return false;
    value = data[index];
    return true;
  }

  bool empty() const override
  {
    return index >= count;
  }

  bool reset() override
  {
    index = 0;
    return true;
  }

  DataContainer<T> *clone() const override
  {
    FixedArrayContainer<T, N> *copy = new FixedArrayContainer<T, N>();
    for (size_t i = 0; i < count; ++i)
      copy->insert(data[i]);
    return copy;
  }
};

// ============================================================
// FileBackedContainer<T> (поддържа само char масиви)
// ============================================================
template <typename T>
class FileBackedContainer : public DataContainer<T>
{
  ifstream file;
  const char *filename;

public:
  FileBackedContainer(const char *fname) : filename(fname)
  {
    file.open(fname);
    if (!file.is_open())
      throw runtime_error("Cannot open file.");
  }

  ~FileBackedContainer()
  {
    file.close();
  }

  bool insert(const T &) override
  {
    return false; // Read-only
  }

  bool remove(T &value) override
  {
    file.read((char *)&value, sizeof(T));
    return file.gcount() == sizeof(T);
  }

  bool peek(T &) const override
  {
    return false; // Unsupported
  }

  bool empty() const override
  {
    return file.eof();
  }

  bool reset() override
  {
    file.clear();
    file.seekg(0);
    return true;
  }

  DataContainer<T> *clone() const override
  {
    return new FileBackedContainer<T>(filename);
  }
};

// ============================================================
// FilteredContainer<T>
// ============================================================
template <typename T>
class FilteredContainer : public DataContainer<T>
{
  DataContainer<T> *base;
  bool (*predicate)(const T &);

public:
  FilteredContainer(DataContainer<T> *base_, bool (*pred)(const T &))
      : base(base_), predicate(pred) {}

  bool insert(const T &val) override
  {
    return predicate(val) && base->insert(val);
  }

  bool remove(T &val) override
  {
    while (*base)
    {
      T temp;
      if (!base->remove(temp))
        return false;
      if (predicate(temp))
      {
        val = temp;
        return true;
      }
    }
    return false;
  }

  bool peek(T &val) const override
  {
    return false; // Unsupported
  }

  bool empty() const override
  {
    return !(*base);
  }

  bool reset() override
  {
    return base->reset();
  }

  DataContainer<T> *clone() const override
  {
    return new FilteredContainer<T>(base->clone(), predicate);
  }
};

// ============================================================
// CompositeContainer<T>
// ============================================================
template <typename T>
class CompositeContainer : public DataContainer<T>
{
  DataContainer<T> **containers;
  size_t count;
  size_t index;

public:
  CompositeContainer(DataContainer<T> **conts, size_t cnt)
      : containers(conts), count(cnt), index(0) {}

  bool insert(const T &) override
  {
    return false; // Read-only composite
  }

  bool remove(T &val) override
  {
    for (size_t i = 0; i < count; ++i)
    {
      size_t current = (index + i) % count;
      if (*(containers[current]))
      {
        index = (current + 1) % count;
        return containers[current]->remove(val);
      }
    }
    return false;
  }

  bool peek(T &) const override
  {
    return false;
  }

  bool empty() const override
  {
    for (size_t i = 0; i < count; ++i)
      if (*(containers[i]))
        return false;
    return true;
  }

  bool reset() override
  {
    bool result = true;
    for (size_t i = 0; i < count; ++i)
      result &= containers[i]->reset();
    return result;
  }

  DataContainer<T> *clone() const override
  {
    DataContainer<T> **clones = new DataContainer<T> *[count];
    for (size_t i = 0; i < count; ++i)
      clones[i] = containers[i]->clone();
    return new CompositeContainer<T>(clones, count);
  }
};

// ============================================================
// Помощна функция: запис в бинарен файл
// ============================================================
template <typename T>
void save_to_binary_file(DataContainer<T> &container, const char *filename, size_t count)
{
  ofstream out(filename, ios::binary);
  if (!out.is_open())
    throw runtime_error("Cannot open output file.");
  for (size_t i = 0; i < count && container; ++i)
  {
    T value;
    container >> value;
    out.write((char *)&value, sizeof(T));
  }
  out.close();
}

// ============================================================
// Филтър: четни числа
// ============================================================
bool is_even(const int &x)
{
  return x % 2 == 0;
}

// Филтър: низ, започващ с 'a'
bool starts_with_a(const char (&s)[11])
{
  return s[0] == 'a';
}

// ============================================================
// main()
// ============================================================
int main()
{
  srand(time(0));

  // --- Демонстрация с цели числа ---
  FixedArrayContainer<int, 100> ints;
  for (int i = 0; i < 100; ++i)
    ints.insert(i);

  FilteredContainer<int> evens(&ints, is_even);

  DataContainer<int> *containers[] = {&ints, &evens};
  CompositeContainer<int> composite(containers, 2);

  char filename1[256];
  cout << "Enter binary filename for 50 even integers: ";
  cin >> filename1;
  save_to_binary_file(evens, filename1, 50);

  // --- Демонстрация с низове ---
  FixedArrayContainer<char[11], 100> strings;
  for (int i = 0; i < 100; ++i)
  {
    char temp[11];
    for (int j = 0; j < 10; ++j)
      temp[j] = 'a' + rand() % 26;
    temp[10] = '\0';
    strings.insert(temp);
  }

  FilteredContainer<char[11]> filtered_strs(&strings, starts_with_a);

  char filename2[256];
  cout << "Enter binary filename for 50 strings starting with 'a': ";
  cin >> filename2;
  save_to_binary_file(filtered_strs, filename2, 50);

  return 0;
}
