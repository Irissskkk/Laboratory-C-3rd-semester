#include <stdio.h>
#include <stdlib.h>

enum errors
{
    OK,
    INVALID_INPUT,
    INVALID_MEMORY,
};

int sum(int num1, int num2)
{
    int res = 0, carry = 0;
    res = num1 ^ num2;
    carry = (num1 & num2) << 1;
    while (carry)
    {
        int tmp = res;
        res = res ^ carry;
        carry = (tmp & carry) << 1;
    }
    return res;
}


int negative(int n)
{
    return sum(~n, 1);
}

int subtraction(int a, int b)
{
    return sum(a, negative(b));
}

enum errors ten_into_n(long int num, int r, char** res, int * capacity, int * count, char * base) {
    *count = 0;
    int mask, digit;

    do {
        if (*count >= *capacity)
        {
            *capacity <<= 1;
            char * for_realloc = (char*)realloc(*res, *capacity * sizeof(char));
            if (for_realloc == NULL)
            {
                return INVALID_MEMORY;
            }
            *res = for_realloc;
        }

        mask = subtraction((1 << r), 1);
        digit = num & mask; // крайний разряд числа num
        char sim = base[digit];
        (*res)[*count] = sim;
        *count = sum(*count, 1);

        num >>= r;
    } while (num > 0);

    return OK;
}

void print_num(int flag, char * res, int count)
{
    printf("Result: ");
    if(flag == 1) printf("-");

    for (int i = count - 1; i >= 0; i--)
    {
        printf("%c", res[i]);
    }
    printf("\n");
}

int main() {
    char* base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int capacity = 1;
    char* result = (char*)malloc(sizeof(char) * capacity);
    if (result == NULL)
    {
        printf("Error");
        return INVALID_MEMORY;
    }

    long int num;
    int r;
    int count;

    printf("Enter decimal number and base: ");
    if (scanf("%ld%d", &num, &r) != 2 || r < 1 || r > 5)
    {
        printf("Error");
        free(result);
        return INVALID_INPUT;
    }

    int flag_negative = 0;
    if(num < 0)
    {
        num = negative(num);
        flag_negative = 1;
    }

    if(ten_into_n(num, r, &result, &capacity, &count, base) != OK)
    {
        printf("Error");
        free(result);
        result = NULL;
        return INVALID_INPUT;
    }

    print_num(flag_negative, result, count);

    free(result);

    return 0;
} 