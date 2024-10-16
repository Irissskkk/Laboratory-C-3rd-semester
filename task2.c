#include "library.c"

int main(int argc, char *argv[])
{
    // проверка введенных аргументов
    if (argc != 2)
    {
        printf("Invalid input\n");
        return INVALID_INPUT;
    }
    double epsilon;
    if (StrToDouble(argv[1], &epsilon) != VALID || epsilon <= 0)
    {
        printf("Incorrect epsilon\n");
        return INVALID_INPUT;
    }

    // массив решений
    double results[15];
    // решение через значения пределов
    results[0] = limit_e(epsilon);
    results[1] = limit_pi(epsilon);
    results[2] = limit_ln(epsilon);
    results[3] = limit_sqrt(epsilon);
    results[4] = limit_y(epsilon);
    // решение через сумму ряда
    results[5] = row_e(epsilon);
    results[6] = row_pi(epsilon);
    results[7] = row_ln(epsilon);
    results[8] = row_sqrt(epsilon);
    results[9] = row_y(epsilon);
    // решение специального уравнения
    results[10] = equation_e(epsilon);
    results[11] = equation_pi(epsilon);
    results[12] = equation_ln(epsilon);
    results[13] = equation_sqrt(epsilon);
    results[14] = equation_y(epsilon);

    // массив констант для обозначения решений
    char *constants[5] = {"e", "pi", "ln2", "sqrt2", "gamma"};
    // массив решений
    char *ways[3] = {"LIMITS", "ROWS", "EQUATIONS"};

    // точность вывода результата
    int precision = 0;// считает количество нулей после запятой в epsilon
    double temp = epsilon;
    while (temp != 1)
    {
        temp *= 10;
        ++precision;
    }
    int i;
    // решение с точностью precision
    printf("Solution with accuracy %.*f", precision, epsilon);
    for (i = 0; i < 15; i++)
    {
        if (i % 5 == 0)
        {
            printf("\n%c%s", '-', ways[i / 5]);
        }
        // вывод решения на экран
        printf("\nresult for %s:", constants[i % 5]);
        if (results[i] != INFINITY && !isnan(results[i]))
        {
            printf(" %.*f", precision, results[i]);
        }
        else
        {
            printf("Couldn't calculate constant with given accuracy");
        }
    }
    printf("\n");
    return 0;
}