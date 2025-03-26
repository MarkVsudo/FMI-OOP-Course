#include <iostream>

class Interval
{
public:
  Interval() : a(0), b(0) {}

  Interval(int a, int b)
  {
    if (a > b)
    {
      setA(0);
      setB(0);
    }
    else
    {
      setA(a);
      setB(b);
    }
  }

  void setA(int a) { this->a = a; }
  void setB(int b) { this->b = b; }

  int getA() const { return a; }
  int getB() const { return b; }

  int intervalLength() const { return b - a; }

  bool isInInterval(int x) const { return x >= a && x <= b; }

  int primeNumbersCount() const
  {
    int count = 0;
    for (int i = a; i <= b; i++)
    {
      if (isPrime(i))
        count++;
    }
    return count;
  }

  int palindromesCount() const
  {
    int count = 0;
    for (int i = a; i <= b; i++)
    {
      if (isPalindrome(i))
        count++;
    }
    return count;
  }

  int nonRepeatingDigitsNumbersCount() const
  {
    int count = 0;
    for (int i = a; i <= b; i++)
    {
      if (!hasRepeatingDigits(i))
        count++;
    }
    return count;
  }

  bool arePowersOfTwo() const
  {
    bool flag1 = false, flag2 = false;

    if (a % 2 != 0 || b % 2 != 0)
    {
      return false;
    }

    int num = 2;

    while (num <= a)
    {
      if (num == a)
        flag1 = true;

      num *= 2;
    }

    num = 2;

    while (num <= b)
    {
      if (num == b)
        flag2 = true;

      num *= 2;
    }

    return flag1 && flag2;
  }

  void findIntersection(int x, int y) const
  {
    if (b < x || a > y)
    {
      std::cout << "No intersection!" << std::endl;
      return;
    }

    int start = (a < x) ? x : a;
    int end = (b > y) ? y : b;

    std::cout << "Intersection: [" << start << ", " << end << "]" << std::endl;
  }

  bool isSubinterval(int x, int y)
  {
    return a <= x && b >= y;
  }

private:
  bool isPrime(int a) const
  {
    if (a < 2)
      return false;

    for (int i = 2; i * i <= a; i++)
    {
      if (a % i == 0)
        return false;
    }

    return true;
  }

  bool isPalindrome(int num) const
  {
    int reversed = 0, original = num;
    while (num > 0)
    {
      reversed = reversed * 10 + num % 10;
      num /= 10;
    }
    return original == reversed;
  }

  bool hasRepeatingDigits(int num) const
  {
    bool digits[10] = {false};

    while (num > 0)
    {
      int lastDigit = num % 10;

      if (digits[lastDigit])
        return true;

      digits[lastDigit] = true;
      num /= 10;
    }

    return false;
  }

  int a, b;
};

int main()
{
  Interval interval(1, 3);

  std::cout << std::boolalpha;
  std::cout << "Interval length: " << interval.intervalLength() << std::endl;
  std::cout << "Is number in interval: " << interval.isInInterval(4) << std::endl;
  std::cout << "Prime Numbers Count: " << interval.primeNumbersCount() << std::endl;
  std::cout << "Palindrome Numbers Count: " << interval.palindromesCount() << std::endl;
  std::cout << "Numbers with no repeating digits: " << interval.nonRepeatingDigitsNumbersCount() << std::endl;
  std::cout << "Are interval limits power of 2: " << interval.arePowersOfTwo() << std::endl;
  interval.findIntersection(4, 7);
  std::cout << "Is subinterval: " << interval.isSubinterval(0, 3) << std::endl;

  return 0;
}
