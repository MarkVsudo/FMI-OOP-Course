#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

enum DocumentType
{
  TEXT,
  CODE
};

// ========== Абстрактен Клас ==========
class Document
{
protected:
  char *title;
  char *content;
  int day, month, year;

  void copyString(char *&dest, const char *src)
  {
    if (src)
    {
      dest = new char[strlen(src) + 1];
      strcpy(dest, src);
    }
    else
    {
      dest = nullptr;
    }
  }

public:
  Document(const char *title = "", const char *content = "")
  {
    copyString(this->title, title);
    copyString(this->content, content);

    time_t now = time(0);
    tm *ltm = localtime(&now);
    day = ltm->tm_mday;
    month = 1 + ltm->tm_mon;
    year = 1900 + ltm->tm_year;
  }

  virtual ~Document()
  {
    delete[] title;
    delete[] content;
  }

  virtual void display() const = 0;
  virtual void saveToFile(const char *filename) const = 0;
  virtual void saveBinary(ofstream &out) const = 0;
  virtual DocumentType getType() const = 0;

  virtual Document *clone() const = 0;

  friend ostream &operator<<(ostream &os, const Document &doc)
  {
    doc.display();
    return os;
  }
};

// ========== Текстов Документ ==========
class TextDocument : public Document
{
public:
  TextDocument(const char *title = "", const char *content = "")
      : Document(title, content) {}

  void display() const override
  {
    cout << "[Text Document]\n";
    cout << "Title: " << title << "\nContent: " << content << "\nDate: "
         << day << "/" << month << "/" << year << "\n";
  }

  void saveToFile(const char *filename) const override
  {
    ofstream out(filename);
    if (!out)
      throw runtime_error("Cannot open file.");
    out << "TEXT\n"
        << title << "\n"
        << content << "\n"
        << day << " " << month << " " << year << "\n";
    out.close();
  }

  void saveBinary(ofstream &out) const override
  {
    DocumentType type = TEXT;
    out.write((char *)&type, sizeof(type));
    int len = strlen(title);
    out.write((char *)&len, sizeof(len));
    out.write(title, len);
    len = strlen(content);
    out.write((char *)&len, sizeof(len));
    out.write(content, len);
    out.write((char *)&day, sizeof(day));
    out.write((char *)&month, sizeof(month));
    out.write((char *)&year, sizeof(year));
  }

  static TextDocument *loadBinary(ifstream &in)
  {
    int len;
    char *buffer;

    in.read((char *)&len, sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    char *title = buffer;

    in.read((char *)&len, sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    char *content = buffer;

    int d, m, y;
    in.read((char *)&d, sizeof(d));
    in.read((char *)&m, sizeof(m));
    in.read((char *)&y, sizeof(y));

    TextDocument *doc = new TextDocument(title, content);
    doc->day = d;
    doc->month = m;
    doc->year = y;
    delete[] title;
    delete[] content;
    return doc;
  }

  DocumentType getType() const override
  {
    return TEXT;
  }

  Document *clone() const override
  {
    return new TextDocument(*this);
  }
};

// ========== Код Документ ==========
class CodeDocument : public Document
{
  char *language;

public:
  CodeDocument(const char *title = "", const char *content = "", const char *lang = "")
      : Document(title, content)
  {
    copyString(language, lang);
  }

  ~CodeDocument() override
  {
    delete[] language;
  }

  void display() const override
  {
    cout << "[Code Document]\n";
    cout << "Title: " << title << "\nLanguage: " << language
         << "\nContent: " << content << "\nDate: "
         << day << "/" << month << "/" << year << "\n";
  }

  void saveToFile(const char *filename) const override
  {
    ofstream out(filename);
    if (!out)
      throw runtime_error("Cannot open file.");
    out << "CODE\n"
        << title << "\n"
        << content << "\n"
        << language << "\n"
        << day << " " << month << " " << year << "\n";
    out.close();
  }

  void saveBinary(ofstream &out) const override
  {
    DocumentType type = CODE;
    out.write((char *)&type, sizeof(type));
    int len = strlen(title);
    out.write((char *)&len, sizeof(len));
    out.write(title, len);
    len = strlen(content);
    out.write((char *)&len, sizeof(len));
    out.write(content, len);
    len = strlen(language);
    out.write((char *)&len, sizeof(len));
    out.write(language, len);
    out.write((char *)&day, sizeof(day));
    out.write((char *)&month, sizeof(month));
    out.write((char *)&year, sizeof(year));
  }

  static CodeDocument *loadBinary(ifstream &in)
  {
    int len;
    char *buffer;

    in.read((char *)&len, sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    char *title = buffer;

    in.read((char *)&len, sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    char *content = buffer;

    in.read((char *)&len, sizeof(len));
    buffer = new char[len + 1];
    in.read(buffer, len);
    buffer[len] = '\0';
    char *language = buffer;

    int d, m, y;
    in.read((char *)&d, sizeof(d));
    in.read((char *)&m, sizeof(m));
    in.read((char *)&y, sizeof(y));

    CodeDocument *doc = new CodeDocument(title, content, language);
    doc->day = d;
    doc->month = m;
    doc->year = y;
    delete[] title;
    delete[] content;
    delete[] language;
    return doc;
  }

  DocumentType getType() const override
  {
    return CODE;
  }

  Document *clone() const override
  {
    return new CodeDocument(*this);
  }
};

// ========== Шаблонен Клас ==========
template <typename T>
class DocumentBox
{
  T **documents;
  int capacity;
  int count;

public:
  DocumentBox(int cap) : capacity(cap), count(0)
  {
    documents = new T *[capacity];
  }

  ~DocumentBox()
  {
    for (int i = 0; i < count; ++i)
    {
      delete documents[i];
    }
    delete[] documents;
  }

  void add(T *doc)
  {
    if (count >= capacity)
    {
      cout << "Box is full!\n";
      return;
    }
    documents[count++] = doc;
  }

  void listAll() const
  {
    if (count == 0)
    {
      cout << "No documents to display.\n";
      return;
    }
    for (int i = 0; i < count; ++i)
    {
      cout << *documents[i] << "\n";
    }
  }

  void saveAllBinary(const char *filename) const
  {
    ofstream out(filename, ios::binary);
    if (!out)
    {
      cerr << "Error opening binary file.\n";
      return;
    }
    out.write((char *)&count, sizeof(count));
    for (int i = 0; i < count; ++i)
    {
      documents[i]->saveBinary(out);
    }
    out.close();
  }

  void loadAllBinary(const char *filename)
  {
    ifstream in(filename, ios::binary);
    if (!in)
    {
      cerr << "Error opening binary file for reading.\n";
      return;
    }
    int num;
    in.read((char *)&num, sizeof(num));
    for (int i = 0; i < num; ++i)
    {
      DocumentType type;
      in.read((char *)&type, sizeof(type));
      Document *doc = nullptr;
      if (type == TEXT)
        doc = TextDocument::loadBinary(in);
      else if (type == CODE)
        doc = CodeDocument::loadBinary(in);
      if (doc)
        add(doc);
    }
    in.close();
  }
};

// ========== Main Function ==========
int main()
{
  DocumentBox<Document> box(20);
  int choice;

  while (true)
  {
    cout << "\n===== Document System Menu =====\n";
    cout << "1. Add Text Document\n";
    cout << "2. Add Code Document\n";
    cout << "3. List All Documents\n";
    cout << "4. Save All (Binary)\n";
    cout << "5. Load All (Binary)\n";
    cout << "0. Exit\n";
    cout << "Your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 0)
      break;

    char title[256], content[1024], language[64];

    switch (choice)
    {
    case 1:
      cout << "Enter title: ";
      cin.getline(title, 256);
      cout << "Enter content: ";
      cin.getline(content, 1024);
      box.add(new TextDocument(title, content));
      break;
    case 2:
      cout << "Enter title: ";
      cin.getline(title, 256);
      cout << "Enter content: ";
      cin.getline(content, 1024);
      cout << "Enter programming language: ";
      cin.getline(language, 64);
      box.add(new CodeDocument(title, content, language));
      break;
    case 3:
      box.listAll();
      break;
    case 4:
      box.saveAllBinary("documents.bin");
      cout << "Documents saved to binary file.\n";
      break;
    case 5:
      box.loadAllBinary("documents.bin");
      cout << "Documents loaded from binary file.\n";
      break;
    default:
      cout << "Invalid option.\n";
    }
  }

  return 0;
}
