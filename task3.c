#include <locale.h>
#include "library.c"

int main(int argc, char *argv[])
{
	// �������� ��������� ���������
    char *locale = setlocale(LC_ALL, "Russian_Russia.1251");

    if (argc < 4)
    {
        printf("Error: invalid input\n");
        return INVALID_INPUT;
    }

    if (!((argv[1][0] == '-' || argv[1][0] == '/') && argv[1][2] == '\0'))
    {
        printf("Error: invalid input");
        return INVALID_INPUT;
    }

    errno = 0;
    int i, j;
    
    switch (argv[1][1])
    {
   	// ������� ���������� ��������� A*x^2 + B*x + C = 0 �� ����� ���������� �������������� ������������� A, B � C
    case 'q':
        if (argc != 6)
        {
            printf("Error: invalid input\n");
            return INVALID_INPUT;
        }
        double epsilon_q, coefA, coefB, coefC;

        if (StrToDouble(argv[2], &epsilon_q) != VALID ||
            epsilon_q <= 0 ||
            StrToDouble(argv[3], &coefA) != VALID ||
            StrToDouble(argv[4], &coefB) != VALID ||
            StrToDouble(argv[5], &coefC) != VALID)
        {
            printf("Error: invalid input\n");
            return INVALID_INPUT;
        }

        int size_array = 3;
        int count_permutation = 0;
        // �������� ������ ��� ������ �� 3 ��������� double
        double *ArrayOfCoefficients = (double *)malloc(size_array * sizeof(double));
        if (ArrayOfCoefficients == NULL)
        {
            printf("Error: no memory is allocated\n");
            free(ArrayOfCoefficients);
            return INVALID_MEMORY;
        }
        // ���������� ������������ �������� � ������ ��� ���������� ������������
        ArrayOfCoefficients[0] = coefA;
        ArrayOfCoefficients[1] = coefB;
        ArrayOfCoefficients[2] = coefC;

		// ����������� ������ �� ����������� ����� �������� ������������ ��������
    	quickSortD(ArrayOfCoefficients, 0, size_array - 1);

    	do
    	{
    		// ������� �� ����� ������� ���������� �������������
        	PrintD(ArrayOfCoefficients, size_array);
        	double x1, x2;
        	// ������ ���������� ���������
        	int res = calculateSquareEquation(ArrayOfCoefficients[0], ArrayOfCoefficients[1], ArrayOfCoefficients[2], &x1, &x2);
        	switch (res)
        	{
        	case 0:
            	printf("Only one solution x = %lf\n", x1);
            	break;
        	case 1:
            	printf("Two solutions x1 = %f, x2 = %lf\n", x1, x2);
            	break;
        	case -1:
            	printf("No solution\n");
            	break;
        	default:
            	printf("Exceptional answer: %d\n", res);
        	}
    	}  
		// ����� ��������� ������� ������������ 3 ����� � ��������� �� ��������� ����� ����� epsilon_q
		while (NextSetD(ArrayOfCoefficients, size_array, epsilon_q));
    
        break;
    case 'm':
        if (argc != 4)
        {
            printf("Error: invalid input\n");
            return INVALID_INPUT;
        }
        long int num1, num2;
        if (StrToInt(argv[2], &num1, 10) != VALID ||
            StrToInt(argv[3], &num2, 10) != VALID ||
            num1 == 0 || num2 == 0)
        {
            printf("Error: too big or 0 number\n");
            return INVALID_INPUT;
        }
        if (num1 % num2 == 0)
        {
            printf("Number %ld div on %ld without lost\n", num1, num2);
        }
        else
        {
            printf("Number %ld DOESN'T div on %ld without lost\n", num1, num2);
        }
        break;

    case 't':
        if (argc != 6)
        {
            printf("Error: invalid input\n");
            return INVALID_INPUT;
        }
        double epsilon_t, side1, side2, side3;
        if (StrToDouble(argv[2], &epsilon_t) != VALID ||
            epsilon_t <= 0 ||
            StrToDouble(argv[3], &side1) != VALID ||
            StrToDouble(argv[4], &side2) != VALID ||
            StrToDouble(argv[5], &side3) != VALID)
        {
            printf("Error: invalid input\n");
            return INVALID_INPUT;
        }

        int result_t;
        // ���������� - ���������� �� ������������� ����������� �� ��������� side1, side2 � side3 � ��������� ��������� epsilon_t
        SolutionResult status_t = IsTriangleExists(epsilon_t, side1, side2, side3, &result_t);
        if (status_t == OVERFLOW_ERROR)
        {
            printf("Error: overflow\n");
            return OVERFLOW_ERROR;
        }
        else if (status_t == INVALID_INPUT)
        {
            printf("Error: invalid input\n");
            return INVALID_INPUT;
        }

        if (result_t == 1)
            printf("Sides %Lf %Lf %Lf form right triangle\n", side1, side2, side3);
        else
            printf("Sides %Lf %Lf %Lf DOESNT form right triangle\n", side1, side2, side3);

        break;

    default:
        printf("Error: flag is wrong: %s\n", argv[1]);
        return INVALID_INPUT;
    }
    return 0;
}
