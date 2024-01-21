/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 18:35:46 by pedro             #+#    #+#             */
/*   Updated: 2023/12/02 18:35:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	all[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*ret;
	int			trigger;

	trigger = 0;
	ret = NULL;
	if (fd < 0 || fd > FOPEN_MAX || !BUFFER_SIZE)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (ft_null_content(all[fd]));
	while (all[fd][0] || read(fd, all[fd], BUFFER_SIZE) > 0)
	{
		ret = ft_backup(ret, all[fd]);
		static_manager(all[fd], &trigger);
		if (trigger)
			break ;
	}
	return (ret);
}
