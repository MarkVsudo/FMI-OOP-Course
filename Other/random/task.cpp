#include <iostream>
#include <stdexcept>
#include <cstring>

class Member
{
public:
  Member()
  {
    setUsername("Undefined");
    setPassword("Undefined");
  }

  Member(const char *username, const char *password) : username(nullptr), password(nullptr)
  {
    setUsername(username);
    setPassword(password);
  }

  virtual ~Member()
  {
    delete[] username;
    delete[] password;
  }

  Member(const Member &other) : username(nullptr), password(nullptr)
  {
    setUsername(other.username);
    setPassword(other.password);
  }

  Member &operator=(const Member &other)
  {
    if (this != &other)
    {
      setUsername(other.username);
      setPassword(other.password);
    }

    return *this;
  }

  bool operator==(const Member &other) const
  {
    return !strcmp(this->username, other.username);
  }

  bool operator!=(const Member &other) const
  {
    return !(*this == other);
  }

  virtual void print(std::ostream &out) const
  {
    out << "Username: " << username << " Password: " << password << std::endl;
  }

  friend std::ostream &operator<<(std::ostream &out, const Member &member)
  {
    member.print(out);
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Member &member)
  {
    char tempUsername[256];
    char tempPassword[256];

    std::cout << "Enter username: ";
    in >> tempUsername;
    std::cout << "Enter password: ";
    in >> tempPassword;

    member.setUsername(tempUsername);
    member.setPassword(tempPassword);

    return in;
  }

  void setPassword(const char *password)
  {
    if (!password)
      throw std::invalid_argument("Password cannot be null");

    size_t len = strlen(password);

    if (len < 8)
      throw std::invalid_argument("Password must be at least 8 characters");

    delete[] this->password;
    this->password = new char[len + 1];
    strcpy(this->password, password);
  }

  const char *getUsername() const { return username; }
  const char *getPassword() const { return password; }

protected:
  char *username;
  char *password;

private:
  void setUsername(const char *username)
  {
    if (!username)
      throw std::invalid_argument("Username cannot be null");

    for (size_t i = 0; username[i] != '\0'; ++i)
    {
      if (username[i] == ' ')
        throw std::invalid_argument("Username cannot have empty spaces");
    }

    size_t len = strlen(username);
    delete[] this->username;
    this->username = new char[len + 1];
    strcpy(this->username, username);
  }
};

class Moderator : public Member
{
public:
  Moderator() : Member(), level(1), handledReports(0) {}

  Moderator(const char *username, const char *password, unsigned level, unsigned handledReports) : Member(username, password), level(level), handledReports(handledReports)
  {
    if (level < 1 || level > 10)
      throw std::invalid_argument("Level must be between 1-10");

    if (handledReports < 0)
      throw std::invalid_argument("Handled reports must be a non-negative number");
  }

  virtual ~Moderator() = default;

  Moderator(const Moderator &other) : Member(other), level(other.level), handledReports(other.handledReports) {}

  Moderator &operator=(const Moderator &other)
  {
    if (this != &other)
    {
      Member::operator=(other);
      this->level = other.level;
      this->handledReports = other.handledReports;
    }
    return *this;
  }

  void reviewReport()
  {
    // handledReports++;
    // ...
  }

  bool operator<(const Moderator &other) const
  {
    if (this->level == other.level)
    {
      return this->handledReports < other.handledReports;
    }

    return this->level < other.level;
  }

  bool operator>(const Moderator &other) const
  {
    return !(*this < other);
  }

  Moderator operator++(int)
  {
    Moderator temp = *this;
    if (level == 10)
      throw std::logic_error("Max experience level is 10");
    level += 1;
    return temp;
  }

  Moderator &operator++()
  {
    if (level == 10)
      throw std::logic_error("Max experience level is 10");
    ++level;
    return *this;
  }

  Moderator operator--(int)
  {
    Moderator temp = *this;
    if (level == 1)
      throw std::logic_error("Min experience level is 1");
    level -= 1;
    return temp;
  }

  Moderator &operator--()
  {
    if (level == 1)
      throw std::logic_error("Min experience level is 1");
    --level;
    return *this;
  }

  void print(std::ostream &out) const override
  {
    Member::print(out);
    out << " Level: " << level << " Reports: " << handledReports;
  }

  friend std::ostream &operator<<(std::ostream &out, const Moderator &moderator)
  {
    moderator.print(out);
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Moderator &moderator)
  {
    char username[256], password[256];
    unsigned level, reports;

    std::cout << "Username: ";
    in >> username;
    std::cout << "Password: ";
    in >> password;
    std::cout << "Level: ";
    in >> level;
    std::cout << "Handled Reports: ";
    in >> reports;

    moderator = Moderator(username, password, level, reports);
  }

  unsigned getLevel() const { return level; }
  unsigned getHandledReports() const { return handledReports; }

protected:
  unsigned level;
  unsigned handledReports;
};

class SuperModerator : public Moderator
{
public:
  SuperModerator() : Moderator(), bannedUsers(nullptr), size(0), cap(2)
  {
    bannedUsers = new char *[cap];
  }

  SuperModerator(const char *username, const char *password, unsigned level, unsigned handledReports)
      : Moderator(username, password, level, handledReports), size(0), cap(2)
  {
    bannedUsers = new char *[cap];
  }

  SuperModerator(const SuperModerator &other) : Moderator(other), size(other.size), cap(other.cap)
  {
    bannedUsers = new char *[cap];
    for (int i = 0; i < size; ++i)
    {
      size_t len = strlen(other.bannedUsers[i]);
      bannedUsers[i] = new char[len + 1];
      strcpy(bannedUsers[i], other.bannedUsers[i]);
    }
  }

  SuperModerator &operator=(const SuperModerator &other)
  {
    if (this != &other)
    {
      Moderator::operator=(other);
      freeMem();

      size = other.size;
      cap = other.cap;
      bannedUsers = new char *[cap];
      for (int i = 0; i < size; ++i)
      {
        size_t len = strlen(other.bannedUsers[i]);
        bannedUsers[i] = new char[len + 1];
        strcpy(bannedUsers[i], other.bannedUsers[i]);
      }
    }
    return *this;
  }

  ~SuperModerator()
  {
    freeMem();
  }

  void operator()(const Member &member)
  {
    for (int i = 0; i < size; ++i)
    {
      if (strcmp(bannedUsers[i], member.getUsername()) == 0)
      {
        std::cout << "User: " << member.getUsername() << " is already banned" << std::endl;
        return;
      }
    }

    if (size >= cap)
    {
      cap *= 2;
      char **temp = new char *[cap];
      for (int i = 0; i < size; ++i)
      {
        temp[i] = bannedUsers[i];
      }
      delete[] bannedUsers;
      bannedUsers = temp;
    }

    size_t len = strlen(member.getUsername());
    bannedUsers[size] = new char[len + 1];
    strcpy(bannedUsers[size], member.getUsername());
    ++size;

    std::cout << "User: " << member.getUsername() << " has been banned" << std::endl;
  }

  bool operator[](const char *name) const
  {
    for (int i = 0; i < size; ++i)
    {
      if (strcmp(bannedUsers[i], name) == 0)
        return true;
    }
    return false;
  }

  void print(std::ostream &out) const override
  {
    Moderator::print(out);
    for (int i = 0; i < size; ++i)
    {
      out << "Banned user " << i + 1 << ": " << bannedUsers[i] << std::endl;
    }
  }

  friend std::ostream &operator<<(std::ostream &out, const SuperModerator &supModerator)
  {
    supModerator.print(out);
    return out;
  }

  friend std::istream &operator>>(std::istream &in, SuperModerator &supModerator)
  {
    char username[256], password[256];
    unsigned level, reports;

    std::cout << "Username: ";
    in >> username;
    std::cout << "Password: ";
    in >> password;
    std::cout << "Level: ";
    in >> level;
    std::cout << "Handled Reports: ";
    in >> reports;

    supModerator = SuperModerator(username, password, level, reports);
    return in;
  }

private:
  void freeMem()
  {
    if (bannedUsers != nullptr)
    {
      for (int i = 0; i < size; ++i)
      {
        delete[] bannedUsers[i];
      }
      delete[] bannedUsers;
      bannedUsers = nullptr;
    }

    size = 0;
    cap = 2;
  }

  char **bannedUsers;
  int size;
  int cap;
};

class Forum
{
};

int main()
{

  try
  {
    Member member1;
    Member member2;
    std::cout << ((member1 == member2) ? "True" : "False") << std::endl;
    std::cout << ((member1 != member2) ? "True" : "False") << std::endl;
    std::cout << member1;

    Moderator moderator1("Mark", "password123", 10, 5);
    std::cout << moderator1;
  }
  catch (const std::exception &err)
  {
    std::cerr << "An error occurred: " << err.what() << std::endl;
  }

  return 0;
}