#include "libft.h"

int my_isspace(char ch)
{
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r');
}

double ft_atof(const char *str)
{
    double result = 0.0;
    double power = 1.0;
    int sign = 1;

    // Skip leading whitespaces
    while (my_isspace(*str)) {
        str++;
    }

    // Handle sign
    if (*str == '-' || *str == '+') {
        sign = (*str++ == '-') ? -1 : 1;
    }

    // Parse digits before the decimal point
    while (ft_isdigit(*str)) {
        result = result * 10.0 + (*str++ - '0');
    }

    // Handle decimal point and digits after it
    if (*str == '.') {
        str++;
        while (ft_isdigit(*str)) {
            result = result * 10.0 + (*str++ - '0');
            power *= 10.0;
        }
    }

    // Apply sign and scale
    return sign * result / power;
}