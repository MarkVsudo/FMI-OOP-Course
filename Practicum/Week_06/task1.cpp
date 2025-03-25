// 1. Напишете клас Teacher, която описва преподавател. Класът трябва да съдържа:

// Име (максимум 25 символа)
// Възраст (число от 18 до 70)
// Предмет (enum с учебни предмети)
// Заплата (положително число над 500 лева)
// Създайте подходящи конструктори, get и set член-функции.

#include <iostream>
#include <cstring>

enum Subjects
{
  MATHS,
  SCIENCE,
  INFORMATICS,
  GEOGRAPHY,
  BIOLOGY,
  CHEMISTRY,
  COUNTER
};

const char *SUBJECTS_STRS[] = {"Maths", "Science", "Informatics", "Geography", "Biology", "Chemistry"};

class Teacher
{
public:
  Teacher() : name("Unknown"), age(18), subject(MATHS), salary(500) {}

  Teacher(const char *teacherName, short teacherAge, Subjects teacherSubject, unsigned teacherSalary)
  {
    setName(teacherName);
    setAge(teacherAge);
    setSubject(teacherSubject);
    setSalary(teacherSalary);
  }

  void setName(const char *newName)
  {
    if (newName == nullptr)
      return;

    strncpy(name, newName, 25);
    name[25] = '\0';
  }

  void setAge(short newAge)
  {
    if (newAge < 18 || newAge > 70)
      return;

    age = newAge;
  }

  void setSubject(Subjects newSubject)
  {
    if (newSubject < 0 || newSubject >= Subjects::COUNTER)
      return;

    subject = newSubject;
  }

  void setSalary(unsigned newSalary)
  {
    if (newSalary < 500)
      return;

    salary = newSalary;
  }

  const char *getName() const
  {
    return name;
  }

  short getAge() const
  {
    return age;
  }

  Subjects getSubject() const
  {
    return subject;
  }

  unsigned getSalary() const
  {
    return salary;
  }

private:
  char name[26];
  short age;
  Subjects subject;
  unsigned salary;
};

void printTeacher(const Teacher &teacher)
{
  std::cout << "Name: " << teacher.getName() << "\nAge: " << teacher.getAge() << "\nSubject: " << SUBJECTS_STRS[teacher.getSubject()] << "\nSalary: " << teacher.getSalary() << std::endl;
}

int main()
{

  Teacher teacher1;
  printTeacher(teacher1);
  Teacher teacher2("Ivanka Ivankova", 53, CHEMISTRY, 2200);
  printTeacher(teacher2);

  return 0;
}