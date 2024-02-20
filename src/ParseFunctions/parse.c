/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:13:29 by pedro             #+#    #+#             */
/*   Updated: 2024/02/20 11:26:02 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

char	**getpropreties(char **line)
{
	int		i;
	char	*trim;

	i = -1;
	trim = ft_strtrim(*line, " ");
	while ((trim)[++i])
		if (((trim)[i]) == ' ' || ((trim)[i]) == '\t')
			(trim)[i] = ' ';
	(gscene())->props = ft_split((trim), ' ');
	i = -1;
	while ((gscene())->props[++i])
	{
		if ((gscene())->props[i][0] == '\n')
		{
			free((gscene())->props[i]);
			(gscene())->props[i] = NULL;
		}
	}
	free(trim);
	free(*line);
	*line = NULL;
	return ((gscene())->props);
}

static bool	checkskip(char *line)
{
	if (ft_strnstr(line, "#", ft_strlen(line)) || line[0] == '\n'
		|| line[0] == '\0')
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	fetchdata(int fd)
{
	char	*line;
	bool	isok;

	(gscene())->props = NULL;
	isok = true;
	line = NULL;
	while (isok)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (checkskip(line))
			continue ;
		if (!getpropreties(&line) && !(gscene())->props)
			return (uptadeerror("Error getting properties\n"), false);
		if (generateobject((gscene())->props) == false)
			return (uptadeerror("Error generating object\n"), false);
		if ((gscene())->error)
			isok = false;
	}
	free(line);
	return (isok);
}

bool	parse(char *f)
{
	int		file;
	char	*extention;

	if (!f || (ft_strnstr(f, ".rt", ft_strlen(f)) == NULL))
		return (uptadeerror("Invalid file extention\n"), false);
	extention = ft_strnstr(f, ".rt", ft_strlen(f));
	if (ft_strlen(extention) != 3)
		return (uptadeerror("Invalid file extention\n"), false);
	file = open(f, O_RDONLY);
	if (file < 0)
		return (uptadeerror("Error opening file\n"), false);
	if (!fetchdata(file))
		return (uptadeerror("Error fetching data\n"), close(file), false);
	close(file);
	return (true);
}
