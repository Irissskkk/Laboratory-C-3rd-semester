#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
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

SolutionResult StrToInt(const char *str, long int * result, int base) // преобразования строки в целое число
// функция преобразует строку в целое число
// в указанной системе счисления (int base)
{
    char *endptr; //указатель на символ (char *endptr), который используется для проверки, была ли вся входная строка успешно преобразована в число
    *result = strtol(str, &endptr, base); // функция использует стандартную функцию strtol для преобразования строки в число

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN)) // проверка на переполнение
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) { 
        return INVALID_INPUT;
    } else if (*endptr != '\0') { 
        return INVALID_INPUT;
    }

    return VALID;
}

// h функция вывести в консоль натуральные числа в пределах 100 включительно, кратные указанному
SolutionResult MultiplyNumbers(long int number, int** result, int* size_arr_res)
{
    if(number == 0) return INVALID_INPUT; // проверка входного значения

    int capacity = 4; // инициализация массива, начальный размер массива
    *result = (int*)malloc(capacity * sizeof(int)); //выделение памяти
    if (result == NULL) return INVALID_MEMORY;

	int i;
    for(i = 1; i <= 100; ++i) 
	{
        if (i % number == 0) //проверка, делится ли на number
		{
            (*result)[(*size_arr_res)++] = i; //увеличивается счетчик
            if (capacity == *size_arr_res) 
			{
                capacity *= 2;
                int *for_realloc = realloc(*result, capacity * sizeof(int)); //увеличение емкости массива
                if (for_realloc == NULL) {
                    return INVALID_MEMORY;
                }
                *result = for_realloc;
            }
        }
    }
    return VALID;
}

// p функция проверяет - простое ли число n
bool isPrime(int n)
{
    if (n > 1)
    {
    	int i;
        // в цикле перебираются числа 2 до n - 1 
        for (i = 2; i < n; i++)
            if (n % i == 0) // если n делится без остатка на i - возвращаем false (число не простое)
                return false;

        // если программа дошла до данного оператора, то возвращаем true (число простое) - проверка пройдена
        return true;
    }
    else  
        return false;
}

//s разделить число x на отдельные цифры сс с основанием 16 и вывести отдельно каждую цифру
//принимает строку, представляющую шестнадцатеричное число, и преобразует его в десятичное целое число
int HexToInt(char* hexadecimalnumber)
{
	int decimalNumber = 0; //хранит результат в десятичной системе
	
	// хранение цифр шестнадцатеричного числа в одном массиве
    char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', 
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }; 
    // объявление переменных
	// используется для учета позиции цифры при переводе
    int i, j, power = 0, digit; 
  
    // преобразование шестнадцатеричного числа в эквивалентное десятичное число
	// проходит по строке, начиная с последнего символа
    for (i = strlen(hexadecimalnumber) - 1; i >= 0; i--) { 
  
        // поиск, присутствует ли данный входной символ в массиве или нет 
		// если он присутствует в массиве, то 
		// найдем эквивалентное десятичное число для каждой шестнадцатеричной цифры
		// ищет индекс текущего символа в hexDigits
        for (j = 0; j < 16; j++) { 
            if (hexadecimalnumber[i] == hexDigits[j]) { 
                decimalNumber += j * pow(16, power); // если символ найден, к decimalNumber добавляется значение (индекс символа) умноженное на 16^power
 				//(поскольку каждая позиция в шестнадцатеричной системе увеличивается в 16 раз).
            } 
        } 
        power++; 
    }
    return decimalNumber; //после завершения циклов возвращается итоговое десятичное число
}

int digitCount(int x) // функция возвращает количество цифр в десятичном числе
{
	return floor(log10(abs(x))) + 1;
}

char* IntToHex(int decimalnumber) //функция принимает десятичное число и возвращает его строковое представление в шестнадцатеричной системе
{
	char *res = (char *)malloc(sizeof(char) * digitCount(decimalnumber));
	int i = 0;
	int n = decimalnumber;
	char c;
	while(n > 0) // выполняет деление на 16 для получения остатка, который соответствует разряду шестнадцатеричного числа
	{
  		int x = n%16;
  		n /= 16;
  		res[i] = x < 10 ? x+'0' : x-10 + 'A';
  		i++;
	}
	res[i] = '\0';
	i--;
	int j = 0;
	//поменять начало и конец символов
	while(j < i)
	{
		c = res[j];
		res[j] = res[i];
		res[i] = c;
		i--;
		j++;
	}
	return res; // возвращается указатель на строку, представляющую шестнадцатеричное число
}

// s перевести число в шестнадцатиричное и разделить на символы
// целое число, которое нужно преобразовать в шестнадцатеричное представление
// указатель на указатель, который будет содержать адрес полученной строки с шестнадцатеричным представлением
// указатель на целочисленную переменную, в которую мы можем записать размер результата
SolutionResult SplitNumberToHexDigits(long int number, char** res, int* arr_size)
{
	*res = IntToHex(number);
    if (*res == NULL) return INVALID_MEMORY;
	
    (*arr_size)++; // увеличение размера массива
    return VALID;
}

// e сделать таблицу степеней числа
SolutionResult DegreesTable(long int*** res, long int number)
{

    *res = (long int **) malloc(11 * sizeof(long int*));// выделение памяти
    if((*res) == NULL) return INVALID_MEMORY; // проверка ошибок выделения памяти
	int i; // выделение памяти для строк таблицы
    for (i = 0; i <= 10; ++i)
    {
        (*res)[i] = (long int *) malloc((number + 1) * sizeof(long int));

        if((*res)[i] == NULL) //проверка ошибок выделения памяти для строк
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

    (*res)[0][0] = 1; //инициализация таблицы, инициализация верхнего левого элемента

    for(i = 0; i < 11; ++i) //инициализация первогои второго столбцов
    {
        (*res)[i][0] = 1; //инициализирует первый элемент ряда значением 1
        (*res)[i][1] = i; //инициализирует второй элемент ряда значением индекса ряда i
    }

    for(i = 2; i <= number; ++i) //инициализация остальной части таблицы
    {
        (*res)[0][i] = 0; //инициализирует элемент в строке 0 и столбце i значением 0
        (*res)[2][i] = 1; //инициализирует элемент в строке 2 и столбце i значением 1
    }

	int base; //вычисление значений таблицы
    for(base = 0; base <= 10; ++base)//цикл будет выполняться 11 раз, при этом переменная base будет принимать значения от 0 до 10
    {
    	int degree;
        for(degree = 2; degree <= number; ++degree)//переменная degree будет принимать значения от 2 до number
        {
            (*res)[base][degree] = (*res)[base][degree - 1] * base;//элемент таблицы res в строке base и столбце degree. Формула берет предыдущее значение в этом столбце ((*res)[base][degree - 1]) и умножает его на значение base
        }
    }

    return VALID;
}

//a сумма натурального числа
SolutionResult NumbersSumma(long int number, long long int * res)
{
    int flag = 1;
    if (number < 0)
    {
        number = labs(number);
        flag = -1;
    }
    int i; 
    for (i = 1; i <= number; ++i)
    {
        if(*res > INT_MAX - i || *res < INT_MIN + i) return INVALID_MEMORY; // проверка на переполнение

        *res += i;
    }
    *res = *res * flag; // после вычисления суммы функция умножает результат *res на флаг flag, чтобы учесть знак числа number
    return VALID;
}

//f факториал натурального числа
SolutionResult Factorial(long int number, unsigned long long int* res)
{
    *res = 1;
    long int i;
    for(i = 2; i <= number; ++i) // начинает с 2, потому что факториал 0 и 1 равен 1
    {
        if(*res > ULLONG_MAX / i) return INVALID_MEMORY;
        *res *= i;
    }
    return VALID;
}

int main(int argc, char* argv[]) 
{
	char *locale = setlocale(LC_ALL, "Russian_Russia.1251");
	
    // функция проверяет количество параметров (argc) и аргументов (argv) командной строк
    if (argc != 3) // если количество параметров не равно 3, функция выводит сообщение об ошибке и завершается
    {
        printf("Run the program with the key for help\n");
    }
    else
    {
    	// аргумент командной строки X 
    	long int number = 0;
    	if(StrToInt(argv[2], &number, 10) != VALID) // берет второй аргумент (argv[2]) и пытается преобразовать его в целое число (long int) с помощью функции StrToInt
    	{
        	printf("Error: Invalid number format entered\n");
        	return INVALID_INPUT;
    	}
    	
    	//переменная цикла
		//функция берет первый аргумент (argv[1]) и обрабатывает его как ключ
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
            		if(result_h != NULL) free(result_h);
            		return INVALID_MEMORY;
        		}
        		else if (status_h == INVALID_INPUT)
        		{
            		printf("Error: division by zero\n");// деление на ноль
            		if(result_h != NULL) free(result_h);
            		return INVALID_INPUT;
        		}

        		if(size_arr_result_h == 0) // если ошибок нет, функция проверяет размер массива result_h, если размер массива равен 0, функция выводит сообщение 
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
        		if(result_h != NULL) free(result_h);

	    		break;
	    	}

			// определить является ли число x простым или составным
	    	case 'p':
	    	{
				if (number != 1)
				{
	    			if (isPrime(number))
		    			printf("The number %ld is prime\n", number);
	    			else
		    			printf("The number %ld is composite (not prime)\n", number);
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
	    		if(number > 10 || number < 0)
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
        		if(result_e != NULL) free(result_e);
	    		
	    		break;
	    	}
			// вычислить сумму всех натуральных чисел от 1 до x
	    	case 'a':
	    	{
	    		long long int result_a = 0;
        		if (NumbersSumma(number, &result_a) == INVALID_MEMORY)
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
	    		if(number < 0)
        		{
            		printf("Error: only positive numbers\n");
            		return INVALID_INPUT;
        		}

        		unsigned long long int result_f = 1;
        		if(Factorial(number, &result_f) == INVALID_MEMORY)
        		{
            		printf("Error: An overflow occurred\n"); //переполнение
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
