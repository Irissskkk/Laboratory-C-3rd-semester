#include "library.c"

int main(int argc, char* argv[])
{
    // у программы должно быть 2 аргумента: x и epsilon
    if(argc != 3)
    {
        printf("Error: invalid input\n");
        return INVALID_INPUT;
    }

    double x;
    double epsilon;

    // проверка аргументов на валидность
    if (StrToDouble(argv[1], &x) != VALID ||
        StrToDouble(argv[2], &epsilon) != VALID ||
        epsilon <= 0)
    {
        printf("Error: incorrect input\n");
        return INVALID_INPUT;
    }

    double result_a = 0, result_b, result_c, result_d;

    // сумма ряда чисел x^n / n!
    taylor_a(x, epsilon, &result_a);
    printf("A: %lf\n", result_a);

    // сумма ряда чисел (-1)^n*x^2n / (2n)!
    taylor_b(x, epsilon, &result_b);
    printf("B: %lf\n", result_b);

    if(fabs(x) < 1)
    {
        // сумма ряда чисел 3^3n*(n!)^3*x^2n / (3n)!
        taylor_c(x, epsilon, &result_c);
        printf("C: %lf\n", result_c);

        // сумма ряда чисел (-1)^n*(2n-1)!!*x^2n / (2n)!!
        taylor_d(x, epsilon, &result_d);
        printf("D: %lf\n", result_d);
    }
    else
    {
        printf("x must be between -1 and 1\n");
    }

    return 0;
}