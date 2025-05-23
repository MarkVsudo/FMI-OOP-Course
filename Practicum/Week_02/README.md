## Примери - теория
**1.** Какво ще изведе следният код?
```c++
enum class A : double
{
    Action,
    Adventure
};

int main()
{
    std::cout << (double)A::Action + (double)A::Adventure;
}
```
**2.** Има ли грешки в следния код и ако да - какви?
```c++
#include <iostream>

struct Book
{
    double price;
    char genre;
    int copiesCount;
    bool isSoldOut;
};

bool areEqual(Book b1, Book b2)
{
    return b1.price == b2.price && 
        b1.genre == b2.genre && 
        b1.copiesCount == b2.copiesCount && 
        b1.isSoldOut == b2.isSoldOut;
}

void createBook(Book b)
{
    std::cin >> b.price >> b.genre >> b.copiesCount >> b.isSoldOut;
}

void printBook(Book b)
{
    std::cout << b.price << b.genre << b.copiesCount << b.isSoldOut;
}

int main()
{
    Book b;
    createBook(b);
    printBook(b);

    Book* bookPtr = &b;
    std::cout << bookPtr.genre;
}
```
## Задачи
**1.** Създайте структура ```ParseResult```, която представлява резултат от превръщане на низ в число (parse-ване) и съдържа число и статус код (който може да бъде OK или Error).
Също така, реализирайте функция ```parse```, която приема символен низ, превръща го в число и връща ```ParseResult```.
</br>
**Пример:** </br>
Вход:
```
"123"
```
Изход:
```
{number: 123, statusCode: OK}
```
Вход:
```
"12d3"
```
Изход:
```
{number: _, statusCode: Error}
```
**2.** Създайте структура, която представлява комплексно число. Също така, реализирайте следните функции:
- получаване на комплексно спрегнатото на комплексно число
- събиране на 2 комплексни числа
- изваждане на 2 комплексни числа
- умножение на 2 комплексни числа
- деление на 2 комплексни числа
- сравнение за равенство на 2 комплексни числа
- принтиране на комплексно число
</br>

**3.** Създайте структура, която представлява точка в двумерното пространство. Също така, реализирайте следните функции:
- четене от стандартния вход
- принтиране на стандартния изход
- разстояние между две точки
</br>

**4.** Създайте структура, която представлява фигурата триъгълник. Също така, реализирайте следните функции:
- четене от стандартния вход
- принтиране на стандартния изход
- пресмятане на обиколка
- пресмятане на лице
- връщане на типа на триъгълника спрямо страните му (равнобедрен, равностранен, разностранен)
- връщане на типа на триъгълника спрямо ъглите му (остроъгълен, правоъгълен, тъпоъгълен)
</br>


**5.** Създайте структура, която представлява песен, която съдържа следните характеристики:
- заглавие (до 100 символа)
- изпълнител (до 100 символа)
- жанр (може да бъде Rock, Pop, Thrash Metal, K-pop, Chalga)
- рейтинг (дробно число от 0 до 5)
- брой слушания (цяло число)
</br>

Създайте структура Playlist, която се описва с най-много 64 песни. Реализирайте следните функции:
- добавяне на песен в колекцията (ако капацитетът е запълнен, принтирайте подходящо съобщение)
- връщане на указател към песен по подаден предикат, приемащ като аргумент 1 песен
- сортиране на песните по подаден предикат, приемащ като аргументи 2 песни
