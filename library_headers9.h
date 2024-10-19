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

// сделать массив из случайных чисел
SolutionResult GenerateArray(long int start_for_generation,
                             long int end_for_genetation,
                             long int ** result_array,
                             int size_of_array);
                             
// поменять местами мин и макс элементы массива
void SwapMinMaxArray(long int ** array, int size_of_array);

// сделать массив из случайных чисел в диапазоне start_for_generation и end_for_genetation, размером size_of_array
SolutionResult GenerateArrayTask2(int start_for_generation, int end_for_genetation,
                                      short ** result_array, int size_of_array);
                                      
// сделать массив из двух входных массивов с суммой ближайших по значению элементов этих массивов                                      
SolutionResult GenerateArrayOfClosestValues(short ** array_a, int size_of_array_a,
                                            short ** array_b, int size_of_array_b,
                                            short ** array_c);
// пузырьковая сортировка массива
void BubbleSort(short** arr, int size);

// поиск ближайшего по значению элемента массива
short FindClosest(short ** array, int size, short number);

#endif