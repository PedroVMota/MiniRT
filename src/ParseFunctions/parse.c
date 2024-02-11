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

#include <StandarLibrarys.h>

bool distributeobject(int type, char **props);

bool	err(char *msg, int exit_code)
{
	if (msg)
		printf("%s%s%s\n", RED, msg, RESET);
	exit(exit_code);
}

void	printprops(char **line, char *name, const char *funcname)
{
	int	i;

	i = 0;
	printf("%s\"%s%s%s\"%s :", BLU, YEL, funcname, BLU, RESET);
	printf("%s{%s\n", MAG, RESET);
	while (line[i])
	{
		printf("\t%s\"%s%s%s[%d]%s\"%s: %s\"%s%s%s\"%s\n", BLU, RESET, MAG, name, i, BLU, RESET, BLU, YEL, line[i], BLU, RESET);
		i++;
	}
	printf("%s}%s\n", MAG, RESET);
}

void	delprops(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

char **getpropreties(char **line)
{
	
	char **props;
	int i;

	i = -1;
	while((*line)[++i])
	{
		if((*line)[i] == ' ' || (*line)[i] == '\t')
			(*line)[i] = ' ';
	}
	props = ft_split((*line), ' ');
	return (props);
}


bool generateobject(char **props)
{
	int type;

	type = UNKNOWN;
	if (ft_strncmp(props[0], "sp", 6) == 0)
		type = SPHERE;
	else if (ft_strncmp(props[0], "pl", 5) == 0)
		type = PLANE;
	else if (ft_strncmp(props[0], "C", 6) == 0)
		type = CAMERA;
	else if (ft_strncmp(props[0], "L", 5) == 0)
		type = POINT;
	else if (ft_strncmp(props[0], "A", 7) == 0)
		type = AMBIENT;
	else if (ft_strncmp(props[0], "D", 12) == 0)
		type = DIRECTIONAL;
	else if (ft_strncmp(props[0], "cy", 8) == 0)
		type = CYLINDER;
	else if (ft_strncmp(props[0], "py", 7) == 0)
		type = PYRAMID;
	if(distributeobject(type, props) == false)
		return (false);
	return (true);
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
		if (ft_strnstr(line, "#", ft_strlen(line)))
			continue ;
		props = getpropreties(&line);
		if (!props)
			err("Error parsing properties", 1);
		if(generateobject(props) == false)
			err("Error generating object", 1);
		if(g_scene->error){
			return false;
		}
	}
	return (true);
}

bool	parse(char *f)
{
	int	file;

	printf("%s\n", f);
	if (!f || (ft_strnstr(f, ".rt", ft_strlen(f)) == NULL))
		return (err("No file or doesn't have the correct extention\n", 1));
	file = open(f, O_RDONLY);
	if (file < 0)
		err("File not found or doesn't have the permissions\n", 1);
	if (!fetchdata(file))
		err("Error fetching data", 1);
	close(file);
	return (true);
}
