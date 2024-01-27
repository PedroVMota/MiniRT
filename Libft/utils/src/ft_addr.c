/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:33:32 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:34:10 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_len(intptr_t addr)
{
	int	len;

	len = 0;
	while (addr != 0)
	{
		len++;
		addr = addr / 16;
	}
	return (len);
}

void	ft_show_addr(intptr_t addr)
{
	if (addr >= 16)
	{
		ft_show_addr(addr / 16);
		ft_show_addr(addr % 16);
	}
	else
	{
		if (addr <= 9)
			ft_putchar_fd((addr + '0'), 1);
		else
			ft_putchar_fd((addr - 10 + 'a'), 1);
	}
}

int	ft_print_ptr(unsigned long long ptr_addr)
{
	int	len;

	len = 0;
	if (ptr_addr == 0)
	{
		len += ft_printf("(nil)");
		return (len);
	}
	else
	{
		len += write(1, "0x", 2);
		ft_show_addr(ptr_addr);
		len += ft_get_len(ptr_addr);
	}
	return (len);
}
