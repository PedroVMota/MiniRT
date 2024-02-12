/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseFunctions.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:33:27 by pedro             #+#    #+#             */
/*   Updated: 2024/02/10 17:12:11 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

char	**getpropreties(char **line)
{
	char	**props;
	int		i;

	i = -1;
	props = NULL;
	while ((*line)[++i])
		if (((*line)[i]) == ' ' || ((*line)[i]) == '\t')
			(*line)[i] = ' ';
	props = ft_split((*line), ' ');
	return (props);
}

bool	fetchdata(int fd)
{
	char	*line;
	char	**props;

	line = NULL;
	while (true)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strnstr(line, "#", ft_strlen(line)) || line[0] == '\n'
			|| line[0] == '\0')
			continue ;
		props = getpropreties(&line);
		if (!props)
			return (updateError("Error getting properties"), false);
		if (generateobject(props) == false)
			return (updateError("Error generating object"), false);
		if (g_scene->error)
			return (false);
	}
	return (true);
}

bool	parse(char *f)
{
	int	file;

	if (!f || (ft_strnstr(f, ".rt", ft_strlen(f)) == NULL))
		return (updateError("Error file extension"), false);
	file = open(f, O_RDONLY);
	if (file < 0)
		return (updateError("Error opening file"), false);
	if (!fetchdata(file))
		return (updateError("Error fetching data"), close(file), false);
	close(file);
	return (true);
}
