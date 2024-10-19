#include "functions10.c"

int main()
{
    int base;
    if(!scanf("%d", &base) ||  base > 36 || base < 2)
    {
        printf("Error: incorrect number system\n"); 
        return INVALID_INPUT;
    }
    
    char* end_of_input = "Stop";
    char * array_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    char * input_number_array = NULL;
    input_number_array = malloc(sizeof(char) * 101);
    if(input_number_array == NULL)
    {
        printf("Error: memory processing eroor\n"); 
        return INVALID_MEMORY;
    }

    long long int result_number = 0;
    long long int input_number = 0;
    int flag_stop = 0; //0 - ложь, 1 - истина
    while(scanf("%100s", input_number_array))
    {
    	//сравниваем очередную строку с признаком окончания Stop
        if(strcmp(input_number_array, end_of_input) == 0)
        {
        	//проверить - было ли введено хотя бы одно число
            if(flag_stop)
            {
                char * result_number_array = NULL;
                //массив систем счисления 9, 18, 27 и 36
                int * base_array_for_print = (int*)malloc(5 * sizeof(int));
                if(base_array_for_print == NULL)
                {
                    printf("Error: memory processing eroor\n"); // Ошибка: ошибка работы с памятью
                    return INVALID_MEMORY;
                }
                base_array_for_print[0] = base;
                base_array_for_print[1] = 9;
                base_array_for_print[2] = 18;
                base_array_for_print[3] = 27;
                base_array_for_print[4] = 36;
				
				int i;
                for(i = 0; i < 5; ++i)
                {
                	//преобразуем найденное максимальное число в разные системы счисления 9, 18, 27 и 36 и выведем на экран
                    if(ConvertToBase(&result_number_array, result_number, base_array_for_print[i], array_base) != VALID)
                    {
                        printf("Error: memory processing eroor\n");
                        free(input_number_array);
                        free(result_number_array);
                        free(base_array_for_print);
                        return INVALID_MEMORY;
                    }
                    printf("Number system %2d, value: %s\n", base_array_for_print[i], result_number_array);
                    free(result_number_array);
                    result_number_array = NULL;
                }
                free(base_array_for_print);
            }
            break;

        }
        //проверим введенное число s
        if(CheckNumberValidation(input_number_array, base) == INVALID_INPUT)
        {
            printf("Error: invalid data %s\n", input_number_array); 
            free(input_number_array);
            return INVALID_INPUT;
        }
        //преобразуем строку в число
        if(StrTollint(input_number_array, &input_number, base) == INVALID_INPUT)
        {
            printf("Error: invalid data %s\n", input_number_array); 
            free(input_number_array);
            return INVALID_INPUT;
        }
		//сравним введенное число с максимальным и если оно больше - сохраним его
        if(llabs(input_number) - llabs(result_number) > 0)
        {
            result_number = input_number;
        }

        flag_stop = 1;
    }

    free(input_number_array);

    return 0;
}