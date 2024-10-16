//Task 3!
#ifndef MATH_CALC_WITH_FLAGS_H_
#define MATH_CALC_WITH_FLAGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>

// перечислимый тип для определения результата вычислений
typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR
} SolutionResult;

// перевод строки в вещественное число
SolutionResult StrToDouble(const char *str, double * result);

// перевод строки в целое число
SolutionResult StrToInt(const char *str, long int * result, int base);

// Проверка существования прямоугольного треугольника со сторонами side1, side2 и side3
SolutionResult IsTriangleExists(double epsilon, double side1, double side2, double side3, int* result);

int CheckOverflowDouble(double* num1, double* num2, double epsilon);

// решение квадратного уравнения 'ax2 + bx + c = 0'
// 0 - есть одно решение
// 1 - есть два решения
// -1 - нет решений
int calculateSquareEquation(int a, int b, int c, double *x1, double *x2);

// вывод массива чисел
void PrintD(double *arr, int n);

// перестановка местами 2 чисел
void swapD(double *a, int i, int j);

// перебор сочетаний элементов (работает только в сортированном массиве)
bool NextSetD(double *a, int n, double epsilon);

// Функция быстрой сортировки массива
void quickSortD(double *numbers, int left, int right);

#endif
