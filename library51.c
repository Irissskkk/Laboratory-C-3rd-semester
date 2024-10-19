#include "library_headers5.h"


SolutionResult StrToDouble(const char *str, long double *result)
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
void taylor_a(long double x, long double epsilon, long double * result)
{
    int n = 0;//для отслеживаия номера текущего члена ряда
    *result = 0;
    long double element = 1.0;//хранение текущего значения члена ряда
    while(fabs(element) > epsilon)
    {
        *result += element;
        n++;
        element *= (x/(n+1.0)); //element = xⁿ / n! формула для n-го члена ряда Тейлора
    }
}
// сумма ряда чисел (-1)^n*x^2n / (2n)!
void taylor_b(long double x, long double epsilon, long double* result)
{
    int n = 0;
    *result = 0;
    long double element = 1;
    while(fabs(element) > epsilon)
    {
        *result += element;
        n++;
        element *= (((-1.0) * x * x) / ((2.0 * n + 2.0) * (2.0 * n + 1.0))); // включает фактор (-1)^n и деление на факториалы, что здесь реализовано через умножение 
    }
}
// сумма ряда чисел 3^3n*(n!)^3*x^2n / (3n)!
void taylor_c(long double x, long double epsilon, long double* result)
{
    long double pr = 1, cur = pr;
    int n = 0;
    *result = 1;
    do
    {
        pr = cur;
        cur = (pr * (27.0*(n+1.0)*(n+1.0)*(n+1.0)*x*x))/((3.0*n+3.0)*(3.0*n+2.0)*(3.0*n+1.0));
        ++n;
        (*result) += cur;
    } while (fabs(pr-cur)>epsilon);
}
// сумма ряда чисел (-1)^n*(2n-1)!!*x^2n / (2n)!!
void taylor_d(long double x, long double epsilon, long double* result)
{
    int n = 1;
    *result = 0;
    long double pr = ((-1.0) * x * x) * 0.5, cur = pr;
    do
    {
        pr = cur;
        cur = pr * ((x*x*(-1.0)*(2.0*n+1.0))/(2.0*n+2.0));
        ++n;
        (*result) += cur;
    } while (fabs(pr-cur)>epsilon);
    
}