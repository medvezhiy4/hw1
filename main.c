/*
 * ДЗ 1. Обработка одномерного массива.
 * Вар 5: Удаление повторений - формируем новый массив в котором каждое значение исходного массива встречается только один раз
 * Компиляция: gcc main.c -Wall -Wextra -Wpedantic -std=c11 -o homework1
 */

#include <stdio.h> // printf, scanf
#include <stdlib.h> // exit - завершение проги при неверном вводе элементов

#define MAX_SIZE 100 // максимальный размер массива по условию задачи

// Прототипы функций
void inputArray(int array[], int size); // ввод с клавы
void printArray(const int array[], int size); // вывод в одну стр
int findMin(const int array[], int size); // мин элемент
int findMax(const int array[], int size); // макс элемент
int findFirstIndex(const int array[], int size, int value); // первый индекс значения
long long calculateSum(const int array[], int size); // сум элементов
double calculateAverage(const int array[], int size); // ср ариф
void printSignCounts(const int array[], int size); // сколько >0 <0 и =0
void printParityCounts(const int array[], int size); // сколько чёт и нечёт
void printInRange(const int array[], int size, int a, int b); // эл из диапазона [a, b]
void performIndividualTask(const int array[], int size); // вар 5 без повт

int main(void)
{
    int array[MAX_SIZE]; // исх массив (с запасом на макс разм)
    int size; // скок эл вводить
    int minValue; // мин эл массива
    int maxValue; // макс эл массива
    int a; // лев гран диап
    int b; // прав гран диап

    // 1. просим разм массива и проверяем его допустимост
    // если сканф не прочитал число или число не в диапазоне 1-100 - выходим отсюдова
    printf("Введите размер массива от 1 до %d: ", MAX_SIZE);
    if (scanf("%d", &size) != 1 || size < 1 || size > MAX_SIZE)
    {
        printf("Ошибко: недопустимый размер массива (давай от 1 до %d).\n", MAX_SIZE);
        return 1; // массив не вводим и не обрабатываем
    }

    // 2. Вводим эл и выводим исх масс в одной стр
    inputArray(array, size);
    printf("Исходный массив:");
    printArray(array, size);

    // 3. Мин и макс Индекс ищем отдельной функ (первое вхождение)
    minValue = findMin(array, size);
    maxValue = findMax(array, size);
    printf("Минимальный элемент: %d (первый индекс: %d)\n",
           minValue, findFirstIndex(array, size, minValue));
    printf("Максимальный элемент: %d (первый индекс: %d)\n",
           maxValue, findFirstIndex(array, size, maxValue));

    // 4. Сумма эл и ср ариф (вещ чис)
    printf("Сумма элементов: %lld\n", calculateSum(array, size));
    printf("Среднее арифметическое: %.2f\n", calculateAverage(array, size));

    // 5. Колво положительных отрицательных нулевых чёт и нечёт
    printSignCounts(array, size);
    printParityCounts(array, size);

    // 6. Просим гр диап [a, b] и выводим эл из него
    printf("Введите границы диапазона a и b через пробел: ");
    if (scanf("%d %d", &a, &b) != 2)
    {
        printf("Ошибк: границы диапазона должны быть целыми числами.\n");
        return 1;
    }
    printInRange(array, size, a, b);

    // 7. вариант 5: удаление повторений
    performIndividualTask(array, size);

    return 0; // программа завершилась успешно
}

// Ввод и вывод

/*
 * Вводит size целых чис с клавы в массив array
 * Если введено не целое чис - сообщает об ошибке и заверш прогу
 */
void inputArray(int array[], int size)
{
    int i; // индекс эл который вводим

    printf("Введите элементы массива (количество: %d): ", size);

    for (i = 0; i < size; i++)
    {
        // scanf возвращает 1 если удалось прочитать одно цел чис
        if (scanf("%d", &array[i]) != 1)
        {
            printf("Ошибка: элементы массива должны быть целыми числами.\n");
            exit(1); // заверш прогу с кодом ошибки (как return 1 в main)
        }
    }
}

/*
 * Выводит size эл масс в одной стр через пробел
 * Пробел печат ПЕРЕД числом, поэтому подпись перед вызовом
 * пишется без пробела на конце (например, "Исходный массив:")
 */
void printArray(const int array[], int size)
{
    int i; // индекс выводимого эл

    for (i = 0; i < size; i++)
    {
        printf(" %d", array[i]);
    }

    printf("\n"); // переход на новую строку после посл эл
}

// Основная обработка 

/* Возвращает мин эл масс (size >= 1) */
int findMin(const int array[], int size)
{
    int min = array[0]; // пока считаем мин перв эл
    int i; // индекс сравниваемого эл

    // Сравниваем со вторым третьим и тд до конца масс
    for (i = 1; i < size; i++)
    {
        if (array[i] < min)
        {
            min = array[i]; // нашли элемент меньше - запоминаем
        }
    }

    return min;
}

/* Возвращает макс эл масс (size >= 1). */
int findMax(const int array[], int size)
{
    int max = array[0]; // пока считаем макс первый эл
    int i; // индекс сравниваемого эл

    // Сравниваем со вторым третьим и тд до конца масс
    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i]; // нашли элемент больше - запоминаем
        }
    }

    return max;
}

/*
 * Возвращает индекс ПЕРВОГО элемента, равного value
 * Если такого элемента нет - возвращает -1 (в проге value всегда взято из масс, так что -1 не встретится)
 */
int findFirstIndex(const int array[], int size, int value)
{
    int i; // индекс проверяемого эл

    for (i = 0; i < size; i++)
    {
        if (array[i] == value)
        {
            return i; // нашли первое совпадение - сразу возвращаем его индек
        }
    }

    return -1; // значение не найдено
}

/* Возвращает сум всех эл масс */
long long calculateSum(const int array[], int size)
{
    long long sum = 0; // long long, чтобы сумма не переполнилась
    int i; // индекс прибавляемого эл

    for (i = 0; i < size; i++)
    {
        sum += array[i]; // прибавляем очередной эл к сум
    }

    return sum;
}

/*
 * Возвращает ср ариф эл (вещ чис)
 * Деления на ноль нет: main гарантирует, что size >= 1
 */
double calculateAverage(const int array[], int size)
{
    // double делает деление вещ, иначе дробная часть потерялась бы
    return (double)calculateSum(array, size) / size;
}

/* Считает и выводит колво полож отриц и нулевых эл */
void printSignCounts(const int array[], int size)
{
    int positive = 0; // счётчик полож эл
    int negative = 0; // счётчик отриц эл
    int zero = 0; // счётчик нулевых эл
    int i; // индекс проверяемого эл

    for (i = 0; i < size; i++)
    {
        if (array[i] > 0)
        {
            positive++;
        }
        else if (array[i] < 0)
        {
            negative++;
        }
        else
        {
            zero++; // остался единст вар - эл равен 0
        }
    }

    printf("Положительных: %d, отрицательных: %d, нулевых: %d\n", positive, negative, zero);
}

/* Считает и выводит колво чёт и нечёт эл */
void printParityCounts(const int array[], int size)
{
    int even = 0; // счётчик чёт эл
    int odd = 0; // счётчик нечёт эл
    int i; // индекс проверяемого эл

    for (i = 0; i < size; i++)
    {
        // Остаток от дел на 2 равен 0 - число чёт
        // Нечёт проверяем через else, а не через "% 2 == 1"
        // у отриц нечёт чис остаток равен -1
        if (array[i] % 2 == 0)
        {
            even++;
        }
        else
        {
            odd++;
        }
    }

    printf("Чётных: %d, нечётных: %d\n", even, odd);
}

/* Выводит эл масс, принадлеж диапазону [a, b] (границы входят) */
void printInRange(const int array[], int size, int a, int b)
{
    int count = 0; // скок эл попало в диап
    int i; // индекс проверяемого эл

    printf("Элементы из диапазона [%d, %d]:", a, b);

    for (i = 0; i < size; i++)
    {
        // Эл подходит, если a <= эл <= b
        // Если a > b, усл никогда не выпол - подх эл не будет
        if (array[i] >= a && array[i] <= b)
        {
            printf(" %d", array[i]);
            count++; // запоминаем что хотя бы один элемент нашёлся
        }
    }

    // Если ни один эл не подошёл то сообщаем
    if (count == 0)
    {
        printf(" таких элементов нет");
    }

    printf("\n"); // переход на новую строку
}

// задание вариант 5

/*
 * Форм новый масс в котором каждое знач исх масс встречается только 1 раз (порядок по первому появлению), и выводит его
 */
void performIndividualTask(const int array[], int size)
{
    int uniqueArray[MAX_SIZE]; // новый масс без повт
    int uniqueSize = 0; // скок эл уже лежит в новом масс
    int found; // 1 - значение уже есть в новом масс, 0 - ещё нет
    int i; // индекс по исх масс
    int j; // индекс по новому масс

    // Идём по исх масс слева направо
    for (i = 0; i < size; i++)
    {
        found = 0; // для нового эл считаем что такого значения ещё не было

        // Ищем array[i] среди уже добавленных эл нового масс
        // Цикл останавливается, как только знач найдено (found станет 1)
        for (j = 0; j < uniqueSize && found == 0; j++)
        {
            if (uniqueArray[j] == array[i])
            {
                found = 1; // такое знач уже есть
            }
        }

        // Если знач в новом массиве ещё нет то добавляем его в конец
        if (found == 0)
        {
            uniqueArray[uniqueSize] = array[i];
            uniqueSize++; // в новом масс стало на один эл больше
        }
    }

    // Вывод новый масс. Эл в нём не больше size <= MAX_SIZE,
    // поэтому выхода за границы масс не будет
    printf("Массив без повторений:");
    printArray(uniqueArray, uniqueSize);
}
