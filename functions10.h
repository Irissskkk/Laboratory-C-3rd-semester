#ifndef NUMBER_CONVERSION_H
#define NUMBER_CONVERSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    ERROR_OPEN_FILE
} SolutionResult;


SolutionResult StrTollint(const char *str, long long int * result, int base);


SolutionResult CheckNumberValidation(char* number, int base);


SolutionResult ConvertToBase(char ** result, long long int number, int base, char * array_base);

#endif