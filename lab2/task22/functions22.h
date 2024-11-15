#ifndef _LIBRARY_HEADERS22_H
#define _LIBRARY_HEADERS22_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <float.h>

typedef enum Status
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
    OVERFLOW_ERROR
} status;

status int_pow(double base, int degree, double *res);
status geometric_mean(double *res, int count, ...);
status check_overflow(double number);

#endif