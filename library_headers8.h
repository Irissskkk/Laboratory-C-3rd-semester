#ifndef NUMBER_BASE_DETECTION_H_
#define NUMBER_BASE_DETECTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

// ������������ ��� ��� ����������� ���������� ����������
typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    ERROR_OPEN_FILE
} SolutionResult;

// ����������� ������ � ������� ������� �����
SolutionResult StrTollint(const char *str, long long int * result, int base);

// ��������� ���������� ����� � ��������� � �����
SolutionResult ReadInputFromFile(FILE ** input, char** buff, int* len, int* min_base, int * capacity);

#endif