#include "library.c"

int main(int argc, char * argv[])
{
	// должно быть 4 или 5 аргументов
    if(argc != 5 && argc != 4)
    {
        printf("Error: incorrect input\n");
        return INVALID_INPUT;
    }
    // первым символом аргумента-флага должен быть - или /
    if( !((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0') ) {
        printf("Error: incorrect input\n");
        return INVALID_INPUT;
    }

    switch (argv[1][1])
    {
        case 'r':
        	// проверяем аргументы программы
            if(argc != 5)
            {
                printf("Error: incorrect input\n");
                return INVALID_INPUT;
            }
            // открыть входные файлы 
            FILE * input1 = fopen(argv[2], "r"); // открыть 1-й входной файл
            FILE * input2 = fopen(argv[3], "r"); // открыть 2-й входной файл
            FILE * output_r = fopen(argv[4], "w"); // открыть файл для записи результата
            if(input1 == NULL || input2 == NULL || output_r == NULL)
            {
                printf("Error: file not found\n");
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output_r != NULL) fclose(output_r);
                return ERROR_OPEN_FILE;
            }
            // буфер для чтения строки файла
            char * buff;
            buff = (char *)malloc(101 * sizeof(char));
            if(buff == NULL)
            {
                printf("Error: no memory is allocated\n");
                if(input1 != NULL) fclose(input1);
                if(input2 != NULL) fclose(input2);
                if(output_r != NULL) fclose(output_r);
                return INVALID_MEMORY;
            }

			// цикл по содержимому файлов 1 и 2
            int len_r = 0;
            while (!feof(input1) || !feof(input2))
            {
            	// на нечетной позиции лексема файла1
            	// читать строку файла и записать в буфер
                if(!feof(input1) && ReadInputFromFile(&input1, &buff, &len_r) != VALID)
                {
                    printf("Error: lexema is too long\n");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output_r != NULL) fclose(output_r);
                    free(buff);
                    return INVALID_INPUT;
                }
                // записать содержимое буфера в выходной файл
                if(len_r > 0) fprintf(output_r, "%s ", buff);
                len_r = 0;
                
				// на четной позиции лексема файла2
				// читать строку файла и записать в буфер
                if(!feof(input2) && ReadInputFromFile(&input2, &buff, &len_r) != VALID)
                {
                    printf("Error: lexema is too long\n");
                    if(input1 != NULL) fclose(input1);
                    if(input2 != NULL) fclose(input2);
                    if(output_r != NULL) fclose(output_r);
                    free(buff);
                    return INVALID_INPUT;
                }
                // записать содержимое буфера в выходной файл
                if(len_r > 0) fprintf(output_r, "%s ", buff);
                len_r = 0;
            }
            
            printf("Task is done\n");
            // закрыть все файлы
            if(input1 != NULL) fclose(input1);
            if(input2 != NULL) fclose(input2);
            if(output_r != NULL) fclose(output_r);
            free(buff);
            break;
        case 'a':
            if(argc != 4)
            {
                printf("Error: incorrect input\n");
                return INVALID_INPUT;
            }
            FILE * input = fopen(argv[2], "r");
            FILE * output_a = fopen(argv[3], "w");
            char * buffer;
            short * result;
            buffer = (char *)malloc(101 * sizeof(char));
            result = (short *)malloc(100 * sizeof(short));

            if(buffer == NULL || result == NULL)
            {
                printf("Error: file not found\n");
                if(input != NULL) fclose(input);
                if(output_a != NULL) fclose(output_a);
                free(buffer);
                free(result);
                return INVALID_MEMORY;
            }
            int len = 0;
            int count_token = 0;
            while(!feof(input))
            {
            	// читать строку файла и записать в буфер
                if(ReadInputFromFile(&input, &buffer, &len) != VALID)
                {
                    printf("Error: lexema is too long\n");
                    if(input != NULL) fclose(input);
                    if(output_a != NULL) fclose(output_a);
                    free(result);
                    free(buffer);
                    return INVALID_INPUT;
                }
                count_token++;
                // в каждой десятой лексеме символы преобразованы в эквивалентные им ASCII-коды, записанные в системе счисления с основанием 4
                if(len > 0 && count_token % 10 == 0)
                {
                    ConvertToLowercaseBase4(&buffer, len, &result);
                    int i;
                    for(i = 0; i < len; ++i)
                    {
                        fprintf(output_a, "'%d'", result[i]);
                    }
                    fprintf(output_a, " ");
                }
                else if (len > 0 && count_token % 2 == 0)
                {
                    ConvertToLowercase(&buffer, len);
                    fprintf(output_a, "%s ", buffer);
                }
                else if (len > 0 && count_token % 5 == 0)
                {
                    ConvertToAsciiBase8(&buffer, len, &result);
                    int i;
                    for(i = 0; i < len; ++i)
                    {
                        fprintf(output_a, "'%d'", result[i]);
                    }
                    fprintf(output_a, " ");
                }
                else
                {
                    fprintf(output_a, "%s ", buffer);
                }
            }
            printf("Task is done\n");
            if(input != NULL) fclose(input);
            if(output_a != NULL) fclose(output_a);
            free(result);
            free(buffer);
            break;
        default:
            printf("Error: flag isn't correct: %s\n", argv[1]);
            return INVALID_INPUT;
    }
    return 0;
}