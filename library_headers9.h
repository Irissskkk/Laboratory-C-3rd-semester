#ifndef ARRAY_OPERATIONS_H_
#define ARRAY_OPERATIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

typedef enum 
{
    VALID,
    INVALID_MEMORY,
    INVALID_INPUT,
    OVERFLOW_ERROR,
    ERROR_OPEN_FILE
} SolutionResult;

SolutionResult StrToInt (const char *str, long int * result, int base);

// ������� ������ �� ��������� �����
SolutionResult GenerateArray(long int start_for_generation,
                             long int end_for_genetation,
                             long int ** result_array,
                             int size_of_array);
                             
// �������� ������� ��� � ���� �������� �������
void SwapMinMaxArray(long int ** array, int size_of_array);

// ������� ������ �� ��������� ����� � ��������� start_for_generation � end_for_genetation, �������� size_of_array
SolutionResult GenerateArrayTask2(int start_for_generation, int end_for_genetation,
                                      short ** result_array, int size_of_array);
                                      
// ������� ������ �� ���� ������� �������� � ������ ��������� �� �������� ��������� ���� ��������                                      
SolutionResult GenerateArrayOfClosestValues(short ** array_a, int size_of_array_a,
                                            short ** array_b, int size_of_array_b,
                                            short ** array_c);
// ����������� ���������� �������
void BubbleSort(short** arr, int size);

// ����� ���������� �� �������� �������� �������
short FindClosest(short ** array, int size, short number);

#endif