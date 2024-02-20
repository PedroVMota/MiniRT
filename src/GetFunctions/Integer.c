/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:31:55 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/20 12:07:45 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool intrequire(char *s, int start, int end)
{
    int i = start;
    
    // Handle leading '+' or '-' signs
    if (s[i] == '+' || s[i] == '-')
        i++;
    
    // Check if the remaining characters are digits
    while (i <= end && s[i] && s[i] != '\n') {
        printf("[%c]\n", s[i]);
        if (s[i] < '0' || s[i] > '9')
            return true;  // Non-digit character found
        i++;
    }
    
    return false;  // All characters are valid digits
}

int newint(char *s, int max, int min)
{
    long value;

    if(intrequire(s, 0, ft_strlen(s) - 1))
        return (uptadeerror("Invalid integer value\n"), 0);
    value = ft_atoi(s);
    if(value < min || value > max)
        return (uptadeerror("Invalid integer out of range\n"), 0);
    return value;
}

int getint(char *s, bool require, int max, int min)
{
    if((gscene()->error))
        return 0;
    if(require)
    {
        if(!s)
            return (uptadeerror("Field required!\n"), 0);
        return newint(s, max, min);
    }
    if(s)
        return newint(s, max, min);
    return 0;
}