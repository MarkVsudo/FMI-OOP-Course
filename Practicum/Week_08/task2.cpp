#include <iostream>
#include <cstring>
#include <stdexcept>

class User;

class Book
{
public:
  Book() : id(genId()), title(nullptr), author(nullptr), isAvailable(false), renter(nullptr)
  {
    setTitle("No title");
    setAuthor("No author");
  }

  Book(const char *title, const char *author, bool isAvailable) : id(genId()), renter(nullptr)
  {
    setTitle(title);
    setAuthor(author);
    setAvailability(isAvailable);
  }

  Book(const Book &other)
  {
    setId(other.id);
    setTitle(other.title);
    setAuthor(other.author);
    setAvailability(other.isAvailable);
    this->renter = other.renter;
  }

  Book &operator=(const Book &other)
  {
    if (this != &other)
    {
      setId(other.id);
      setTitle(other.title);
      setAuthor(other.author);
      setAvailability(other.isAvailable);
      this->renter = other.renter;
    }
    return *this;
  }

  ~Book()
  {
    delete[] title;
    delete[] author;
  }

  void print() const
  {
    std::cout << "Id: " << id << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Is available: " << std::boolalpha << isAvailable << std::noboolalpha << std::endl;
  }

  void setId(int id)
  {
    this->id = id;
  }

  void setTitle(const char *title)
  {
    if (!title)
      throw std::invalid_argument("Cannot set a nullptr for title");

    if (this->title)
      delete[] this->title;

    size_t len = strlen(title);
    this->title = new char[len + 1];
    strncpy(this->title, title, len);
    this->title[len] = '\0';
  }

  void setAuthor(const char *author)
  {
    if (!author)
      throw std::invalid_argument("Cannot set a nullptr for author");

    if (this->author)
      delete[] this->author;

    size_t len = strlen(author);
    this->author = new char[len + 1];
    strncpy(this->author, author, len);
    this->author[len] = '\0';
  }

  void setAvailability(bool isAvailable)
  {
    this->isAvailable = isAvailable;
  }

  void setRenter(User *renter)
  {
    this->renter = renter;
    setAvailability(renter == nullptr);
  }

  const char *getTitle() const
  {
    return title;
  }

  const char *getAuthor() const
  {
    return author;
  }

  bool getAvailability() const
  {
    return isAvailable;
  }

  int getId() const
  {
    return id;
  }

private:
  char *title;
  char *author;
  bool isAvailable;
  int id;
  User *renter;
  static int genId()
  {
    static int nextId = 0;
    return ++nextId;
  }
};

class User
{
public:
  User(const char *username, const char *number)
  {
    setUsername(username);
    setNumber(number);
    registerInstance(this); // Register the new user
  }

  User(const User &other)
  {
    setUsername(other.username);
    setNumber(other.number);
    registerInstance(this); // Register the copied user
  }

  User &operator=(const User &other)
  {
    if (this != &other)
    {
      setUsername(other.username);
      setNumber(other.number);
    }

    return *this;
  }

  ~User()
  {
    delete[] username;
    delete[] number;
    // (Optional) Deregister logic can go here if needed
  }

  void setUsername(const char *username)
  {
    if (!username)
      throw std::invalid_argument("Cannot pass a nullptr as a username");

    if (strlen(username) > 8)
      throw std::logic_error("The username should be 8 chars at most");

    delete[] this->username;
    size_t len = strlen(username);
    this->username = new char[len + 1];
    strncpy(this->username, username, len);
    this->username[len] = '\0';
  }

  void setNumber(const char *number)
  {
    if (!number)
      throw std::invalid_argument("Cannot pass a nullptr as a number");

    if (strlen(number) > 10)
      throw std::logic_error("The number should be 10 chars at most");

    delete[] this->number;
    size_t len = strlen(number);
    this->number = new char[len + 1];
    strncpy(this->number, number, len);
    this->number[len] = '\0';
  }

  const char *getUsername() const
  {
    return username;
  }

  const char *getNumber() const
  {
    return number;
  }

  // 🔍 Search function
  static User *findByUsername(const char *name)
  {
    for (int i = 0; i < count; ++i)
    {
      if (strcmp(users[i]->getUsername(), name) == 0)
      {
        return users[i];
      }
    }
    return nullptr;
  }

  // 📋 For testing: list all usernames
  static void listAllUsers()
  {
    for (int i = 0; i < count; ++i)
    {
      std::cout << users[i]->getUsername() << std::endl;
    }
  }

private:
  char *username = nullptr;
  char *number = nullptr;

  static User *users[100];
  static int count;

  static void registerInstance(User *user)
  {
    if (count >= 100)
      throw std::runtime_error("Maximum number of users reached");

    users[count++] = user;
  }
};

// Static member initialization
User *User::users[100];
int User::count = 0;

const int MAX_BOOKS = 50;

class Library
{
public:
  Library() : books(nullptr), size(0) {}

  Library(const Library &other) : size(other.size)
  {
    books = new Book[size];
    for (size_t i = 0; i < size; ++i)
    {
      books[i] = other.books[i];
    }
  }

  Library &operator=(const Library &other)
  {
    if (this != &other)
    {
      delete[] books;

      size = other.size;
      books = new Book[size];
      for (size_t i = 0; i < size; ++i)
      {
        books[i] = other.books[i];
      }
    }
    return *this;
  }

  ~Library()
  {
    delete[] books;
  }

  void addBook(const Book *book)
  {
    if (!book)
      throw std::invalid_argument("Cannot pass a nullptr");

    if (size == MAX_BOOKS)
      throw std::logic_error("You have reached the max books");

    Book *tempBooks = new Book[size + 1];

    for (size_t i = 0; i < size; ++i)
    {
      tempBooks[i] = books[i];
    }

    tempBooks[size] = *book;
    delete[] books;
    books = tempBooks;
    ++size;
  }

  void print() const
  {
    for (size_t i = 0; i < size; ++i)
    {
      books[i].print();
    }
  }

  Book *getBooks() const
  {
    return books;
  }

  size_t getSize() const
  {
    return size;
  }

private:
  Book *books;
  size_t size;
};

void rentBook(int bookId, const char *username, Library *library)
{
  if (!User::findByUsername(username))
    throw std::invalid_argument("Cannot pass a nullptr as a username");

  if (!library)
    throw std::logic_error("No books available in this library");

  for (size_t i = 0; i < library->getSize(); i++)
  {
    if (library->getBooks()[i].getId() == bookId)
    {
      library->getBooks()[i].setRenter(User::findByUsername(username));
    }
  }
}

void returnBook(int bookId, Library *library)
{
  if (!library)
    throw std::logic_error("No books available in this library");

  for (size_t i = 0; i < library->getSize(); i++)
  {
    if (library->getBooks()[i].getId() == bookId)
    {
      library->getBooks()[i].setRenter(nullptr);
    }
  }
}

int main()
{

  try
  {
    Book book1("Book 1", "Author 1", true);
    Book book2("Book 2", "Author 2", false);
    Library library;
    library.addBook(&book1);
    library.addBook(&book2);
    library.print();
  }
  catch (const std::exception &e)
  {
    std::cerr << "An error occurred: " << e.what() << std::endl;
  }

  return 0;
}