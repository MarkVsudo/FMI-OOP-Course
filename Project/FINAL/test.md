# Команди за тестване на CSV Manager

## 1. Подготовка на тестови данни

Първо създайте тестови CSV файлове:

### test_students.csv

```csv
Name,Age,Grade,EGN,Faculty_Number,Salary
"Иван Петров",20,85.5,9512154321,12345,1250.50BGN
"Мария Георгиева",19,92.0,0012184567,0CS0400123,1350.75BGN
"Петър Стоянов",21,78.3,8905123456,54321,1180.25BGN
"Анна Димитрова",20,88.7,9801234567,0IT0400124,1420.00BGN
"Стефан Николов",22,94.2,9701123456,11111,1500.50BGN
"Елена Попова",19,76.8,0112185432,0CS0400125,1100.75BGN
"Иван Петров",20,85.5,9512154321,12345,1250.50BGN
```

### test_products.csv

```csv
Product,Price,Category,Stock
"Laptop",1200.50EUR,Electronics,15
"Mouse",25.99USD,Electronics,50
"Keyboard",45.00EUR,Electronics,30
"Chair",150.75BGN,Furniture,8
"Desk",300.00BGN,Furniture,5
"Monitor",250.99EUR,Electronics,12
```

## 2. Основни операции

### Стартиране и помощ

```bash
# Стартиране на програмата
./csv_manager

# Показване на помощ
help
```

### Зареждане на файлове

```bash
# Зареждане на файл с headers
open test_students.csv true ,

# Зареждане на файл без headers
open test_products.csv false ;

# Зареждане с различен delimiter
open test_data.csv true ;
```

## 3. Преглед на данни

```bash
# Показване на таблицата
print
```

## 4. Сортиране

```bash
# Сортиране по име (възходящо)
sort Name

# Сортиране по възраст (низходящо)
sort Age desc

# Сортиране по оценка (възходящо)
sort Grade asc

# Сортиране по факултетен номер
sort Faculty_Number

# Сортиране по заплата
sort Salary desc
```

## 5. Филтриране

```bash
# Филтриране по възраст
filter Age > 20
filter Age <= 19
filter Age == 20

# Филтриране по оценка
filter Grade >= 90
filter Grade < 80

# Филтриране по име
filter Name == "Иван Петров"
filter Name != "Мария Георгиева"

# Филтриране по заплата
filter Salary > 1300.00BGN
filter Salary <= 1200.00BGN

# Филтриране по факултетен номер
filter Faculty_Number == 12345
```

## 6. Управление на колони

```bash
# Премахване на колона
remove_column EGN

# Дублиране на колона
duplicate_column Name
duplicate_column Age New_Age

# Дублиране без ново име (автоматично _copy)
duplicate_column Grade
```

## 7. Управление на редове

```bash
# Премахване на дублиращи се редове
remove_duplicates

# Добавяне на ред с минимални стойности
add_row min

# Добавяне на ред с максимални стойности
add_row max

# Добавяне на ред с най-честите стойности
add_row mode

# Копиране на ред номер 1
add_row copy 1

# Копиране на ред номер 3
add_row copy 3
```

## 8. Редактиране на клетки

```bash
# Промяна на стойност в клетка
set_cell Name 1 "Нико Белчев"
set_cell Age 2 25
set_cell Grade 3 95.5
set_cell Salary 1 1600.00BGN

# Промяна на факултетен номер
set_cell Faculty_Number 2 0MA0400999
```

## 9. Undo функционалност

```bash
# Отмяна на последната операция
undo

# Тест на undo след различни операции:
sort Name
undo

filter Age > 20
undo

remove_column Age
undo

add_row min
undo
```

## 10. Запазване

```bash
# Запазване в същия файл
save

# Запазване в нов файл
save output.csv

# Запазване с ново име
save students_modified.csv
```

## 11. Тестове за грешки

```bash
# Невалидни команди
invalid_command

# Невалидни параметри
sort NonExistentColumn
filter Name >> "test"
remove_column NonExistentColumn
set_cell Name -1 "test"
add_row invalid_type

# Празни параметри
sort
filter
save ""
```

## 12. Комплексни тестове

### Тест 1: Пълна обработка на студентски данни

```bash
open test_students.csv
print
sort Age desc
print
filter Grade >= 85
print
remove_duplicates
print
add_row max
print
duplicate_column Name Full_Name
print
set_cell Full_Name 1 "Иван Стоянов Петров"
print
save students_processed.csv
```

### Тест 2: Тест на undo функционалност

```bash
open test_students.csv
print
sort Name
print
undo
print
filter Age > 20
print
remove_column EGN
print
undo
print
add_row min
print
undo
print
```

### Тест 3: Тест с различни типове данни

```bash
open test_students.csv
print
# Сортиране по ЕГН (число)
sort EGN
print
# Сортиране по факултетен номер (специален тип)
sort Faculty_Number
print
# Сортиране по заплата (валута)
sort Salary desc
print
# Филтриране по валута
filter Salary > 1300.00BGN
print
```

## 13. Край на сесията

```bash
# Излизане от програмата
exit

# При несъхранени промени ще бъде попитано дали да се съхранят
```

## Допълнителни тестове

### Тест с голям файл

Създайте файл с повече данни и тествайте производителността:

```bash
open large_dataset.csv
sort Name
filter Age > 25
remove_duplicates
save large_processed.csv
```

### Тест с различни delimiters

```bash
open semicolon_data.csv true ;
open tab_data.csv true "\t"
open pipe_data.csv true |
```

### Тест със специални символи

Тествайте с данни съдържащи:

* Кавички в текста
* Запетаи в стойностите
* Празни клетки
* Специални символи

## Очаквани резултати

При правилно изпълнение на командите трябва да наблюдавате:

* Коректно зареждане и показване на данни
* Правилно сортиране според типа данни
* Точно филтриране по зададените критерии
* Успешно премахване на дублирани редове
* Работеща undo функционалност
* Запазване на файлове в правилен CSV формат

При грешки програмата трябва да показва подходящи съобщения без да се затваря.
