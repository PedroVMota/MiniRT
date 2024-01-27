/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:34:55 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:34:56 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long long	i;
	char		*d_dst;
	char		*s_src;

	i = 0;
	d_dst = (char *)dst;
	s_src = (char *)src;
	if (d_dst == s_src)
		return (dst);
	if (d_dst > s_src)
	{
		while (len--)
			d_dst[len] = s_src[len];
	}
	else
	{
		while (i < len)
		{
			d_dst[i] = s_src[i];
			i++;
		}
	}
	return (dst);
}
