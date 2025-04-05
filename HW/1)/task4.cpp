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
#include <cstdlib>

struct Address
{
  char street[64];          // 64 B
  char city[32];            // 32 B
  unsigned postalCode;      // 4 B
  unsigned number;          // 4 B
  unsigned short entrance;  // 2 B
  unsigned short floor;     // 2 B
  unsigned short apartment; // 2 B
  char letter;              // 1 B
};

enum Majors
{
  INFORMATICS1 = 1,
  INFORMATION_SYSTEMS,
  COMPUTER_SCIENCE,
  SOFTWARE_ENGINEERING
};

struct Student
{
  Address address;                 // 112 B
  float *grades;                   // 4-8 B
  char firstName[32];              // 32 B
  char middleName[32];             // 32 B
  char lastName[32];               // 32 B
  char email[32];                  // 32 B
  char FN[11];                     // 11 B
  Majors major;                    // 4 B
  unsigned short course;           // 2 B
  unsigned short stream;           // 2 B
  unsigned short group;            // 2 B
  unsigned short passedExamsCount; // 2 B
};

const unsigned FN_LENGTH = 10;
const unsigned MAX_EMAIL_LEN = 32;
const char *FIRST_NAMES[10]{
    "Ivan", "Maria", "Georgi", "Elena", "Dimitar", "Ivana", "Nikolay", "Viktoria", "Petar", "Yana"};
const char *MIDDLE_NAMES[10]{
    "Ivanov", "Georgiev", "Dimitrov", "Nikolov", "Petrov", "Stefanov", "Stanislavov", "Hristov", "Martinov", "Kaloyanov"};
const char *LAST_NAMES[10]{
    "Petrov", "Ivanov", "Georgiev", "Dimitrov", "Nikolov", "Stefanov", "Stanislavov", "Hristov", "Martin", "Kaloyanov"};
const char *MAJORS[4] = {"Informatics", "Information Systems", "Computer Science", "Software Engineering"};

void readAddressData(Address &address)
{
  std::cout << "-- Enter address data --" << std::endl;

  std::cout << "City: ";
  std::cin.getline(address.city, 32);

  do
  {
    std::cout << "Postal code: ";
    std::cin >> address.postalCode;
  } while (address.postalCode < 0);

  std::cin.ignore();
  std::cout << "Street: ";
  std::cin.getline(address.street, 64);

  do
  {
    std::cout << "Number: ";
    std::cin >> address.number;
  } while (address.number < 0);

  std::cout << "Letter: ";
  std::cin >> address.letter;

  do
  {
    std::cout << "Entrance: ";
    std::cin >> address.entrance;
  } while (address.entrance < 1);

  do
  {
    std::cout << "Floor: ";
    std::cin >> address.floor;
  } while (address.floor < 0);

  do
  {
    std::cout << "Apartment: ";
    std::cin >> address.apartment;
  } while (address.apartment < 1);
}

void printAddressData(const Address &address)
{
  std::cout << "Address: \"" << address.city << "\", " << address.postalCode << ", \"" << address.street << "\", " << address.number << " " << address.letter << ", ent. " << address.entrance << ", floor " << address.floor << ", ap. " << address.apartment << std::endl;
}

unsigned getStrLength(const char *str)
{
  unsigned count = 0;

  while (str[count] != '\0')
  {
    count++;
  }

  return count;
}

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

unsigned randNum(unsigned min, unsigned max)
{
  return min + (rand() % (max - min + 1));
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

  // Address
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