#include "library21.c"

int main(int argc, char *argv[])
{
    if (argc < 3 || argv[1][0] != '-')
    {
        printf("invalid_input\n");
        return INVALID_INPUT;
    }
    
    switch (argv[1][1])
    {
    case 'l':
        if (argc != 3)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        int len = string_len(argv[2]);
        printf("Length of string '%s': %d\n", argv[2], len);
        break;
    case 'r':
        if (argc != 3)
        {
            printf("invalid_input\n");
            return INVALID_INPUT;
        }
        char *r_result;
        if (string_reverse(argv[2], &r_result) != VALID) 
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("Reverse string of '%s': %s\n", argv[2], r_result);
        free(r_result);
        break;
    case 'u':
        if (argc != 3)
        {
            printf("invalid input\n");
            return INVALID_INPUT;
        }
        char *u_result;
        if (odd_to_upper(argv[2], &u_result) != VALID)
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("Odd upper string of '%s': %s\n", argv[2], u_result);
        free(u_result);
        break;
    case 'n':
        if (argc != 3)
        {
            printf("invalid_input\n");
            return INVALID_INPUT;
        }
        char *n_result;
        if (change_string(argv[2], &n_result) != VALID)
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("Processed string of '%s': %s\n", argv[2], n_result);
        free(n_result);
        break;
    case 'c':
		{
		char *c_result;
        
        int seed = atoi(argv[2]);
        int kol = argc - 3;
        char *strings[kol];
        
        len = 0;
        int i;
        for (i = 0; i < kol; i++)
        {
        	strings[i] = argv[i+3];
        }
        
        if (concat_random(&strings, kol, &c_result, seed) != VALID)
        {
            printf("incorrect memory allocation\n");
            return INVALID_MEMORY;
        }
        printf("Concat strings: %s\n", c_result);
        free(c_result);
		}
        break;
    default:
        printf("invalid_flag\n");
        break;
    }
    return VALID;
}