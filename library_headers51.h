#ifndef CALCULATION_OF_SUMM_H_
#define CALCULATION_OF_SUMM_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <errno.h>

// перечислимый тип для определения результата вычислений
typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR
} SolutionResult;

// перевод строки в вещественное число
SolutionResult StrToDouble(const char *str, long double * result);

// сумма ряда чисел x^n / n!
void taylor_a(long double x, long double epsilon, long double* result);

// сумма ряда чисел (-1)^n*x^2n / (2n)!
void taylor_b(long double x, long double epsilon, long double* result);

// сумма ряда чисел 3^3n*(n!)^3*x^2n / (3n)!
void taylor_c(long double x, long double epsilon, long double* result);

// сумма ряда чисел (-1)^n*(2n-1)!!*x^2n / (2n)!!
void taylor_d(long double x, long double epsilon, long double* result);

#endif