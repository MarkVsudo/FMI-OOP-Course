// Създайте клас NumberSeries, който моделира работата с числова редица. В конструктора на класа ще приемате цяло число - начална стойност на редицата (a_0) и указател към функция на преход, приемаща цяло число и връщаща цяло число (a_i = f(a_i-1)).

// Трябва да имате следните функционалности:

// Генериране на i-то число от редицата.
// Проверка дали подадено число е част от редицата.
// Setter-и за нова начална стойност и нова функция на преход.
// Генерирането на стойности трябва да бъде оптимизирано откъм скорост:

// За коректна работа с фунцкионалността за генериране на i-то по ред число, трябва да поддържате динамичен масив в класа, в който да пазите досега генерираните стойности.
// Ако числото вече е било генерирано, трябва да го върнете като резултат без да го генерирате повторно.
// Ако числото го няма в масива, генерирайте и добавете към масива всички числа, които липсват до a_i в редицата и върнете генерираната стойност.
// Ако в масива няма достатъчно място, за да се съхранят новите стойности, преоразмерете го по подходящ начин.
// При set-ване на нова начална стойност или функция на преход, трябва да изтривате динамичния масив и да започвате процеса на запазване отначало.
// Помислете как трябва да се handle-не коректно копирането на обекти от вашия клас.

#include <iostream>

class NumberSeries
{
public:
  NumberSeries(int a_0, int (*transitionFuncPtr)(int))
  {
    cap = 10;
    size = 1;
    numSeries = new int[cap];
    setTransitionFunc(transitionFuncPtr);
    setA_0(a_0);
  }

  ~NumberSeries()
  {
    delete[] numSeries;
  }

  // Генериране на i-то число от редицата.
  int generateIthNum(int pos)
  {
    if (pos <= size)
    {
      return numSeries[pos - 1];
    }

    if (pos > cap)
    {
      while (cap < pos)
      {
        cap *= 2;
      }

      int *newSeries = new int[cap];
      for (int i = 0; i < size; i++)
      {
        newSeries[i] = numSeries[i];
      }

      delete[] numSeries;
      numSeries = newSeries;
    }

    // Generate and store new values
    for (int i = size; i < pos; i++)
    {
      numSeries[i] = transitionFuncPtr(numSeries[i - 1]);
    }

    size = pos;
    return numSeries[pos - 1];
  }

  bool isNumInSeries(int num) const
  {
    for (int i = 0; i < size; i++)
    {
      if (numSeries[i] == num)
        return true;
    }
    return false;
  }

  void setA_0(int a_0)
  {
    this->a_0 = a_0;

    // Reset array
    delete[] numSeries;
    cap = 10;
    size = 1;
    numSeries = new int[cap];
    numSeries[0] = a_0;
  }

  void setTransitionFunc(int (*transitionFuncPtr)(int))
  {
    this->transitionFuncPtr = transitionFuncPtr;

    // Reset array using current a_0
    delete[] numSeries;
    cap = 10;
    size = 1;
    numSeries = new int[cap];
    numSeries[0] = a_0;
  }

  void printNumSeries() const
  {
    std::cout << "Number series -> [";
    for (int i = 0; i < size; i++)
    {
      std::cout << numSeries[i] << (i == size - 1 ? "" : ", ");
    }
    std::cout << "]\n";
  }

  int getSize() const
  {
    return size;
  }

private:
  int a_0;
  int size;
  int cap;
  int *numSeries;
  int (*transitionFuncPtr)(int);
};

int addTwo(int a)
{
  return a + 2;
}

int main()
{
  NumberSeries numberSeries(2, addTwo);

  numberSeries.printNumSeries();
  std::cout << "Number series size: " << numberSeries.getSize() << std::endl;
  std::cout << std::boolalpha;
  std::cout << "Is number in series: " << numberSeries.isNumInSeries(2) << std::endl;
  std::cout << "i-th number: " << numberSeries.generateIthNum(9) << std::endl;
  numberSeries.printNumSeries();
  std::cout << "i-th number: " << numberSeries.generateIthNum(3) << std::endl;
  numberSeries.printNumSeries();

  return 0;
}
