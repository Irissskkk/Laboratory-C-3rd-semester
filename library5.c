#include "library_headers.h"

// перевод строки в вещественное число
SolutionResult StrToDouble(const char *str, double *result)
{
    char *endptr;
    *result = strtold(str, &endptr);
    if (errno == ERANGE && (*result == HUGE_VALL || *result == -HUGE_VALL))
    {
        return INVALID_INPUT;
    }
    else if (errno == ERANGE && *result == 0)
    {
        return INVALID_INPUT;
    }
    else if (*endptr != '\0')
    {
        return INVALID_INPUT;
    }
    return VALID;
}
// сумма ряда чисел x^n / n!
void taylor_a(double x, double epsilon, double * result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        n++;
        element *= x/n;
    }
}
// сумма ряда чисел (-1)^n*x^2n / (2n)!
void taylor_b(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        n++;
        element *= (-1.0 * x * x) / (2 * n * (2 * n - 1.0));
    }
}
// сумма ряда чисел 3^3n*(n!)^3*x^2n / (3n)!
void taylor_c(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        n++;
		element *= (9.0 * n * n * x * x) / (9.0 * n * n - 9.0 * n + 2.0);
    }
}
// сумма ряда чисел (-1)^n*(2n-1)!!*x^2n / (2n)!!
void taylor_d(double x, double epsilon, double* result)
{
    int n = 0;
    *result = 0;
    double element = -1.0 * x * x / 2.0;
    while(fabs(element) > epsilon)
    {
        *result += element;
        ++n;
        element *= (-1.0 * x * x * (2.0 * n - 1)) / (2.0 * n);
    }
}