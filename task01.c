#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

typedef enum 
{
    VALID, 
    INVALID_MEMORY, 
    INVALID_INPUT 
} SolutionResult;

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

//h функция вывести в консоль натуральные числа в пределах 100 включительно, кратные указанному
SolutionResult MultiplyNumbers(long int number, int **result, int *size_arr_res)
{
    if (number == 0) 
	{
		return INVALID_INPUT; 
	}

    int capacity = 4;
    *result = (int*)malloc(capacity * sizeof(int)); 
    if (result == NULL) 
	{
		return INVALID_MEMORY;
	}

	int i;
    for(i = 1; i <= 100; ++i) 
	{
        if (i % number == 0)
		{
            (*result)[(*size_arr_res)++] = i; 
    
        }
    }
    return VALID;
}

// p функция проверяет - простое ли число n
bool isPrime(int n)
{
    if (abs(n) > 1)
    {
    	int i;
        for (i = 2; i < abs(n); i++)
            if (abs(n) % i == 0) 
                return false;

        return true;
    }
    else  
        return false;
}

//s разделить число x на отдельные цифры сс с основанием 16 и вывести отдельно каждую цифру
int HexToInt(char* hexadecimalnumber)
{
	int decimalNumber = 0; 
	
    char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', 
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }; 
    
    int i, j, power = 0; //индекс для обхода строки, индекс для обхода массива hexDigits, степень 16 для текущего символа
  
	// проходит по строке, начиная с последнего символа
    for (i = strlen(hexadecimalnumber) - 1; i >= 0; i--) { 
  
        for (j = 0; j < 16; j++) { 
            if (hexadecimalnumber[i] == hexDigits[j]) { 
                decimalNumber += j * pow(16, power); // если символ найден, к decimalNumber добавляется значение (индекс символа) умноженное на 16^power
            } 
        } 
        power++; 
    }
    return decimalNumber; 
}

int digitCount(int x) //функция возвращает количество цифр в десятичном числе
{
	return floor(log10(abs(x))) + 1;
}

char *IntToHex(int decimalnumber) 
{
	char *res = (char *)malloc(sizeof(char) * (digitCount(decimalnumber)+1));
	int i = 0;
	int n = abs(decimalnumber);
	if (decimalnumber<0) res[i++] = '-';
	char c;
	while(n > 0) // выполняет деление на 16 для получения остатка, который соответствует разряду шестнадцатеричного числа
	{
  		int x = n % 16;
  		n /= 16;
  		res[i] = x < 10 ? x + '0' : x - 10 + 'A';
  		i++;
	}
	res[i] = '\0';
	i--;
	int j = 1;
	// поменять начало и конец символов
	while(j < i)
	{
		c = res[j];
		res[j] = res[i];
		res[i] = c;
		i--;
		j++;
	}
	
	return res; 
}

// s перевести число в шестнадцатиричное и разделить на символы
SolutionResult SplitNumberToHexDigits(long int number, char** res, int* arr_size)
{
	*res = IntToHex(number);
    if (*res == NULL) 
	{
		return INVALID_MEMORY;
	}
    (*arr_size)++; 
    return VALID;
}

// e сделать таблицу степеней числа
SolutionResult DegreesTable(long int*** res, long int number)
{

    *res = (long int **)malloc(11 * sizeof(long int*));
    if ((*res) == NULL) 
	{
		return INVALID_MEMORY; 
	}

	int i; // индекс для перебора строк массива
    for (i = 0; i <= 10; ++i)
    {
        (*res)[i] = (long int *)malloc((number + 1) * sizeof(long int));

        if((*res)[i] == NULL) 
        {
        	int j;
            for(j = 0; j < i; ++j)
            {
                free((*res)[j]);
            }
            free(*res);
            return INVALID_MEMORY;
        }
    }

    (*res)[0][0] = 1; 

    for(i = 0; i < 11; ++i) //инициализация первого и второго столбцов
    {
        (*res)[i][0] = 1; 
        (*res)[i][1] = i; 
    }

    for(i = 2; i <= number; ++i) //инициализация остальной части таблицы
    {
        (*res)[0][i] = 0; 
        (*res)[2][i] = 1; //инициализирует элемент в строке 2 и столбце i значением 1
    }

	int base; //вычисление значений таблицы
    for(base = 0; base <= 10; ++base)
    {
    	int degree;
        for(degree = 2; degree <= number; ++degree)
        {
            (*res)[base][degree] = (*res)[base][degree - 1] * base; //Формула берет предыдущее значение в этом столбце ((*res)[base][degree - 1]) и умножает его на значение base
        }
    }

    return VALID;
}

//a сумма натурального числа
SolutionResult NumbersSumma(long int number, long long int * res)
{
    if (number < 1)
    {
        return INVALID_INPUT;
    }
	(*res)= ((1 + number)*number)/2;
    return VALID;
}

//f факториал натурального числа
SolutionResult Factorial(long int number, unsigned long long int* res)
{
    *res = 1;
    long int i;
    for(i = 2; i <= number; ++i) 
    {
        if(*res > ULLONG_MAX / i) return INVALID_MEMORY;
        *res *= i;
    }
    return VALID;
}

int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        printf("invalid input\n");
    }
    else
    {
    	// аргумент командной строки X 
    	long int number = 0;
    	if(StrToInt(argv[2], &number, 10) != VALID) 
    	{
        	printf("Error: Invalid number format entered\n");
        	return INVALID_INPUT;
    	}
    	
    	
		int i;
    	switch (argv[1][1])
    	{
			//вывести в консоль натуральные числа в пределах 100 включительно, кратные x
	    	case 'h':
	    	{
	    		
	    		int* result_h = NULL;
        		int size_arr_result_h = 0;
        		SolutionResult status_h = MultiplyNumbers(number, &result_h, &size_arr_result_h);

        		if (status_h == INVALID_MEMORY)
        		{
            		printf("Error: Memory error\n");
            		if(result_h != NULL) 
					{
						free(result_h);
					}
            		return INVALID_MEMORY;
        		}
        		else if (status_h == INVALID_INPUT)
        		{
            		printf("Error: division by zero\n"); // деление на ноль
            		return INVALID_INPUT;
        		}

        		if(size_arr_result_h == 0) 
        		{
            		printf("There are no such numbers\n");
        		}
        		else
        		{
            		printf("Array of numbers:\n");
            		for(i = 0; i < size_arr_result_h; ++i)
            		{
                		printf("%d ", result_h[i]);
            		}
            		printf("\n");
        		}
        		if(result_h != NULL) 
				{
					free(result_h);
				}
	    		break;
	    	}

			// определить является ли число x простым или составным
	    	case 'p':
	    	{
				if (number != 1 && number != 0)
				{
	    			if (isPrime(number))
		    			printf("The number %ld is prime\n", number);
	    			else
		    			printf("The number %ld is compound (not prime)\n", number);
				}
				else 
				{
					printf("Number %ld is not simple not compound \n", number);
				}
	    		
	    		break;
	    	}
			// разделить число x на отдельные цифры системы счисления с основанием 16 и вывести отдельно каждую цифру
	    	case 's':
	    	{
				int arr_size = (number == 0) ? 1 : log10l(labs(number));
        		char* res_s = NULL;
        		SolutionResult status_s = SplitNumberToHexDigits(number, &res_s, &arr_size);
        		if(status_s == INVALID_MEMORY)
        		{
            		printf("Error: Memory error\n");
            		if(res_s != NULL) free(res_s);
            		return INVALID_MEMORY;
        		}
	    		printf("Hexadecimal representation of a number %ld:\n", number);
        		for(i = 0; i < arr_size; ++i)
        		{
            		printf("%c ", res_s[i]);
        		}
        		printf("\n");
        		if (res_s != NULL)
        		{
		        	free(res_s);
		        }
	    		
	    		break;
	    	}
			
			// вывести таблицу степеней (для всех показателей в диапозоне от 1 до x) оснований от 1 до 10
	    	case 'e':
	    	{
	    		if (number > 10 || number < 0)
        		{
            		printf("Error: invalid number\n");
            		return INVALID_INPUT;
        		}

        		long int** result_e = NULL;
        		if (DegreesTable(&result_e, number) == INVALID_MEMORY)
        		{
            		printf("Error: Memory error\n");
            		return INVALID_MEMORY;
        		}

        		for(i = 0; i <= 10; i++)
        		{
        			int j;
            		for(j = 0; j <= number; ++j)
            		{
                		printf("%d^%d = %ld\n", i, j, result_e[i][j]);
            		}
            		printf("\n");
        		}

        		for(i = 0; i <= 10; ++i) if(result_e[i] != NULL) free(result_e[i]);
        		if (result_e != NULL)
				{ 
					free(result_e);
				}
	    		break;
	    	}
			// вычислить сумму всех натуральных чисел от 1 до x
	    	case 'a':
	    	{
	    		long long int result_a = 0;
				SolutionResult res = NumbersSumma(number, &result_a);
        		if (res == INVALID_INPUT)
        		{
            		printf("Error: invalid input\n");
            		return INVALID_MEMORY;
        		}
        		if (res == INVALID_MEMORY)
        		{
            		printf("Error: An overflow occurred\n");
            		return INVALID_MEMORY;
        		}
        		printf("Sum of numbers from 1 to %ld: ", number);
        		printf("%lld\n", result_a);
	    		
	    		break;
	    	}
			//вычислить факториал x
	    	case 'f':
	    	{
	    		if (number < 0)
        		{
            		printf("Error: only positive numbers\n");
            		return INVALID_INPUT;
        		}

        		unsigned long long int result_f = 1;
        		if(Factorial(number, &result_f) == INVALID_MEMORY)
        		{
            		printf("Error: An overflow occurred\n"); 
            		return INVALID_MEMORY;
        		}
        		printf("Factorial of a number %ld: ", number);
        		printf("%llu\n", result_f);
        		
        		break;
	    	}
	    }
    }
    
	
	return 0;
}
