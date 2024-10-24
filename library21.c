#include "library21.h"

int string_len(const char *str)
{
    size_t len = 0;
    while (*str != '\0')
    {
        len++;
        str++;
    }
    return len;
}

SolutionResult string_reverse(const char *str, char **result)
{
    int len = string_len(str);
	*result = (char*)malloc(len * sizeof(char));
    if (result == NULL)
    {
        return INVALID_MEMORY;
    }

	int i, j = 0;
	for (i = len; i > 0; i--)
	{
		(*result)[j++] = str[i-1];
	}
	(*result)[len] = '\0';
	return VALID;
}

SolutionResult odd_to_upper(const char *str, char **result)
{
    int len = string_len(str);
    *result = (char*)malloc(sizeof(char)*(len + 1));
    if (result == NULL)
    {
        return INVALID_MEMORY;
    }
    int i;
    for (i = 0; i < len; ++i)
    {
        if (i % 2 != 0 && str[i] >= 'a' && str[i] <= 'z')
        {
            (*result)[i] = str[i] - 32; // 'a' = 97, 'A' = 65, 97 - 65 = 32
        }
        else
        {
            (*result)[i] = str[i];
        }
    }
    (*result)[len] = '\0';
    return VALID;
}

SolutionResult change_string(const char *str, char **result)
{
    int len = string_len(str);
    *result = (char*)malloc(sizeof(char)*(len + 1));
    if (result == NULL)
    {
        return INVALID_MEMORY;
    }
    int index = 0;
    int i;
    for (i = 0; i < len; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            (*result)[index++] = str[i];
        }
    }
    for (i = 0; i < len; ++i)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            (*result)[index++] = str[i];
        }
    }
    for (i = 0; i < len; ++i)
    {
        if (!(str[i] >= '0' && str[i] <= '9') &&
            !(str[i] >= 'a' && str[i] <= 'z') &&
            !(str[i] >= 'A' && str[i] <= 'Z'))
        {
            (*result)[index++] = str[i];
        }
    }
    (*result)[index] = '\0';
    return VALID;
}

SolutionResult convert_str_to_int(const char *str, unsigned int * result, int base)
{
    char *endptr;
    *result = strtol(str, &endptr, base);

    if (errno == ERANGE && (*result == UINT_MAX || *result == 0))
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) {
        return INVALID_INPUT;
    } else if (*endptr != '\0') {
        return INVALID_INPUT;
    }

    return VALID;
}

SolutionResult concat_random(char **strs, int count_str, char **result, unsigned int seed)
{
    int i, len = 0, capacity = 0; // len для отслеживания текущей длины результ. строки, capacity для определения максимальной строки
    for (i = 0; i < count_str; ++i) // определяет максимальную длину строки
    {
        len = string_len(strs[i]);
        if (len > capacity) capacity = len;
    }
    capacity *= count_str; // расчет общей емкости: максимальная длина строки умножить на кол-во строк
    len = 0;
    (*result) = (char*)malloc(sizeof(char) * (capacity + 1));
    if((*result) == NULL)
    {
        return INVALID_MEMORY;
    }
    srand(seed); // инициализация генератора случайных чисел с переданным значением seed
    int rand_num; // генерируется случайное число
    for (i = 0; i < count_str; ++i)
    {
      do
      {
          rand_num = rand() % count_str;
      } while (strs[rand_num] == '\0');
      
     concat_string(strs[rand_num], result, &len); //пропускаем 3-ю строку по условию задачи
        strs[rand_num] = '\0'; // обнулить выбранную строку, чтобы она не повторялась
    }
    return VALID;
}

void concat_string(char * str, char ** result, int * len)
{
	int i;
    for(i = 0; str[i] != '\0'; ++i)
    {
        (*result)[(*len)++] = str[i];
    }
    (*result)[(*len)] = '\0';
}