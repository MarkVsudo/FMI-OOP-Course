// Да се направи функция, която "разшифрова" скрито съобщение.

// Съобщението представлява двоичен файл с неизвестна дължина. Това, което съхранява е поредица от цели неотрицателни числа.

// "Ключът" за съобщението се съхранява в друг двоичен файл и представлява число в интервала [0, 255]. Преценете как е най-подходящо да прочетете и съхраните ключа.

// Шифърът за получаване на правилното съобщение е към всяко число от прочетения файл, съдържащ съобщението да се добави стойността на прочетения ключ

// Пояснение: ако файлът със скритото съобщение след прочитане изглежда така: 23 48 3 12 4006

// А файлът, съдържащ ключа има стойност 2,

// то разшифрованото съобщение трябва да е: 25 50 5 14 4008

// Изведете разшифрованото съобщение на конзолата.

// Пояснение 2: функцията ви трябва да има следната сигнатура

// 	void decypherMessage(const char* rawMessageFileName, const char* keyFileName )

#include <iostream>
#include <fstream>

void inputStartingData(const char *rawMessageFileName, const char *keyFileName)
{
  std::ofstream rawMessageFile(rawMessageFileName, std::ios::binary);
  if (!rawMessageFile)
  {
    std::cerr << "Error opening raw message file!" << std::endl;
    return;
  }

  int n;
  std::cout << "Enter the amount of numbers for your message: ";
  std::cin >> n;

  int *numbers = new int[n];
  for (int i = 0; i < n; i++)
  {
    std::cout << "Number " << i + 1 << ": ";
    std::cin >> numbers[i];
  }

  rawMessageFile.write((char *)(numbers), n * sizeof(int));
  rawMessageFile.close();
  delete[] numbers;

  std::ofstream keyFile(keyFileName, std::ios::binary);
  if (!keyFile)
  {
    std::cerr << "Error opening key file!" << std::endl;
    return;
  }

  uint8_t key;
  do
  {
    std::cout << "Enter a key [0,255]: ";
    std::cin >> key;
  } while (key < 0 || key > 255);
  keyFile.write((char *)(&key), sizeof(key));
  keyFile.close();
}

void decypherMessage(const char *rawMessageFileName, const char *keyFileName)
{
  std::ifstream rawMessageFile(rawMessageFileName, std::ios::binary | std::ios::ate);
  if (!rawMessageFile)
  {
    std::cerr << "Error reading raw message file!" << std::endl;
    return;
  }

  size_t rawMessageFileSize = rawMessageFile.tellg();
  rawMessageFile.seekg(0);

  size_t numbersCount = rawMessageFileSize / sizeof(int);
  int *decypheredNumbers = new int[numbersCount];
  rawMessageFile.read((char *)decypheredNumbers, numbersCount * sizeof(int));
  rawMessageFile.close();

  std::ifstream keyFile(keyFileName, std::ios::binary);
  if (!keyFile)
  {
    std::cerr << "Error reading key file!" << std::endl;
    return;
  }
  uint8_t key;
  keyFile.read((char *)(&key), sizeof(key));
  keyFile.close();

  for (size_t i = 0; i < numbersCount; i++)
  {
    decypheredNumbers[i] += key;
    std::cout << decypheredNumbers[i] << " ";
  }

  delete[] decypheredNumbers;
}

int main()
{
  const char *rawMessageFileName = "encrypted_data.dat";
  const char *keyFileName = "key.dat";

  inputStartingData(rawMessageFileName, keyFileName);
  decypherMessage(rawMessageFileName, keyFileName);

  return 0;
}