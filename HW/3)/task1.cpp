#include <iostream>

const char *DAYS_STRINGS[] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

class Date
{
public:
  Date() : year(0), month(1), day(1) {}

  Date(int year, int month, int day)
  {
    setYear(year);
    setMonth(month);
    setDay(day);
  }

  void printDate() const
  {
    std::cout << day << "/" << month << "/" << year << std::endl;
  }

  void changeDate()
  {
    int choice;
    do
    {
      std::cout << "Which part of the date would you like to change?\n1) Year\n2) Month\n3) Day\n4) All of the above\n";
      std::cin >> choice;
    } while (choice < 1 || choice > 4);

    switch (choice)
    {
    case 1:
    {
      int year;
      std::cout << "Enter a year: ";
      std::cin >> year;
      setYear(year);
    }
    break;
    case 2:
    {
      int month;
      std::cout << "Enter a month: ";
      std::cin >> month;
      setMonth(month);
    }
    break;
    case 3:
    {
      int day;
      std::cout << "Enter a day: ";
      std::cin >> day;
      setDay(day);
    }
    break;
    case 4:
    {
      std::cout << "Enter a year: ";
      int year;
      std::cin >> year;
      setYear(year);
      std::cout << "Enter a month: ";
      int month;
      std::cin >> month;
      setMonth(month);
      std::cout << "Enter a day: ";
      int day;
      std::cin >> day;
      setDay(day);
    }
    break;
    default:
      std::cout << "Invalid input!";
    }
  }

  int getDayOfWeek() const
  {
    int K = year % 100;
    int J = year / 100;

    int dayIndex = (day + 13 * (month + 1) / 5 + K + J / 4 + 5 * J) % 7;

    return dayIndex;
  }

  // TO-DO
  // - намирате разликата (в брой дни) между две дати (може да е положителна или отрицателна);
  // - сравнявате две дати - реализирайте тризначно сравнение (подобно на strcmp);
  // - прибавяте брой дни към дата (може да е отрицателен).

  void setYear(int year)
  {
    this->year = year;
  }

  void setMonth(int month)
  {
    if (month < 1 || month > 12)
    {
      std::cerr << "Invalid month!" << std::endl;
      return;
    }
    this->month = month;
  }

  void setDay(int day)
  {
    if (!isValidDay(day, month, year))
    {
      std::cerr << "Invalid day for the given month/year!" << std::endl;
      return;
    }
    this->day = day;
  }

  int getYear() const
  {
    return year;
  }

  int getMonth() const
  {
    return month;
  }

  int getDay() const
  {
    return day;
  }

private:
  int year;
  int month;
  int day;

  bool isValidDay(int day, int month, int year) const
  {
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];

    // Leap year
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
      maxDay = 29;

    return day >= 1 && day <= maxDay;
  }
};

void inputDateData(Date &date)
{
  std::cout << "Enter a year: ";
  int year;
  std::cin >> year;
  date.setYear(year);

  std::cout << "Enter a month: ";
  int month;
  std::cin >> month;
  date.setMonth(month);

  std::cout << "Enter a day: ";
  int day;
  std::cin >> day;
  date.setDay(day);
}

int main()
{
  Date date;
  inputDateData(date);
  date.printDate();

  date.changeDate();
  date.printDate();

  std::cout << "This date is on " << DAYS_STRINGS[date.getDayOfWeek()] << std::endl;

  return 0;
}