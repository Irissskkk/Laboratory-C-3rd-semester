#include "library_headers.h"
// перевод строки в вещественное число
SolutionResult StrToDouble(const char *str, double *result)
{
    char *endptr;
    *result = strtold(str, &endptr);
    if (errno == ERANGE && (*result == HUGE_VALL || *result == -HUGE_VALL))
    {
        return INVALID_INPUT;
    }
    else if (errno == ERANGE && *result == 0)
    {
        return INVALID_INPUT;
    }
    else if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    return VALID;
}
// перевод строки в целое число
SolutionResult StrToInt(const char *str, long int *result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN))
    {
        return INVALID_INPUT;
    }
    else if (errno != 0 && *result == 0)
    {
        return INVALID_INPUT;
    }
    else if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }

    return VALID;
}
// проверка переполнения при перемножении
int CheckOverflowDouble(double *num1, double *num2, double epsilon)
{
    epsilon *= 1;
    long double result = *num1 * *num2;
    return (result - DBL_MAX <= epsilon && result + DBL_MAX >= epsilon);
}

// решение квадратного уравнения 'ax2 + bx + c = 0'
// 0 - есть одно решение
// 1 - есть два решения
// -1 - нет решений
int calculateSquareEquation(int a, int b, int c, double *x1, double *x2)
{
    double D;
    D = b * b - 4 * a * c;
    if (a == 0)
    {
        *x1 = (double)-c / b;
        return 0;
    }
    else if (D > 0)
    {
        *x1 = (double)(-b + sqrt(D)) / (2 * a);
        *x2 = (double)(-b - sqrt(D)) / (2 * a);
        return 1;
    }
    else if (D == 0)
    {
        *x1 = (double)-b / (2 * a);
        return 0;
    }
    else
    {
        return -1;
    }
}
// вывод массива чисел
void PrintD(double *arr, int n) 
{
    static int num = 1; // номер перестановки
    printf("%d: ", num++);
    int i;
    for (i = 0; i < n; i++)
    {
        printf(" %Lf", arr[i]);
    }
    printf("\n");
}
// перестановка местами 2 чисел
void swapD(double *a, int i, int j)
{
    double s = a[i];
    a[i] = a[j];
    a[j] = s;
}
// перебор сочетаний элементов (работает только в сортированном массиве)
bool NextSetD(double *a, int n, double epsilon)
{
    int j = n - 2;
    while (j != -1 && (a[j] > a[j + 1] || fabsl(a[j] - a[j + 1]) < epsilon))
        j--;
    if (j == -1)
        return false; // больше перестановок нет
    int k = n - 1;
    while (a[j] > a[k] || fabsl(a[j] - a[k]) < epsilon)
        k--;
    swapD(a, j, k);
    int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
    while (l < r)
        swapD(a, l++, r--);
    return true;
}

// Функция быстрой сортировки массива
void quickSortD(double *numbers, int left, int right)
{
    double pivot;       // разрешающий элемент
    int index;          // индекс разрешающего элемента
    int l_hold = left;  // левая граница
    int r_hold = right; // правая граница
    pivot = numbers[left];
    while (left < right) // пока границы не сомкнутся
    {
        while ((numbers[right] > pivot) && (left < right))
            right--;       // сдвигаем правую границу пока элемент [right] больше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
            left++;                         // сдвигаем левую границу вправо
        }
        while ((numbers[left] < pivot) && (left < right))
            left++;        // сдвигаем левую границу пока элемент [left] меньше [pivot]
        if (left != right) // если границы не сомкнулись
        {
            numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
            right--;                        // сдвигаем правую границу влево
        }
    }
    numbers[left] = pivot; // ставим разрешающий элемент на место
    index = left;
    left = l_hold;
    right = r_hold;
    if (left < index) // Рекурсивно вызываем сортировку для левой и правой части массива
        quickSortD(numbers, left, index - 1);
    if (right > index)
        quickSortD(numbers, index + 1, right);
}
// Проверка существования прямоугольного треугольника со сторонами side1, side2 и side3
SolutionResult IsTriangleExists(double epsilon, double side1, double side2, double side3, int *result)
{
    if (!CheckOverflowDouble(&side1, &side1, epsilon) || !CheckOverflowDouble(&side2, &side2, epsilon) || !CheckOverflowDouble(&side3, &side3, epsilon))
        return OVERFLOW_ERROR; // проверить переполнение памяти под переменные

    if (side1 <= epsilon || side2 <= epsilon || side3 <= epsilon)
        return INVALID_INPUT; // слишком маленькие стороны

    if (fabsl(side1 * side1 + side2 * side2 - side3 * side3) <= epsilon ||
        fabsl(side1 * side1 + side3 * side3 - side2 * side2) <= epsilon ||
        fabsl(side2 * side2 + side3 * side3 - side1 * side1) <= epsilon)
        *result = 1;
    else
        *result = 0;

    return VALID;
}
