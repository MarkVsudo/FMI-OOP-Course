#include <iostream>

enum StatusCode
{
  OK,
  Error
};

struct ParseResult
{
  int number;
  StatusCode statusCode;
};

ParseResult parse(const char *str)
{
  int number = 0;

  // if empty string
  if (str[0] == '\0')
  {
    return {0, Error};
  }

  for (unsigned i = 0; str[i] != '\0'; i++)
  {
    if (str[i] < '0' || str[i] > '9')
    {
      return {0, Error};
    }

    number = number * 10 + (str[i] - '0');
  }

  return {number, OK};
}

void printResult(ParseResult result)
{
  if (result.statusCode == OK)
  {
    std::cout << "{number: " << result.number << ", statusCode: OK}" << "\n";
  }
  else
  {
    std::cout << "{number: _, statusCode: Error}" << "\n";
  }
}

int main()
{
  const char *test1 = "123";
  const char *test2 = "12d3";
  const char *test3 = "";

  printResult(parse(test1));

  printResult(parse(test2));

  printResult(parse(test3));

  return 0;
}
