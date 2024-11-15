#include "functions22.c"

int main()
{
    double result;
    switch (geometric_mean(&result, 5, 5.6, 2.4, 9.2, 5.5, 7.3))
    {
	    case INVALID_INPUT:
    	    printf("invalid_input\n");
       		return INVALID_INPUT;
        	break;
    
    	case OVERFLOW_ERROR:
        	printf("overflow error\n");
        	return OVERFLOW_ERROR;
        	break;
        
		case INVALID_MEMORY:
        	printf("invalid_memory\n");
        	return INVALID_MEMORY;
        	break;
        
    	case OK:
        	printf("Geometric mean: %f\n", result);
        	break;
    }

	double x = 2.0;
	int grad = 12;
    switch (int_pow(x, grad, &result))
    {
	    case INVALID_INPUT:
    	    printf("invalid_input\n");
        	return INVALID_INPUT;
        	break;
    
    	case OVERFLOW_ERROR:
            printf("overflow error\n");
            return OVERFLOW_ERROR;
            break;
        
		case INVALID_MEMORY:
        	printf("invalid_memory\n");
        	return INVALID_MEMORY;
        	break;
        
        case OK:
            printf("int pow %.0lf^%d: %.2lf\n", x, grad, result);
            break;
    }

    return OK;
}