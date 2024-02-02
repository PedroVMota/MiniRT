/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:34:58 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:34:59 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	index;
	int	len;

	len = 0;
	index = 0;
	if (str == NULL)
	{
		len += ft_print_str("(null)");
	}
	else
	{
		while (str[index] != 0)
		{
			ft_print_char(str[index]);
			len++;
			index++;
		}
	}
	return (len);
}
