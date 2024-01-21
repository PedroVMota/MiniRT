/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:35:47 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:35:49 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}

char	*ft_null_content(char *static_buffer)
{
	int	i;

	i = -1;
	while (static_buffer[++i])
		static_buffer[i] = 0;
	return (NULL);
}

char	*ft_backup(char *line, char *old)
{
	int		i1;
	int		i2;
	int		len2;
	int		len1;
	char	*new_line;

	i1 = 0;
	i2 = 0;
	len1 = ft_gnl_strlen(line);
	len2 = ft_gnl_strlen(old);
	new_line = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_line)
		return (NULL);
	while (line && line[i1])
	{
		new_line[i1] = line[i1];
		i1++;
	}
	while (old && i2 < len2)
		new_line[i1++] = old[i2++];
	new_line[i1] = 0;
	if (line)
		free(line);
	return (new_line);
}

void	static_manager(char *static_buffer, int *flag)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (static_buffer[i])
	{
		if (*flag)
			static_buffer[i2++] = static_buffer[i];
		if (static_buffer[i] == '\n')
			*flag = 1;
		static_buffer[i++] = 0;
	}
}
