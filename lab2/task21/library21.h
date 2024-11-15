#ifndef OPERATION_WITH_FLAG_H
#define OPERATION_WITH_FLAG_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    ERROR_OPEN_FILE
} SolutionResult;

int string_len(const char *str);
SolutionResult string_reverse(const char *str, char **result);
SolutionResult odd_to_upper(const char *str, char **result);
SolutionResult change_string(const char *str, char **result);
SolutionResult convert_str_to_int (const char *str, unsigned int * result, int base);
SolutionResult concat_random (char **strs, int count_str, char **result, unsigned int seed);
void concat_string(char *str, char **result, int *len);

#endif