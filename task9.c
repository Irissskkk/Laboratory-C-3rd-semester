#include "library9.c"
#include <unistd.h>

int main(int argc, char* argv[])
{
    switch (argc)
    {
        case 3:
        {
            long int start, stop;
            if(StrToInt(argv[1], &start, 10) != VALID ||
                StrToInt(argv[2], &stop, 10) != VALID ||
                start > stop)
            {
                printf("Error: invalid input\n");
                return INVALID_INPUT;
            }
            long int* result_array = NULL;
            int size_of_array = 20;
            if(GenerateArray(start, stop, &result_array, size_of_array) != VALID)
            {
                printf("Error: memory error \n"); //Ошибка работы с памятью
                free(result_array);
                return INVALID_MEMORY;
            }
            printf("Input array:\n"); // исходный массив
            int i;
            for(i = 0; i < size_of_array; ++i)
            {
                printf("%ld ", result_array[i]);
            }
            printf("\n");
            SwapMinMaxArray(&result_array, size_of_array);
            printf("Result array:\n"); // получившийся массив
            for(i = 0; i < size_of_array; ++i)
            {
                printf("%ld ", result_array[i]);
            }
            printf("\n");
            free(result_array);
        }
            break;
        case 1:
            srand(time(NULL));
            int size_of_array_a = rand() % (100 + 1 - 10) + 10;
            //printf("%d\n", size_of_array_a);
            int size_of_array_b = rand() % (100 + 1 - 10) + 10;
            //printf("%d\n", size_of_array_b);
            short * array_a = NULL;
            short * array_b = NULL;
            short * array_c = NULL;
            srand(time(NULL));
            SolutionResult res1 = GenerateArrayTask2(-1000, 1000, &array_a, size_of_array_a);
            printf("Array a\n");
            int i;
            for (i = 0; i < size_of_array_a; ++i)
            {
                printf("%d ", array_a[i]);
            }
			printf("\n\n");
			
            SolutionResult res2 = GenerateArrayTask2(-990, 990, &array_b, size_of_array_b);
            printf("Array b\n");
            for (i = 0; i < size_of_array_b; ++i)
            {
                printf("%d ", array_b[i]);
            }
			printf("\n");
            
            if(res1 != VALID || res2 != VALID)
            {
                printf("Error: memory error 2\n"); //Ошибка работы с памятью
                free(array_a);
                free(array_b);
                return INVALID_MEMORY;
            }

            if(GenerateArrayOfClosestValues(&array_a, size_of_array_a, &array_b, size_of_array_b, &array_c) != VALID)
            {
                printf("Error: memory error 3\n"); //Ошибка работы с памятью
                free(array_a);
                free(array_b);
                free(array_c);
                return INVALID_MEMORY;
            }

            printf("\nResult array c\n");
            for (i = 0; i < size_of_array_a; ++i)
            {
                printf("%d ", array_c[i]);
            }
            free(array_a);
            free(array_b);
            free(array_c);
            printf("\n\n");
            break;
        default:
            printf("Error: invalid input\n");
            return INVALID_INPUT;
    }
    return 0;
}