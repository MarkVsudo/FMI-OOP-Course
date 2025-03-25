// 1. Създайте структура Student, която описва студент, и се състои от име (с произволна дължина), факултетен номер (10 символа) и факултет (избор между FMI, History, Geography). Реализирайте следната функционалност:

// записване на студент в двоичен файл
// четене на студент от двоичен файл
// Създайте структура Course, който има име (с произволна дължина) и се състои от студенти (произволен брой). Реализирайте следната функционалност:

// записване на курс в двоичен файл
// четене на курс от двоичен файл

#include <iostream>
#include <cstring>
#include <fstream>

enum faculty
{
  FMI = 1,
  History,
  Geography
};

const char *facultyStrs[3] = {"FMI", "History", "Geography"};

struct Student
{
  char name[128];
  char FN[11];
  faculty faculty;
};

void addStudent(const char *fileName)
{
  std::ofstream outFile(fileName, std::ios::binary | std::ios::app);

  if (!outFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return;
  }

  Student student;

  std::cout << "Enter student name: ";
  std::cin.getline(student.name, 128);

  do
  {
    std::cout << "Enter student FN (10 chars): ";
    std::cin.getline(student.FN, 11);
  } while (strlen(student.FN) != 10);

  int choice;
  do
  {
    std::cout << "--Select a faculty--\n1) FMI\n2) History\n3) Geography\n";
    std::cin >> choice;
  } while (choice < 1 || choice > 3);

  student.faculty = (faculty)(choice);

  outFile.write((char *)(&student), sizeof(student));

  outFile.close();
}

void getStudents(const char *fileName)
{
  std::ifstream inFile(fileName, std::ios::binary | std::ios::ate);

  if (!inFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return;
  }

  size_t studentCount = inFile.tellg() / sizeof(Student);

  if (studentCount == 0)
  {
    std::cout << "No students found!" << std::endl;
    inFile.close();
    return;
  }

  Student *students = new Student[studentCount];
  inFile.seekg(0, std::ios::beg);
  inFile.read((char *)(students), studentCount * sizeof(Student));

  inFile.close();

  for (size_t i = 0; i < studentCount; i++)
  {
    std::cout << "--Student " << i + 1 << "--\n";
    std::cout << "Name: " << students[i].name << std::endl;
    std::cout << "FN: " << students[i].FN << std::endl;
    std::cout << "Faculty: " << facultyStrs[students[i].faculty - 1] << std::endl;
  }

  delete[] students;
}

int main()
{
  const char *studentsFileName = "students.dat";

  addStudent(studentsFileName);
  getStudents(studentsFileName);

  // ... add courses functionality

  return 0;
}
