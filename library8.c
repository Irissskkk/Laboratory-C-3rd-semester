#include "library_headers.h"

// прочитать содержимое файла и отправить в буфер
SolutionResult ReadInputFromFile(FILE ** input, char** buff, int* len, int* min_base, int * capacity)
{
    *len = 0;
    *min_base = 2;
    char symbol = fgetc(*input);
    int flag_negative = 0;
    int flag_skip = 0;
    while (symbol == ' ' || symbol == '\t' || symbol == '\n')
    {
        symbol = fgetc(*input);
    }
    while (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != EOF)
    {
        if(symbol == '-' && *len == 0)
        {
            (*buff)[(*len)++] = symbol;
            flag_negative = 1;
        }
        else if ( (symbol == '0' && *len == 0) || (symbol == '0' && *len == 1 && flag_negative == 1) )
        {
            symbol = fgetc(*input);
            flag_skip = 1;
            continue;
        }
        else if(isdigit(symbol))
        {
            (*buff)[(*len)++] = symbol;
            if( symbol - '0' + 1 > *min_base)
            {
                *min_base = symbol - '0' + 1;
            }
        }
        else if(isalpha(symbol))
        {
            (*buff)[(*len)++] = (char)toupper(symbol);
            if(toupper(symbol) - 'A' + 10 + 1 > *min_base)
            {
                *min_base = toupper(symbol) - 'A' + 10 + 1;
            }
        }
        else
        {
            return INVALID_INPUT;
        }
        if(*len == *capacity)
        {
            *capacity *= 2;
            char * for_realloc = (char *) realloc(*buff, *capacity);
            if(for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            *buff = for_realloc;
        }
        if(*min_base > 36)
        {
            return INVALID_INPUT;
        }
        symbol = fgetc(*input);
    }
    if(*len == 0 && flag_skip && flag_negative == 0) (*buff)[(*len)++] = '0';
    if(*len == 1 && flag_skip && flag_negative) (*buff)[(*len)++] = '0';
    (*buff)[(*len)] = '\0';
    return VALID;
}

// преобразует строку в длинное длинное число
// base — основание преобразуемого числа.
// Если base находится в диапазоне от 2 до 36, оно используется как основание числа. 
// Если base равно нулю, число считается десятичным, 
// если только преобразованное число не начинается с O (для восьмеричной системы), Ox (для шестнадцатеричной) или OX (для шестнадцатеричной)
SolutionResult StrTollint(const char *str, long long int * result, int base)
{
    char *endptr;
    *result = strtoll(str, &endptr, base);

    if (errno == ERANGE && (*result == LLONG_MAX || *result == LLONG_MIN))
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return VALID;
}


