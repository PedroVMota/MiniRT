/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:13:29 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 11:25:45 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

char	**getpropreties(char **line)
{
	int		i;

	i = -1;
	while ((*line)[++i])
		if (((*line)[i]) == ' ' || ((*line)[i]) == '\t')
			(*line)[i] = ' ';
	g_scene->props = ft_split((*line), ' ');
	free(*line);
	*line = NULL;
	return (g_scene->props);
}

bool	fetchdata(int fd)
{
	char	*line;
	bool	isok;

	g_scene->props = NULL;
	isok = true;
	line = NULL;
	while (isok)
	{
		free(line);
		delprops(&g_scene->props);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strnstr(line, "#", ft_strlen(line)) || line[0] == '\n'
			|| line[0] == '\0')
			continue ;
		if (!getpropreties(&line) && !g_scene->props)
			return (uptadeerror("Error getting properties"), false);
		if (generateobject(g_scene->props) == false)
			return (uptadeerror("Error generating object"), false);
		if (g_scene->error)
			isok = false;
	}
	free(line);
	return (isok);
}

bool	parse(char *f)
{
	int	file;

	if (!f || (ft_strnstr(f, ".rt", ft_strlen(f)) == NULL))
		return (uptadeerror("Error file extension\n"), false);
	file = open(f, O_RDONLY);
	if (file < 0)
		return (uptadeerror("Error opening file\n"), false);
	if (!fetchdata(file))
		return (uptadeerror("Error fetching data\n"), close(file), false);
	close(file);
	return (true);
}
