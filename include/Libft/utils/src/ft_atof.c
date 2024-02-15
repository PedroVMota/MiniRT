/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 08:29:15 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 08:31:23 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	process_integer_part(char **str_ptr)
{
	double	result;
	char	*str;

	result = 0.0;
	str = *str_ptr;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	*str_ptr = str;
	return (result);
}

double	process_fractional_part(char **str_ptr)
{
	double	result;
	double	factor;
	char	*str;

	result = 0.0;
	factor = 0.1;
	str = *str_ptr;
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
	*str_ptr = str;
	return (result);
}

double	ft_atof(char *str)
{
	double	sign;
	double	integer_part;
	double	fractional_part;

	sign = 1.0;
	if (!str)
		return (0);
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	else if (*str == '+')
		str++;
	integer_part = process_integer_part(&str);
	fractional_part = process_fractional_part(&str);
	return (sign * (integer_part + fractional_part));
}
