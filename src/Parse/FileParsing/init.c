/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:42:56 by pedro             #+#    #+#             */
/*   Updated: 2023/12/22 14:10:39 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static void	generate_data(void)
{
	t_object	*object;

	object = NULL;
	if (!scene()->objd)
		return ;
	if (!ft_strcmp(scene()->objd[0], "C"))
		object = scene()->add_objs[CAMERA](scene()->objd);
	if (!ft_strcmp(scene()->objd[0], "l"))
		object = scene()->add_objs[AMBIENT](scene()->objd);
	if (!ft_strcmp(scene()->objd[0], "A"))
		object = scene()->add_objs[AMBIENT](scene()->objd);
	if (!ft_strcmp(scene()->objd[0], "pl"))
		object = scene()->add_objs[PLANE](scene()->objd);
	if (!ft_strcmp(scene()->objd[0], "sp"))
		object = scene()->add_objs[SPHERE](scene()->objd);
	if (object != NULL)
		objectaddlast(object);
}

static bool	check_unwanted_characters(char **s)
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
				printf("%d\n ", s[i][j]);
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool	splitdata(int fd)
{
	while (scene()->error == 0)
	{
		scene()->line = get_next_line(fd);
		if (scene()->line == NULL)
			break ;
		scene()->objd = ft_splitstr(scene()->line, " \n\t");
		if (check_double_alloc((void **)scene()->objd))
			return (true);
		if (check_object_identifier(scene()->objd[0]))
		{
			scene()->error = 2;
			return (true);
		}
		if (check_unwanted_characters(&scene()->objd[1]))
		{
			scene()->error = 11;
			return (true);
		}
		generate_data();
		interator((void **)scene()->objd, free);
		free(scene()->line);
	}
	return (false);
}

bool	parse_data(char *file)
{
	int	fd;

	init_add_functions();
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (true);
	}
	if (splitdata(fd))
	{
		remove_object_list();
		free(scene()->line);
		close(fd);
		return (true);
	}
	remove_object_list();
	close(fd);
	return (false);
}
