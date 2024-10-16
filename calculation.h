#ifndef CALCULATION_H_ // директива препроцессора, которая проверяет, не включался ли уже файл calculation.h в текущий файл
#define CALCULATION_H_ // директива препроцессора, которая определяет константу M_PI как значение числа пи с высокой точностью

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <float.h>
#include <string.h>

// если не определена константа M_PI то определим ее 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// перечислимый тип для описания ошибок
typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT
} SolutionResult;

// перевод строки str в вещественное число result
SolutionResult StrToDouble (const char *str, double * result);


//double power_binary(double base, int exponent);

// проверка на простое число
int is_prime (int number);

// сумма ряда 1 + 1/n
double sum(int n);

double limit_e(double epsilon);
double row_e(double epsilon);
double equation_e(double epsilon);

double limit_pi(double epsilon);
double row_pi(double epsilon);
double equation_pi(double epsilon);

double limit_ln(double epsilon);
double row_ln(double epsilon);
double equation_ln(double epsilon);

double limit_sqrt(double epsilon);
double row_sqrt(double epsilon);
double equation_sqrt(double epsilon);

double limit_y(double epsilon);
double row_y(double epsilon);
double equation_y(double epsilon);


#endif