// Задача 4.
// Да се реализира структура, която представя адрес. Той се състои от град (символен низ с не повече от 32 символа); пощенски код (цяло число без знак); улица (символен низ с не повече от 64 символа); номер (цяло число без знак); една буква (към номера); вход, етаж, апартамент (малки цели числа без знак). Примерен адрес би бил: "София", 1234, "ул. Цар Симеон", 10 а, вх. 2, ет. 7, ап. 30.
// Да се напишат методи, позволяващи въвеждане и извеждане на адрес от стандартния вход / изход.

// Да се реализира структура, която представлява студент. Той се състои от:
// Име, презиме, фамилия - всеки от тях символен низ с не повече от 32 символа; Адрес - от горния тип; Специалност - едно от предварително зададени опции (изброен тип); Факултетен номер - символен низ с 10 символа; e-mail - символен низ с не по-вече от 32 символа; курс, поток, група, брой успешно положени изпити, оценки от тези изпити - за тях подберете подходящи типове.
// За студентите реализирайте функционалности за:
// - прочитане на данни за студент то стандартния вход
// - извеждане на данни за студент на стандартния вход
// - генериране на случайни, но валидни данни за студент
// - пресмятане на средния успех от положените изпити
// Напишете функции, работещи с масив от записи за студенти, които:
// - намира и връща като резултат всички студенти, които имат успех по-голям от даден праг (например отличници).
// - намира определен брой студенти за дадена специалност с максимален успех, които имат поне даден брой успешно положени изпит.
// - Извежда информация за студентите, намерени сред всички по едно или няколко от полетата: име, презиме, фамилия, факултетен номер. Позволете подаването на критерия да бъде като масив от низове и подходящи други параметри, определящи какви полета точно ще бъдат използвани при търсенето.

#include <iostream>
#include "address.h"
#include "student.h"
#include "global_constants.h"

int main()
{
  unsigned n;
  do
  {
    std::cout << "Enter amount of students: ";
    std::cin >> n;
  } while (n < 0);

  Student *students = new Student[n];

  // Read student data
  for (unsigned i = 0; i < n; i++)
  {
    std::cout << "-- Student " << i + 1 << " --" << std::endl;
    readStudentData(students[i]);
  }

  std::cout << "----------------" << std::endl;

  // Print student data
  for (unsigned i = 0; i < n; i++)
  {
    std::cout << "-- Student " << i + 1 << " --" << std::endl;
    printStudentData(students[i]);
  }

  std::cout << "----------------" << std::endl;

  // Print average grades
  for (unsigned i = 0; i < n; i++)
  {
    std::cout << "Student " << i + 1 << " average grade: " << calcAvgGrade(students[i]) << std::endl;
  }

  std::cout << "----------------" << std::endl;

  // Get excellent students
  unsigned excellentStudentsCount = 0; // Using this method because I don't know how to return two arguments from a function in cpp
  Student *excellentStudents = getStudentsByCriteria(students, n, isAnExcellentStudent, excellentStudentsCount);
  if (excellentStudents)
  {
    std::cout << "-- Excellent students --" << std::endl;
    for (unsigned i = 0; i < excellentStudentsCount; i++)
    {
      printStudentData(excellentStudents[i]);
    }

    delete[] excellentStudents;
  }
  else
  {
    std::cout << "No excellent students found :((" << std::endl;
  }

  std::cout << "----------------" << std::endl;

  // Get top students from a specified major
  unsigned topStudentsCount = 0;
  unsigned requiredStudentsCount;
  do
  {
    std::cout << "Enter the amount of top students to extract: ";
    std::cin >> requiredStudentsCount;
  } while (requiredStudentsCount < 0);

  int majorOption;
  do
  {
    std::cout << "Enter the major for these students: " << std::endl;
    std::cout << "-- Major --\n1 -> Informatics\n2 -> Information Systems\n3 -> Computer Science\n4 -> Software Engineering\n";
    std::cin >> majorOption;
  } while (majorOption < 1 || majorOption > 4);

  unsigned minPassedExams;
  do
  {
    std::cout << "Enter the amount of minimum exams the student has to have passed: ";
    std::cin >> minPassedExams;
  } while (minPassedExams < 0);

  Student *topStudents = getTopStudents(students, n, (Majors)majorOption, requiredStudentsCount, minPassedExams, topStudentsCount);
  if (topStudents)
  {
    std::cout << "-- Top students from " << MAJORS[majorOption - 1] << " with minimum of " << minPassedExams << " exams passed --" << std::endl;
    for (unsigned i = 0; i < topStudentsCount; i++)
    {
      printStudentData(topStudents[i]);
    }

    delete[] topStudents;
  }
  else
  {
    std::cout << "No top students found with the specified criteria :((" << std::endl;
  }

  std::cout << "----------------" << std::endl;

  // Randomly generated data for student
  std::cout << "----------- Random student ------------" << std::endl;
  Student randomStudent;
  generateRandomStudentData(randomStudent);
  printStudentData(randomStudent);

  delete[] randomStudent.grades;

  // Free memory
  for (unsigned i = 0; i < n; i++)
  {
    delete[] students[i].grades;
  }
  delete[] students;

  return 0;
}