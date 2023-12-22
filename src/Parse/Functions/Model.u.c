/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:52:34 by pedro             #+#    #+#             */
/*   Updated: 2023/12/22 14:23:31 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_object	*create_camera(char **objectdata);
t_object	*create_light(char **objectdata);
t_object	*create_sp(char **objectdata);
t_object	*generate_pl(char **objectdata);
t_object	*create_cy(char **objectdata);
t_object	*create_cn(char **objectdata);


void	*generate_object(int size)
{
	t_object	*object;

	object = (t_object *)ft_calloc(size, 1);
	return (object);
}

bool	isallnum(char *str, int error)
{
	int	i;

	i = 0;
	if (!str)
	{
		scene()->error = error;
		return (false);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
		{
			scene()->error = error;
			return (false);
		}
		i++;
	}
	return (true);
}

void	init_add_functions(void)
{
	scene()->add_objs[CAMERA] = create_camera;
	scene()->add_objs[AMBIENT] = create_light;
	scene()->add_objs[POINT] = create_light;
	scene()->add_objs[DIRECTIONAL] = create_light;
	scene()->add_objs[PLANE] = generate_pl;
	scene()->add_objs[SPHERE] = create_sp;
	scene()->add_objs[CYLINDER] = create_cy;
	scene()->add_objs[CONE] = create_cn;
}