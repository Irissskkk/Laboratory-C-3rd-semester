#ifndef FILE_OPERATIONS_WITH_FLAG_H_
#define FILE_OPERATIONS_WITH_FLAG_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// перечислимый тип дл€ определени€ результата вычислений
typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    ERROR_OPEN_FILE
} SolutionResult;

// прочитать из файла и поместить в массив
SolutionResult ReadInputFromFile(FILE ** input, char** buff, int* len);

// символы преобразованы в строчные
void ConvertToLowercase(char** array, int len);

// символы преобразованы в эквивалентные им ASCII-коды, записанные в системе счислени€ с основанием 8
void ConvertToAsciiBase8(char** array, int len, short ** result);

// символы преобразованы в эквивалентные им ASCII-коды, записанные в системе счислени€ с основанием 4
void ConvertToLowercaseBase4(char** array, int len, short ** result);

#endif