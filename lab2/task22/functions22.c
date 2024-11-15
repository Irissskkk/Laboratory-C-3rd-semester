#include "functions22.h"

status is_overflow(double x)
{
    if (isnan(x) || isinf(x))
        return OVERFLOW_ERROR;
    return OK;
}

status geometric_mean(double *res, int count, ...)
{
    if (count < 1)
        return INVALID_INPUT;
    
    va_list args;
    va_start(args, count);
    *res = 1;
    double cur;
    int i;
    for (i = 0; i < count; ++i)
    {
        cur = va_arg(args, double);
        if (cur < 0)
            return INVALID_INPUT;
        *res *= cur;
        if (is_overflow(*res))
        {
            va_end(args);
            return OVERFLOW_ERROR;
        }
    }
    *res = pow(*res, (double)1.0/ count);
    va_end(args);
    return OK;
}

status int_pow(double base, int degree, double *res)
{
    status state = OK;
    if (degree < 0)
        return int_pow(1.0 / base, -degree, res);
    
    else if (!degree)
    {
        *res = 1.0;
        state = OK;
    }
    else if (degree & 1)
    {
        state = int_pow(base, degree - 1, res);
        *res *= base;
        return is_overflow(*res);
    }
    else
    {
        state = int_pow(base, degree / 2, res);
        *res *= *res;
        return is_overflow(*res);
    }
    return state;
}
