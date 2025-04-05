#include "student.h"
#include <iostream>
#include "address.h"
#include "utils.h"
#include "global_constants.h"

const unsigned FN_LENGTH = 10;
const unsigned MAX_EMAIL_LEN = 32;
const char *FIRST_NAMES[10]{
    "Ivan", "Maria", "Georgi", "Elena", "Dimitar", "Ivana", "Nikolay", "Viktoria", "Petar", "Yana"};
const char *MIDDLE_NAMES[10]{
    "Ivanov", "Georgiev", "Dimitrov", "Nikolov", "Petrov", "Stefanov", "Stanislavov", "Hristov", "Martinov", "Kaloyanov"};
const char *LAST_NAMES[10]{
    "Petrov", "Ivanov", "Georgiev", "Dimitrov", "Nikolov", "Stefanov", "Stanislavov", "Hristov", "Martin", "Kaloyanov"};

void readStudentData(Student &student)
{
  std::cout << "-- Enter student data --" << std::endl;

  std::cin.ignore();
  std::cout << "First name: ";
  std::cin.getline(student.firstName, 32);

  std::cout << "Middle name: ";
  std::cin.getline(student.middleName, 32);

  std::cout << "Last name: ";
  std::cin.getline(student.lastName, 32);

  readAddressData(student.address);

  int majorOption;
  do
  {
    std::cout << "-- Major --\n1 -> Informatics\n2 -> Information Systems\n3 -> Computer Science\n4 -> Software Engineering\n";
    std::cin >> majorOption;
  } while (majorOption < 1 || majorOption > 4);
  student.major = (Majors)majorOption;

  std::cin.ignore();
  do
  {
    std::cout << "Faculty number: ";
    std::cin.getline(student.FN, 11);
  } while (getStrLength(student.FN) != 10);

  std::cout << "E-mail: ";
  std::cin.getline(student.email, 32);

  do
  {
    std::cout << "Course: ";
    std::cin >> student.course;
  } while (student.course < 1);

  do
  {
    std::cout << "Stream: ";
    std::cin >> student.stream;
  } while (student.stream < 1);

  do
  {
    std::cout << "Group: ";
    std::cin >> student.group;
  } while (student.group < 1);

  do
  {
    std::cout << "Number of passed exams: ";
    std::cin >> student.passedExamsCount;
  } while (student.passedExamsCount < 0);

  student.grades = new float[student.passedExamsCount];

  for (unsigned i = 0; i < student.passedExamsCount; i++)
  {
    do
    {
      std::cout << "Grade of exam " << i + 1 << " (between 2 and 6): ";
      std::cin >> student.grades[i];
    } while (student.grades[i] < 2 || student.grades[i] > 6);
  }
}

void printStudentData(const Student &student)
{
  std::cout << "-- Student data --" << std::endl;
  std::cout << "First name: " << student.firstName << std::endl;
  std::cout << "Middle name: " << student.middleName << std::endl;
  std::cout << "Last name: " << student.lastName << std::endl;
  printAddressData(student.address);
  std::cout << "Major: " << MAJORS[student.major - 1] << std::endl;
  std::cout << "Faculty number: " << student.FN << std::endl;
  std::cout << "E-mail: " << student.email << std::endl;
  std::cout << "Course: " << student.course << std::endl;
  std::cout << "Stream: " << student.stream << std::endl;
  std::cout << "Group: " << student.group << std::endl;
  std::cout << "Number of passed exams: " << student.passedExamsCount << std::endl;

  std::cout << "Grades: [";
  for (unsigned i = 0; i < student.passedExamsCount; i++)
  {
    std::cout << student.grades[i] << (i < student.passedExamsCount - 1 ? ", " : "");
  }
  std::cout << "]" << std::endl;
}

float calcAvgGrade(const Student &student)
{
  float avgGrade = 0;

  if (student.passedExamsCount == 0)
  {
    std::cout << "Student has not passed any exams yet..." << std::endl;
    return 0;
  }

  for (unsigned i = 0; i < student.passedExamsCount; i++)
  {
    avgGrade += student.grades[i];
  }

  avgGrade /= student.passedExamsCount;

  return avgGrade;
}

bool isAnExcellentStudent(const Student &student)
{
  return (calcAvgGrade(student) - 5.50) >= -0.00001;
}

Student *getStudentsByCriteria(const Student *students, const unsigned n, bool (*predicate)(const Student &), unsigned &studentsMeetingCriteriaCount)
{
  studentsMeetingCriteriaCount = 0;
  for (unsigned i = 0; i < n; i++)
  {
    if (predicate(students[i]))
      studentsMeetingCriteriaCount++;
  }

  if (studentsMeetingCriteriaCount == 0)
  {
    return nullptr;
  }

  Student *studentsMeetingCriteria = new Student[studentsMeetingCriteriaCount];

  for (unsigned i = 0, j = 0; i < n; i++)
  {
    if (predicate(students[i]))
      studentsMeetingCriteria[j++] = students[i];
  }

  return studentsMeetingCriteria;
}

void generateRandomStudentData(Student &student)
{
  // First, middle, last name
  unsigned fstNameIndex = randNum(0, 9);
  unsigned fstNameLen = getStrLength(FIRST_NAMES[fstNameIndex]);
  for (unsigned i = 0; i < fstNameLen; i++)
  {
    student.firstName[i] = FIRST_NAMES[fstNameIndex][i];
  }
  student.firstName[fstNameLen] = '\0';

  unsigned middleNameIndex = randNum(0, 9);
  unsigned middleNameLen = getStrLength(MIDDLE_NAMES[middleNameIndex]);
  for (unsigned i = 0; i < middleNameLen; i++)
  {
    student.middleName[i] = MIDDLE_NAMES[middleNameIndex][i];
  }
  student.middleName[middleNameLen] = '\0';

  unsigned lastNameIndex = randNum(0, 9);
  unsigned lastNameLen = getStrLength(LAST_NAMES[lastNameIndex]);
  for (unsigned i = 0; i < lastNameLen; i++)
  {
    student.lastName[i] = LAST_NAMES[lastNameIndex][i];
  }
  student.lastName[lastNameLen] = '\0';

  // FN
  // Don't really know the formula for creating FNs, doing it based on my FN

  student.FN[0] = '0' + randNum(0, 9);
  student.FN[1] = 'M';
  student.FN[2] = 'I';
  student.FN[3] = '0';
  student.FN[4] = '7';
  student.FN[5] = '0';
  student.FN[6] = '0';

  for (unsigned i = 7; i < FN_LENGTH; i++)
  {
    student.FN[i] = '0' + randNum(0, 9);
  }
  student.FN[FN_LENGTH] = '\0';

  // email
  // First email option
  // 9mi0700339@g.fmi.uni-sofia.bg
  const char *EMAIL_TEMPLATE_1 = "@g.fmi.uni-sofia.bg";

  for (unsigned i = 0; i < FN_LENGTH; i++)
  {
    student.email[i] = student.FN[i];
  }

  for (unsigned i = 0; EMAIL_TEMPLATE_1[i] != '\0'; i++)
  {
    student.email[FN_LENGTH + i] = EMAIL_TEMPLATE_1[i];
  }

  student.email[FN_LENGTH + getStrLength(EMAIL_TEMPLATE_1)] = '\0';

  // Second email option
  // mveskov@uni-sofia.bg
  // no need for lower case convertion of email characters since email@example.com == EMAIL@example.com

  // const char *EMAIL_TEMPLATE_2 = "@uni-sofia.bg";

  // student.email[0] = student.firstName[0];

  // for (unsigned i = 0; i < lastNameLen; i++)
  // {
  //   student.email[i + 1] = student.lastName[i];
  // }

  // for (unsigned i = 0; EMAIL_TEMPLATE_2[i] != '\0'; i++)
  // {
  //   student.email[lastNameLen + 1 + i] = EMAIL_TEMPLATE_2[i];
  // }

  // student.email[lastNameLen + 1 + getStrLength(EMAIL_TEMPLATE_2)] = '\0';

  // Major, course, stream, and group
  student.major = (Majors)randNum(1, 4);
  student.course = randNum(1, 4);
  // Not sure which majors have multiple streams
  student.stream = (student.major == Majors::COMPUTER_SCIENCE) ? randNum(1, 2) : 1;
  student.group = randNum(1, 4);

  // Generate grades
  student.passedExamsCount = randNum(0, 5);
  student.grades = new float[student.passedExamsCount];
  for (unsigned i = 0; i < student.passedExamsCount; i++)
  {
    student.grades[i] = (float)randNum(3, 6);
  }

  // Address (will improve this after we start working with text files)
  const char *CITIES[2] = {"Sofia", "Plovdiv"};
  const int SOFIA_POSTAL_CODES[2] = {1301, 1172};
  const char *POSTAL_CODE_1301_STREETS[2] = {"Pirotska Street", "Graf Ignatiev Street"};
  const char *POSTAL_CODE_1172_STREETS[2] = {"Nikola Gabrovski Street", "Buenos Aires Street"};

  const int PLOVDIV_POSTAL_CODES[2] = {4000, 4023};
  const char *POSTAL_CODE_4000_STREETS[2] = {"Maritsa Boulevard", "Knyaz Alexander I Street"};
  const char *POSTAL_CODE_4023_STREETS[2] = {"Vasil Levski Street", "Brezovsko Shose"};

  unsigned cityIndex = randNum(0, 1);
  unsigned cityLen = getStrLength(CITIES[cityIndex]);
  for (unsigned i = 0; i < cityLen; i++)
  {
    student.address.city[i] = CITIES[cityIndex][i];
  }
  student.address.city[cityLen] = '\0';

  const char *streetName;
  if (cityIndex == 0)
  {
    student.address.postalCode = SOFIA_POSTAL_CODES[randNum(0, 1)];
    switch (student.address.postalCode)
    {
    case 1301:
      streetName = POSTAL_CODE_1301_STREETS[randNum(0, 1)];
      break;
    case 1172:
      streetName = POSTAL_CODE_1172_STREETS[randNum(0, 1)];
      break;
    default:
      streetName = "Unknown Street";
      break;
    }
  }
  else
  {
    student.address.postalCode = PLOVDIV_POSTAL_CODES[randNum(0, 1)];
    switch (student.address.postalCode)
    {
    case 4000:
      streetName = POSTAL_CODE_4000_STREETS[randNum(0, 1)];
      break;
    case 4023:
      streetName = POSTAL_CODE_4023_STREETS[randNum(0, 1)];
      break;
    default:
      streetName = "Unknown Street";
      break;
    }
  }

  unsigned streetLen = getStrLength(streetName);
  for (unsigned i = 0; i < streetLen; i++)
  {
    student.address.street[i] = streetName[i];
  }
  student.address.street[streetLen] = '\0';

  student.address.number = randNum(1, 99);
  student.address.entrance = randNum(1, 4);
  student.address.floor = randNum(0, 8);
  student.address.apartment = randNum(1, 32);
  student.address.letter = 'a' + randNum(0, 4);
}

Student *getTopStudents(const Student *students, const unsigned n, Majors chosenMajor,
                        const unsigned requiredStudentsCount, const unsigned minPassedExams,
                        unsigned &studentsMeetingCriteriaCount)
{
  studentsMeetingCriteriaCount = 0;
  for (unsigned i = 0; i < n; i++)
  {
    if (students[i].major == chosenMajor && students[i].passedExamsCount >= minPassedExams)
    {
      studentsMeetingCriteriaCount++;
    }
  }

  if (studentsMeetingCriteriaCount == 0)
  {
    return nullptr;
  }

  // this shallow copy allows us to "filter -> sort -> pick" instead of "filter -> pick -> sort" without using a copy which could let us miss out on the best students if they are at the end of the array
  Student *filteredStudents = new Student[studentsMeetingCriteriaCount];
  unsigned index = 0;
  for (unsigned i = 0; i < n; i++)
  {
    if (students[i].major == chosenMajor && students[i].passedExamsCount >= minPassedExams)
    {
      filteredStudents[index++] = students[i];
    }
  }

  // Bubble
  for (unsigned i = 0; i < studentsMeetingCriteriaCount - 1; i++)
  {
    for (unsigned j = 0; j < studentsMeetingCriteriaCount - i - 1; j++)
    {
      if (calcAvgGrade(filteredStudents[j]) < calcAvgGrade(filteredStudents[j + 1]))
      {
        Student temp = filteredStudents[j];
        filteredStudents[j] = filteredStudents[j + 1];
        filteredStudents[j + 1] = temp;
      }
    }
  }

  if (studentsMeetingCriteriaCount > requiredStudentsCount)
  {
    studentsMeetingCriteriaCount = requiredStudentsCount;
  }

  Student *topStudents = new Student[studentsMeetingCriteriaCount];
  for (unsigned i = 0; i < studentsMeetingCriteriaCount; i++)
  {
    topStudents[i] = filteredStudents[i];
  }

  delete[] filteredStudents;
  return topStudents;
}
