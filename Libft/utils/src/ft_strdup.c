/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:35:20 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:35:21 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*dup_str;
	int		i;
	int		len;

	i = -1;
	len = ft_strlen((char *)str);
	dup_str = (char *)malloc((len + 1) * sizeof(char));
	if (!dup_str)
		return (0);
	while (str[++i])
		dup_str[i] = str[i];
	dup_str[i] = 0;
	return (dup_str);
}
