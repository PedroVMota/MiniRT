/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:42:56 by pedro             #+#    #+#             */
/*   Updated: 2023/12/23 22:01:43 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	generate_data()
{
	t_object	*object;

	object = NULL;
	if (!ft_strcmp((scene())->objd[0], "C"))
		object = (scene())->add_objs[CAMERA]((scene())->objd);
	if (!ft_strcmp((scene())->objd[0], "L"))
		object = (scene())->add_objs[POINT]((scene())->objd);
	if (!ft_strcmp((scene())->objd[0], "A"))
		object = (scene())->add_objs[AMBIENT]((scene())->objd);
	if (!ft_strcmp((scene())->objd[0], "pl"))
		object = (scene())->add_objs[PLANE]((scene())->objd);
	if (!ft_strcmp((scene())->objd[0], "sp"))
		object = (scene())->add_objs[SPHERE]((scene())->objd);
	if (object != NULL)
		objectaddlast(object);
	if(scene()->error)
		return (true);
	return (false);
}

bool	check_unwanted_characters(char **s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (!ft_isdigit(s[i][j]) && s[i][j] != '.' && s[i][j] != '-'
				&& s[i][j] != '+' && s[i][j] != ',')
			{
				printf("Char: %c\n", s[i][j]);
				scene()->error = 11;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

char **parsedata(char *s, t_type *identifier)
{
	char **data;
	
	(void)identifier;
	if (!s)
		return NULL;
	data = ft_splitstr(s, " \t\n");
	free(s);
	return data;
}

bool	splitdata(int fd)
{
	t_type identifier;

	identifier = EMPTY_LINE;
	while (!(scene())->error)
	{
		scene()->line = get_next_line(fd);
		scene()->objd = parsedata(scene()->line, &identifier);
		if(!scene()->objd)
			break;
		if(scene()->objd[0] && check_unwanted_characters(&scene()->objd[1]))
			break ;
		if(scene()->objd[0] && generate_data())
			break;
		interator(&scene()->objd, free);
	}
	interator(&scene()->objd, free);	
	return (false);
}

bool	parse_data(char *file)
{
	int	fd;

	init_add_functions();
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		(scene())->error = -1;
		report();
		return (true);
	}
	if ((scene())->error == 0 && splitdata(fd))
	{
		remove_object_list();
		free((scene())->line);
		close(fd);
		return (true);
	}
	remove_object_list();
	close(fd);
	return (false);
}
