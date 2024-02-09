#include <libft.h>

double ft_atof(char *str)
{

    double result = 0.0;
    double sign = 1.0;
    double factor = 0.1;

    // Skip leading white spaces
    while (*str == ' ') {
        str++;
    }

    // Check for sign
    if (*str == '-') {
        sign = -1.0;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Convert integer part
    while (*str >= '0' && *str <= '9') {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    // Convert fractional part
    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            result += factor * (*str - '0');
            factor /= 10.0;
            str++;
        }
    }

    return sign * result;
}