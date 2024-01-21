/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:35:35 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:35:36 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Allocates (with malloc(3)) and returns a “fresh” substring from the string
**	given as argument. The substring begins at indexstart and is of size len.
**	If start and len aren’t refering to a valid substring,
**	the behavior is undefined.
**	If the allocation fails, the function returns NULL.
*/

int	ft_custom_len(char const *s, unsigned int start, unsigned long int len)
{
	unsigned long int	i;

	i = 0;
	s += start;
	while (*s++ && i < len)
		i++;
	return (i);
}

char	*ft_error_return(void)
{
	char	*error_res;

	error_res = (char *)malloc((sizeof(char) * 1));
	if (!error_res)
		return (0);
	error_res[0] = '\0';
	return (error_res);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	unsigned long int	i;
	unsigned long int	l_len;
	int					alocation_size;
	char				*substr;

	i = 0;
	l_len = (unsigned long int)len;
	if (start > (unsigned int)ft_strlen(s))
		return (ft_error_return());
	alocation_size = ft_custom_len(s, start, l_len);
	substr = (char *)malloc((sizeof(char) * alocation_size) + 1);
	if (!substr)
		return (0);
	s += start;
	while (*s && i < l_len)
	{
		substr[i] = *s++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
