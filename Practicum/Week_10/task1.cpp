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

class Ticket
{
public:
  Ticket() : name("Undefined"), price(0.00) {}
  Ticket(MyString name, double price) : name(name)
  {
    setPrice(price);
  }

  Ticket(const Ticket &other) : name(other.name), price(other.price) {}

  virtual ~Ticket() = default;

  virtual void printInfo() const
  {
    std::cout << "Ticket: " << name.c_str() << ", Price: " << price << " BGN\n";
  }

protected:
  void setPrice(double price)
  {
    if (price < 0.00)
      throw std::invalid_argument("Price cannot be less than 0.00");
    this->price = price;
  }

  MyString name;
  double price;
};

class StudentTicket : public Ticket
{
public:
  StudentTicket(MyString name, double originalPrice)
      : Ticket(name, originalPrice / 2.0)
  {
  }

  void printInfo() const override
  {
    std::cout << "Student Ticket: " << name.c_str() << ", Price: " << price << " BGN\n";
  }
};

class GroupTicket : public Ticket
{
public:
  GroupTicket(MyString name, double originalPrice)
      : Ticket(name, originalPrice * 0.8)
  {
  }

  void printInfo() const override
  {
    std::cout << "Group Ticket: " << name.c_str() << ", Price: " << price << " BGN\n";
  }
};

int main()
{
  Ticket regular("Theatre Play", 20.00);
  StudentTicket student("Theatre Play", 20.00);
  GroupTicket group("Theatre Play", 20.00);

  Ticket *tickets[] = {&regular, &student, &group};

  for (Ticket *t : tickets)
  {
    t->printInfo();
  }

  return 0;
}
