//=== src/main.cpp ===
#include "io/CommandProcessor.h"
#include "utils/Exception.h"
#include <iostream>

int main()
{
  try
  {
    CommandProcessor processor;
    processor.run();
  }
  catch (const std::exception &e)
  {
    std::cout << "Fatal error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}