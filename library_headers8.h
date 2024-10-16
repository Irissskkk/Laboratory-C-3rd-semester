#ifndef NUMBER_BASE_DETECTION_H_
#define NUMBER_BASE_DETECTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

// перечислимый тип для определения результата вычислений
typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    ERROR_OPEN_FILE
} SolutionResult;

// преобразует строку в длинное длинное число
SolutionResult StrTollint(const char *str, long long int * result, int base);

// прочитать содержимое файла и отправить в буфер
SolutionResult ReadInputFromFile(FILE ** input, char** buff, int* len, int* min_base, int * capacity);

#endif