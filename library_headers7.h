#ifndef FILE_OPERATIONS_WITH_FLAG_H_
#define FILE_OPERATIONS_WITH_FLAG_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// ������������ ��� ��� ����������� ���������� ����������
typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    ERROR_OPEN_FILE
} SolutionResult;

// ��������� �� ����� � ��������� � ������
SolutionResult ReadInputFromFile(FILE ** input, char** buff, int* len);

// ������� ������������� � ��������
void ConvertToLowercase(char** array, int len);

// ������� ������������� � ������������� �� ASCII-����, ���������� � ������� ��������� � ���������� 8
void ConvertToAsciiBase8(char** array, int len, short ** result);

// ������� ������������� � ������������� �� ASCII-����, ���������� � ������� ��������� � ���������� 4
void ConvertToLowercaseBase4(char** array, int len, short ** result);

#endif