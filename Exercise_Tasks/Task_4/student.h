#pragma once

#include "address.h"

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

void readStudentData(Student &student);

void printStudentData(const Student &student);

float calcAvgGrade(const Student &student);

bool isAnExcellentStudent(const Student &student);

Student *getStudentsByCriteria(const Student *students, const unsigned n, bool (*predicate)(const Student &), unsigned &studentsMeetingCriteriaCount);

void generateRandomStudentData(Student &student);

Student *getTopStudents(const Student *students, const unsigned n, Majors chosenMajor,
                        const unsigned requiredStudentsCount, const unsigned minPassedExams,
                        unsigned &studentsMeetingCriteriaCount);