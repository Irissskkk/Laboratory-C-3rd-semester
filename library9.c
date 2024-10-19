#include "library_headers9.h"
#include <unistd.h>

// преобразовать строку в целое число
SolutionResult StrToInt(const char *str, long int * result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN))
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return VALID;
}

// сделать массив из случайных чисел
SolutionResult GenerateArray(long int start_for_generation,
                      long int end_for_genetation,
                      long int ** result_array,
                      int size_of_array)
{
    (*result_array) = (long int *) malloc(size_of_array * sizeof(long int));
    if ((*result_array) == NULL)
    {
        return INVALID_MEMORY;
    }
    srand(time(NULL));
    int i;
    for(i = 0; i < size_of_array; ++i)
    {
        (*result_array)[i] = rand() % (labs(end_for_genetation) + 1 - labs(start_for_generation)) + start_for_generation;
    }
    return VALID;
}

// поменять местами мин и макс элементы массива
void SwapMinMaxArray(long int ** array, int size_of_array)
{
    int min_ind = 0;
    int max_ind = 0;
    int i;
    for(i = 0; i < size_of_array; ++i)
    {
        if((*array)[i] < (*array)[min_ind]) min_ind = i;
        if((*array)[i] > (*array)[max_ind]) max_ind = i;
    }
    long int temp = (*array)[max_ind];
    (*array)[max_ind] = (*array)[min_ind];
    (*array)[min_ind] = temp;
}

// сделать массив из случайных чисел в диапазоне start_for_generation и end_for_genetation, размером size_of_array
SolutionResult GenerateArrayTask2(int start_for_generation, int end_for_genetation, short ** result_array, int size_of_array)
{
    (*result_array) = (short *) malloc(size_of_array * sizeof(short));
    if ((*result_array) == NULL)
    {
        return INVALID_MEMORY;
    }
    int i, j;
    
    for(i = 0; i < size_of_array; ++i)
    {
        int num;
        do {
            //num = rand();
            num = start_for_generation + rand() % (end_for_genetation - start_for_generation + 1);
        } while (num < start_for_generation || num > end_for_genetation);
        (*result_array)[i] = (short)num;
        //(*result_array)[i] = (short )(rand() % (labs(end_for_genetation) + 1 - labs(start_for_generation)) + start_for_generation);
    }
    printf("Log: array is created, size = %d\n", size_of_array); //Лог: массив сгенерирован
    return VALID;
}

// сделать массив из двух входных массивов с суммой ближайших по значению элементов этих массивов
SolutionResult GenerateArrayOfClosestValues(short ** array_a, int size_of_array_a,
                                            short ** array_b, int size_of_array_b,
                                            short ** array_c)
{
    (*array_c) = (short*) malloc(sizeof(short) * size_of_array_a);
    if (array_c == NULL)
    {
        free(array_a);
        return INVALID_MEMORY;
    }
    (*array_c) = (short*) malloc(sizeof(short) * size_of_array_a);
    BubbleSort(array_b, size_of_array_b);
    printf("\nLog: array b is sorted\n"); // Лог: массив b отсортирован
    int i;
    for(i = 0; i < size_of_array_a; ++i)
    {
        (*array_c)[i] = (*array_a)[i] + FindClosest(array_b, size_of_array_b, (*array_a)[i]);
    }
    //printf("\nLog: array is created\n"); //Лог: массив сгенерирован
    return VALID;
}

// пузырьковая сортировка массива
void BubbleSort(short** array, int size)
{
	int i;
    for (i = 0; i < size - 1; i++) {
    	int j;
        for (j = 0; j < size - i - 1; j++) {
            if (abs((*array)[j]) > abs((*array)[j+1])) {
                int temp = (*array)[j];
                (*array)[j] = (*array)[j+1];
                (*array)[j+1] = temp;
            }
        }
    }
}

// поиск ближайшего по значению элемента массива
short FindClosest(short ** array, int size, short number)
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        short diff = abs((*array)[mid]) - abs(number);
        if(diff == 0)
        {
            return (*array)[mid];
        }
        if(diff < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    if(low == 0)
    {
        return (*array)[0];
    }
    if (low > 0 && abs((*array)[low] - number) < abs((*array)[low - 1] - number))
        return (*array)[low];
    else if (low > 0)
        return (*array)[low - 1];
    return 0;
}