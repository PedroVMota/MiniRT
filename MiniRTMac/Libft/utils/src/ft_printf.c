/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:35:02 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:35:03 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_detect(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	ft_format(va_list args, char c)
{
	int	res;

	res = 0;
	if (c == 'c')
		res += ft_print_char(va_arg(args, int));
	else if (c == 's')
		res += ft_print_str(va_arg(args, char *));
	else if (c == 'p')
		res += ft_print_ptr(va_arg(args, unsigned long long));
	else if (c == 'd' || c == 'i')
		res += ft_print_nbr(va_arg(args, int));
	else if (c == 'u')
		res += ft_print_unsigned(va_arg(args, unsigned long));
	else if (c == 'x')
		res += ft_print_hex(va_arg(args, int), c);
	else if (c == 'X')
		res += ft_print_hex(va_arg(args, int), c);
	else if (c == '%')
		res += ft_print_char('%');
	return (res);
}

int	ft_printf(const char *format, ...)
{
	int			size;
	int			index;
	va_list		args;

	va_start(args, format);
	index = 0;
	size = 0;
	while (format[index] != 0)
	{
		if (format[index] == '%' && ft_detect(format[++index]))
			size += ft_format(args, format[index]);
		else
		{
			ft_print_char(format[index]);
			size++;
		}
		index++;
	}
	return (size);
}
