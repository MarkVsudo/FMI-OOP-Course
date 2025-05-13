#include <iostream>
#include <stdexcept>
#include <cstring>

class MyString
{
public:
  MyString(const char *str)
  {
    setStr(str);
  }

  MyString(const MyString &other)
  {
    setStr(other.str);
  }

  MyString &operator=(const MyString &other)
  {
    if (this != &other)
    {
      setStr(other.str);
    }

    return *this;
  }

  ~MyString()
  {
    delete[] str;
  }

  // at(index) - Връща символ от низа на даден индекс
  char at(unsigned index) const
  {
    if (strlen(str) - 1 < index)
      throw std::invalid_argument("Index exceeds string length");

    return str[index];
  }
  // front() - Връща първия елемент на низа, ако има такъв
  char front() const
  {
    if (strlen(str) < 1)
      throw std::logic_error("Cannot access first element since the string has a length of 0");

    return str[0];
  }
  // back() - Връща последния елемент на низа, ако има такъв
  char back() const
  {
    if (strlen(str) < 1)
      throw std::logic_error("Cannot access last element since the string has a length of 0");

    return str[strlen(str) - 1];
  }
  // c_str() - Връща самия низ, който се съдържа в MyString
  const char *c_str() const
  {
    return str;
  }
  // size() - Връща дължината на низа
  unsigned size() const
  {
    return strlen(str);
  }
  // capacity() - Връща количеството заделена памет за низа
  size_t capacity() const
  {
    return strCapacity;
  }

  // empty() - Връща дали стринга е празен
  bool empty() const
  {
    return strlen(str) < 1;
  }
  // append(<подходящ/и параметър/и>) - Долепя нов символ, низ или друг стринг
  void append(const char *otherStr)
  {
    size_t strLength = strlen(str);
    size_t newStrLength = strLength + strlen(otherStr);
    char *newStr = new char[newStrLength + 1];

    for (size_t i = 0; i < strLength; i++)
    {
      newStr[i] = str[i];
    }

    for (size_t i = strLength, j = 0; i < newStrLength; i++, j++)
    {
      newStr[i] = otherStr[j];
    }

    newStr[newStrLength] = '\0';

    setStrCapacity(newStrLength);
    delete[] str;
    str = newStr;
  }
  // clear() - Изчиства съдържанието на обекта, без да променя капацитета
  void clear()
  {
    if (str)
      str[0] = '\0'; // sets it to an empty string
  }

  // equals(<подходящ/и параметър/и) - Проверява дали два низа са равни
  bool equals(const char *otherStr) const
  {
    if (!otherStr)
      throw std::invalid_argument("Cannot pass a nullptr");

    return strcmp(str, otherStr) == 0;
  }
  // find(ch) - Намира индекса на първото срещане на даден символ. Ако такъв символ не е намерен, трябва да се върне -1.
  int find(char ch) const
  {
    for (size_t i = 0; i < strlen(str); i++)
    {
      if (str[i] == ch)
        return i;
    }

    return -1;
  }
  // find(str) - Намира индекса на първото срещане на подниза str в низа. Ако такъв подниз не е намерен, трябва да се върне -1.
  int find(const char *subStr) const
  {
    size_t strLength = strlen(str);
    size_t subStrLength = strlen(subStr);

    if (subStrLength == 0 || subStrLength > strLength)
      return -1;

    for (size_t i = 0; i <= strLength - subStrLength; i++)
    {
      if (strncmp(&str[i], subStr, subStrLength) == 0)
        return i;
    }

    return -1;
  }

  void setStr(const char *str)
  {
    if (!str)
      throw std::invalid_argument("Cannot pass an empty string!");

    delete[] this->str;

    unsigned strLength = strlen(str);
    setStrCapacity(strLength);
    this->str = new char[strLength + 1];
    strncpy(this->str, str, strLength);
    this->str[strLength] = '\0';
  }

  void setStrCapacity(size_t strCapacity)
  {
    this->strCapacity = strCapacity;
  }

  const char *getStr() const
  {
    return str;
  }

private:
  char *str;
  size_t strCapacity;
};

class Student
{
public:
  Student() : name("Unknown"), FN(1111111111), course(1) {}

  Student(MyString name, unsigned FN, unsigned course) : name(name)
  {
    setFN(FN);
    setCourse(course);
  }

  virtual ~Student() = default;

  Student(const Student &other) : name(other.name), FN(other.FN), course(other.course) {}

  Student &operator=(const Student &other)
  {
    if (this != &other)
    {
      this->name = other.name;
      this->FN = other.FN;
      this->course = other.course;
    }

    return *this;
  }

  void print() const
  {
    std::cout << "Name: " << name.c_str() << std::endl;
    std::cout << "FN: " << FN << std::endl;
    std::cout << "Course: " << course << std::endl;
  }

  void setFN(unsigned FN)
  {
    if (numLen(FN) != 10)
      throw std::invalid_argument("Faculty number should be 10 digits");

    this->FN = FN;
  }

  void setCourse(unsigned course)
  {
    if (course <= 0 || course > 4)
      throw std::invalid_argument("Course should be in range 1-4");

    this->course = course;
  }

  unsigned getFN() const
  {
    return FN;
  }

  unsigned getCourse() const
  {
    return course;
  }

  MyString getName() const
  {
    return name;
  }

private:
  unsigned numLen(unsigned num)
  {
    unsigned count = 0;
    do
    {
      count++;
      num /= 10;
    } while (num != 0);
    return count;
  }

  MyString name;
  unsigned FN;
  unsigned course;
};

class StudentDB
{
public:
  StudentDB() : students(nullptr), size(0) {}

  virtual ~StudentDB()
  {
    delete[] students;
  }

  void add(const Student &student)
  {
    if (size == 0)
    {
      size = 1;
      students = new Student[size];
      students[0] = student;
    }
    else
    {
      Student *newStudents = new Student[size + 1];
      for (size_t i = 0; i < size; ++i)
      {
        newStudents[i] = students[i];
      }
      newStudents[size] = student;
      delete[] students;
      students = newStudents;
      size++;
    }
  }

  void remove(unsigned FN)
  {
    if (size == 0)
    {
      throw std::logic_error("Student database is already empty");
    }

    int foundIndx = -1;
    for (size_t i = 0; i < size; ++i)
    {
      if (students[i].getFN() == FN)
      {
        foundIndx = i;
        break;
      }
    }

    if (foundIndx == -1)
    {
      throw std::invalid_argument("No student found with the given FN");
    }

    Student *newStudents = new Student[size - 1];
    for (size_t i = 0, j = 0; i < size; ++i)
    {
      if (i == foundIndx)
        continue;

      newStudents[j++] = students[i];
    }

    delete[] students;
    students = newStudents;
    size--;
  }

  Student *find(unsigned FN) const
  {
    if (size == 0)
    {
      throw std::logic_error("Student database is empty");
    }

    for (size_t i = 0; i < size; ++i)
    {
      if (students[i].getFN() == FN)
      {
        return &students[i];
      }
    }

    return nullptr;
  }

  void display() const
  {
    if (size <= 0 || !students)
      throw std::invalid_argument("No students in the DB");

    for (size_t i = 0; i < size; ++i)
    {
      std::cout << " -- Student " << i + 1 << " --\n";
      students[i].print();
    }
  }

protected:
  Student *students;
  size_t size;
};

enum class SortCriteria
{
  NAME,
  FN,
  COURSE
};

class SortedStudentDB : public StudentDB
{
public:
  void sortBy(SortCriteria criteria)
  {
    if (size <= 1)
      return;

    for (size_t i = 0; i < size - 1; ++i)
    {
      for (size_t j = 0; j < size - i - 1; ++j)
      {
        if (shouldSwap(students[j], students[j + 1], criteria))
        {
          Student temp = students[j];
          students[j] = students[j + 1];
          students[j + 1] = temp;
        }
      }
    }
  }

private:
  bool shouldSwap(const Student &a, const Student &b, SortCriteria criteria)
  {
    switch (criteria)
    {
    case SortCriteria::NAME:
      return strcmp(a.getName().c_str(), b.getName().c_str()) > 0;
    case SortCriteria::FN:
      return a.getFN() > b.getFN();
    case SortCriteria::COURSE:
      return a.getCourse() > b.getCourse();
    default:
      return false;
    }
  }
};

bool isSecondYear(const Student &student)
{
  return student.getCourse() == 2;
}

class FilteredStudentDB : public StudentDB
{
public:
  void filter(bool (*predicate)(const Student &))
  {
    if (size == 0)
      throw std::logic_error("No students registered in the database");

    size_t newSize = 0;
    for (size_t i = 0; i < size; ++i)
    {
      if (predicate(students[i]))
        newSize++;
    }

    Student *filtered = new Student[newSize];
    size_t j = 0;
    for (size_t i = 0; i < size; ++i)
    {
      if (predicate(students[i]))
      {
        filtered[j++] = students[i];
      }
    }

    delete[] students;
    students = filtered;
    size = newSize;
  }

  void limit(unsigned N)
  {
    if (size == 0)
      throw std::logic_error("No students registered in the database");

    if (N > size)
    {
      std::cerr << "Warning: limit exceeds current size. No changes made.\n";
      return;
    }

    Student *newStudents = new Student[N];
    for (size_t i = 0; i < N; ++i)
      newStudents[i] = students[i];
    delete[] students;
    size = N;
  }
};

int main()
{
  try
  {
    Student student1("Mark Veskov", 1234567890, 1);
    StudentDB studentDB;
    studentDB.add(student1);
    Student *foundStudent = studentDB.find(1232567890);
    if (foundStudent)
    {
      foundStudent->print();
    }
    else
    {
      std::cout << "No student found with this FN" << std::endl;
    }
    studentDB.display();
    Student student2("Ivan Minchev", 2345678901, 2);
    studentDB.add(student2);
    studentDB.display();
    studentDB.remove(1234567890);
    studentDB.display();
  }
  catch (std::exception &e)
  {
    std::cerr << "An error occured: " << e.what() << std::endl;
  }

  return 0;
}