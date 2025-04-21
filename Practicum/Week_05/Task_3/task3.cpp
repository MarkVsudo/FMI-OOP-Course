#include <iostream>
#include <fstream>

void printHexByte(unsigned char byte)
{
  const char hexChars[] = "0123456789ABCDEF";
  std::cout << hexChars[byte / 16] << hexChars[byte % 16] << " ";
}

void printCharRepresentation(unsigned char byte)
{
  if ((byte >= 'A' && byte <= 'Z') || (byte >= 'a' && byte <= 'z'))
  {
    std::cout << (char)byte;
  }
  else
  {
    std::cout << ".";
  }
}

void viewFileInHex(std::ifstream &file, size_t fileSize)
{
  if (!file)
  {
    std::cerr << "Error opening file!" << std::endl;
    return;
  }

  unsigned char *buffer = new unsigned char[fileSize];
  file.read((char *)buffer, fileSize);

  for (size_t i = 0; i < fileSize; i++)
  {
    printHexByte(buffer[i]);
  }
  std::cout << std::endl;

  for (size_t i = 0; i < fileSize; i++)
  {
    printCharRepresentation(buffer[i]);
    std::cout << " ";
  }
  std::cout << std::endl;

  delete[] buffer;
}

int main()
{
  constexpr size_t FILENAME_BUFFER_SIZE = 512;
  char fileName[FILENAME_BUFFER_SIZE];
  std::cout << "Enter file name: ";
  std::cin >> fileName;

  int x = 25409;
  std::ofstream outFile(fileName, std::ios::binary);
  if (!outFile)
  {
    std::cerr << "Error opening file for writing!" << std::endl;
    return -1;
  }
  outFile.write((const char *)&x, sizeof(x));
  outFile.close();

  std::ifstream inFile(fileName, std::ios::binary | std::ios::ate);
  if (!inFile)
  {
    std::cerr << "Error opening file for reading!" << std::endl;
    return -2;
  }
  size_t fileSize = inFile.tellg();
  inFile.seekg(0, std::ios::beg);

  std::cout << "File loaded successfully! Size: " << fileSize << " bytes\n";
  while (true)
  {

    int option;
    std::cout << "-- Select an option from the following --\n0) Exit\n1) View file\n2) Change byte at index\n3) Remove last byte\n4) Add a byte at the end\n5) Save changes in the same file\n6) Save changes in another file\n";
    std::cin >> option;

    switch (option)
    {
    case 0:
      std::cout << "Exiting...";
      return 0;
    case 1:
      std::cout << "Viewing file bytes in HEX mode\n";
      viewFileInHex(inFile, fileSize);
      break;
    case 2:
    {
      int index, value;
      std::cout << "Enter an index and a value: ";
      std::cin >> index >> value;
      break;
    }
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    default:
      std::cout << "Invalid option!";
    }
  }

  return 0;
}
