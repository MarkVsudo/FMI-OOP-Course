#include "csvManager.h"

int main()
{
  try
  {
    CSVManager manager;
    manager.run();
  }
  catch (const std::exception &e)
  {
    std::cerr << "An error occurred: " << e.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown fatal error occurred" << std::endl;
    return 1;
  }

  return 0;
}
