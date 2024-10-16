#include "library_headers.h"

// прочитать из файла и поместить в массив
SolutionResult ReadInputFromFile(FILE ** input, char** buff, int* len)
{
    *len = 0;
    char symbol = fgetc(*input);
    while (symbol == ' ' || symbol == '\t' || symbol == '\n')
    {
        symbol = fgetc(*input);
    }
    while (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != EOF)
    {
        (*buff)[(*len)++] = symbol;
        if(*len == 102)
        {
            return INVALID_INPUT;
        }
        symbol = fgetc(*input);
    }
    (*buff)[(*len)] = '\0';
    return VALID;
}

// символы преобразованы в строчные
void ConvertToLowercase(char** array, int len)
{
	int i;
    for(i = 0; i < len; ++i)
    {
        if(isalpha((*array)[i]))
        {
            (*array)[i] = (char)tolower((*array)[i]);
        }
    }
}

// символы преобразованы в эквивалентные им ASCII-коды, записанные в системе счисления с основанием 4
void ConvertToLowercaseBase4(char** array, int len, short ** result)
{
    short number_base4 = 0;
    int i;
    for(i = 0; i < len; ++i)
    {
        if(isalpha((*array)[i]))
        {
            (*array)[i] = (char)tolower((*array)[i]);
        }
        int temp_num = (int)(*array)[i];
        int base10 = 1;
        while(temp_num > 0)
        {
            number_base4 += (temp_num % 4) * base10;
            base10 *= 10;
            temp_num /= 4;
        }
        (*result)[i] = number_base4;
        number_base4 = 0;
    }
}

// символы преобразованы в эквивалентные им ASCII-коды, записанные в системе счисления с основанием 8
void ConvertToAsciiBase8(char** array, int len, short ** result)
{
    short number_base8 = 0;
    int i;
    for(i = 0; i < len; ++i)
    {
        short temp_num = (short)(*array)[i];
        int base10 = 1;
        while(temp_num > 0)
        {
            number_base8 += (temp_num % 8) * base10;
            base10 *= 10;
            temp_num /= 8;
        }
        (*result)[i] = number_base8;
        number_base8 = 0;
    }
}