//=== src/main.cpp ===
#include "CommandProcessor.h"
#include "Exception.h"
#include <iostream>
#include <vector>
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