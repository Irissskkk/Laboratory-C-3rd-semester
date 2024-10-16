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

SolutionResult StrToInt(const char *str, long int * result, int base) // �������������� ������ � ����� �����
// ������� ����������� ������ � ����� �����
// � ��������� ������� ��������� (int base)
{
    char *endptr; //��������� �� ������ (char *endptr), ������� ������������ ��� ��������, ���� �� ��� ������� ������ ������� ������������� � �����
    *result = strtol(str, &endptr, base); // ������� ���������� ����������� ������� strtol ��� �������������� ������ � �����

    if (errno == ERANGE && (*result == LONG_MAX || *result == LONG_MIN)) // �������� �� ������������
    {
        return INVALID_INPUT;
    } else if (errno != 0 && *result == 0) { 
        return INVALID_INPUT;
    } else if (*endptr != '\0') { 
        return INVALID_INPUT;
    }

    return VALID;
}

// h ������� ������� � ������� ����������� ����� � �������� 100 ������������, ������� ����������
SolutionResult MultiplyNumbers(long int number, int** result, int* size_arr_res)
{
    if(number == 0) return INVALID_INPUT; // �������� �������� ��������

    int capacity = 4; // ������������� �������, ��������� ������ �������
    *result = (int*)malloc(capacity * sizeof(int)); //��������� ������
    if (result == NULL) return INVALID_MEMORY;

	int i;
    for(i = 1; i <= 100; ++i) 
	{
        if (i % number == 0) //��������, ������� �� �� number
		{
            (*result)[(*size_arr_res)++] = i; //������������� �������
            if (capacity == *size_arr_res) 
			{
                capacity *= 2;
                int *for_realloc = realloc(*result, capacity * sizeof(int)); //���������� ������� �������
                if (for_realloc == NULL) {
                    return INVALID_MEMORY;
                }
                *result = for_realloc;
            }
        }
    }
    return VALID;
}

// p ������� ��������� - ������� �� ����� n
bool isPrime(int n)
{
    if (n > 1)
    {
    	int i;
        // � ����� ������������ ����� 2 �� n - 1 
        for (i = 2; i < n; i++)
            if (n % i == 0) // ���� n ������� ��� ������� �� i - ���������� false (����� �� �������)
                return false;

        // ���� ��������� ����� �� ������� ���������, �� ���������� true (����� �������) - �������� ��������
        return true;
    }
    else  
        return false;
}

//s ��������� ����� x �� ��������� ����� �� � ���������� 16 � ������� �������� ������ �����
//��������� ������, �������������� ����������������� �����, � ����������� ��� � ���������� ����� �����
int HexToInt(char* hexadecimalnumber)
{
	int decimalNumber = 0; //������ ��������� � ���������� �������
	
	// �������� ���� ������������������ ����� � ����� �������
    char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', 
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }; 
    // ���������� ����������
	// ������������ ��� ����� ������� ����� ��� ��������
    int i, j, power = 0, digit; 
  
    // �������������� ������������������ ����� � ������������� ���������� �����
	// �������� �� ������, ������� � ���������� �������
    for (i = strlen(hexadecimalnumber) - 1; i >= 0; i--) { 
  
        // �����, ������������ �� ������ ������� ������ � ������� ��� ��� 
		// ���� �� ������������ � �������, �� 
		// ������ ������������� ���������� ����� ��� ������ ����������������� �����
		// ���� ������ �������� ������� � hexDigits
        for (j = 0; j < 16; j++) { 
            if (hexadecimalnumber[i] == hexDigits[j]) { 
                decimalNumber += j * pow(16, power); // ���� ������ ������, � decimalNumber ����������� �������� (������ �������) ���������� �� 16^power
 				//(��������� ������ ������� � ����������������� ������� ������������� � 16 ���).
            } 
        } 
        power++; 
    }
    return decimalNumber; //����� ���������� ������ ������������ �������� ���������� �����
}

int digitCount(int x) // ������� ���������� ���������� ���� � ���������� �����
{
	return floor(log10(abs(x))) + 1;
}

char* IntToHex(int decimalnumber) //������� ��������� ���������� ����� � ���������� ��� ��������� ������������� � ����������������� �������
{
	char *res = (char *)malloc(sizeof(char) * digitCount(decimalnumber));
	int i = 0;
	int n = decimalnumber;
	char c;
	while(n > 0) // ��������� ������� �� 16 ��� ��������� �������, ������� ������������� ������� ������������������ �����
	{
  		int x = n%16;
  		n /= 16;
  		res[i] = x < 10 ? x+'0' : x-10 + 'A';
  		i++;
	}
	res[i] = '\0';
	i--;
	int j = 0;
	//�������� ������ � ����� ��������
	while(j < i)
	{
		c = res[j];
		res[j] = res[i];
		res[i] = c;
		i--;
		j++;
	}
	return res; // ������������ ��������� �� ������, �������������� ����������������� �����
}

// s ��������� ����� � ����������������� � ��������� �� �������
// ����� �����, ������� ����� ������������� � ����������������� �������������
// ��������� �� ���������, ������� ����� ��������� ����� ���������� ������ � ����������������� ��������������
// ��������� �� ������������� ����������, � ������� �� ����� �������� ������ ����������
SolutionResult SplitNumberToHexDigits(long int number, char** res, int* arr_size)
{
	*res = IntToHex(number);
    if (*res == NULL) return INVALID_MEMORY;
	
    (*arr_size)++; // ���������� ������� �������
    return VALID;
}

// e ������� ������� �������� �����
SolutionResult DegreesTable(long int*** res, long int number)
{

    *res = (long int **) malloc(11 * sizeof(long int*));// ��������� ������
    if((*res) == NULL) return INVALID_MEMORY; // �������� ������ ��������� ������
	int i; // ��������� ������ ��� ����� �������
    for (i = 0; i <= 10; ++i)
    {
        (*res)[i] = (long int *) malloc((number + 1) * sizeof(long int));

        if((*res)[i] == NULL) //�������� ������ ��������� ������ ��� �����
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

    (*res)[0][0] = 1; //������������� �������, ������������� �������� ������ ��������

    for(i = 0; i < 11; ++i) //������������� �������� ������� ��������
    {
        (*res)[i][0] = 1; //�������������� ������ ������� ���� ��������� 1
        (*res)[i][1] = i; //�������������� ������ ������� ���� ��������� ������� ���� i
    }

    for(i = 2; i <= number; ++i) //������������� ��������� ����� �������
    {
        (*res)[0][i] = 0; //�������������� ������� � ������ 0 � ������� i ��������� 0
        (*res)[2][i] = 1; //�������������� ������� � ������ 2 � ������� i ��������� 1
    }

	int base; //���������� �������� �������
    for(base = 0; base <= 10; ++base)//���� ����� ����������� 11 ���, ��� ���� ���������� base ����� ��������� �������� �� 0 �� 10
    {
    	int degree;
        for(degree = 2; degree <= number; ++degree)//���������� degree ����� ��������� �������� �� 2 �� number
        {
            (*res)[base][degree] = (*res)[base][degree - 1] * base;//������� ������� res � ������ base � ������� degree. ������� ����� ���������� �������� � ���� ������� ((*res)[base][degree - 1]) � �������� ��� �� �������� base
        }
    }

    return VALID;
}

//a ����� ������������ �����
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
        if(*res > INT_MAX - i || *res < INT_MIN + i) return INVALID_MEMORY; // �������� �� ������������

        *res += i;
    }
    *res = *res * flag; // ����� ���������� ����� ������� �������� ��������� *res �� ���� flag, ����� ������ ���� ����� number
    return VALID;
}

//f ��������� ������������ �����
SolutionResult Factorial(long int number, unsigned long long int* res)
{
    *res = 1;
    long int i;
    for(i = 2; i <= number; ++i) // �������� � 2, ������ ��� ��������� 0 � 1 ����� 1
    {
        if(*res > ULLONG_MAX / i) return INVALID_MEMORY;
        *res *= i;
    }
    return VALID;
}

int main(int argc, char* argv[]) 
{
	char *locale = setlocale(LC_ALL, "Russian_Russia.1251");
	
    // ������� ��������� ���������� ���������� (argc) � ���������� (argv) ��������� �����
    if (argc != 3) // ���� ���������� ���������� �� ����� 3, ������� ������� ��������� �� ������ � �����������
    {
        printf("Run the program with the key for help\n");
    }
    else
    {
    	// �������� ��������� ������ X 
    	long int number = 0;
    	if(StrToInt(argv[2], &number, 10) != VALID) // ����� ������ �������� (argv[2]) � �������� ������������� ��� � ����� ����� (long int) � ������� ������� StrToInt
    	{
        	printf("Error: Invalid number format entered\n");
        	return INVALID_INPUT;
    	}
    	
    	//���������� �����
		//������� ����� ������ �������� (argv[1]) � ������������ ��� ��� ����
		int i;
    	switch (argv[1][1])
    	{
			//������� � ������� ����������� ����� � �������� 100 ������������, ������� x
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
            		printf("Error: division by zero\n");// ������� �� ����
            		if(result_h != NULL) free(result_h);
            		return INVALID_INPUT;
        		}

        		if(size_arr_result_h == 0) // ���� ������ ���, ������� ��������� ������ ������� result_h, ���� ������ ������� ����� 0, ������� ������� ��������� 
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

			// ���������� �������� �� ����� x ������� ��� ���������
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
			// ��������� ����� x �� ��������� ����� ������� ��������� � ���������� 16 � ������� �������� ������ �����
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
			
			// ������� ������� �������� (��� ���� ����������� � ��������� �� 1 �� x) ��������� �� 1 �� 10
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
			// ��������� ����� ���� ����������� ����� �� 1 �� x
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
			//��������� ��������� x
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
            		printf("Error: An overflow occurred\n"); //������������
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
