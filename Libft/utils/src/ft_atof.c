#include <libft.h>

double ft_atof(char *str)
{

    double result = 0.0;
    double sign = 1.0;
    double factor = 0.1;

    if(!str)
        return 0;
    while (*str == ' ')
        str++;
    if (*str == '-')
    {
        sign = -1.0;
        str++;
    } else if (*str == '+')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10.0 + (*str - '0');
        str++;
    }
    if (*str == '.')
    {
        str++;
        while (*str >= '0' && *str <= '9')
        {
            result += factor * (*str - '0');
            factor /= 10.0;
            str++;
        }
    }
    return sign * result;
}