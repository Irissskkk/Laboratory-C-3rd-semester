#include "library.c"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Error: incorrect input\n");
        return INVALID_INPUT;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if(input == NULL || output == NULL)
    {
        printf("Error: file not found\n");
        if(input != NULL) fclose(input);
        if(output != NULL) fclose(output);
        return ERROR_OPEN_FILE;
    }

    int capacity = 2;
    char * buffer = (char *)malloc(capacity * sizeof(char));
    if(buffer == NULL)
    {
        printf("Error: no memory is allocated\n");
        return INVALID_MEMORY;
    }

    int len = 0;
    int min_base = 2;

    while (!feof(input))
    {
        SolutionResult err = ReadInputFromFile(&input, &buffer, &len, &min_base, &capacity);
        if(err == INVALID_INPUT)
        {
            if(input != NULL) fclose(input);
            if(output != NULL) fclose(output);
            free(buffer);
            printf("Error: incorrect input\n");
            return INVALID_INPUT;
        }
        else if(err == INVALID_MEMORY)
        {
            free(buffer);
            printf("Error: no memory is allocated\n");
            fclose(input);
            fclose(output);
            return INVALID_MEMORY;
        }
        if(len > 0)
        {
            long long int number_base10 = 0;
            if (StrTollint(buffer, &number_base10, min_base) != VALID)
            {
                if (input != NULL) fclose(input);
                if (output != NULL) fclose(output);
                free(buffer);
                return INVALID_INPUT;
            }
            fprintf(output, "input number: %s\n", buffer);
            fprintf(output, "minimal base: %d\n", min_base);
            fprintf(output, "decimal number: %lld\n", number_base10);
            fprintf(output, "\n");
        }
    }

    printf("Task is done\n");

    if (input != NULL) fclose(input);
    if (output != NULL) fclose(output);
    free(buffer);

    return 0;
}

