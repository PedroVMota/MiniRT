/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:32:35 by pedro             #+#    #+#             */
/*   Updated: 2024/02/17 20:49:57 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static bool	count_args(char **props, int wtoptional, int woptional)
{
	int	i;

	i = -1;
	while (props[++i])
		;
	if (i == woptional || i == wtoptional)
		return (false);
	return (true);
}

static void	fill_data(char **props, t_pa *p)
{
	t_vector	color;

	color = (t_vector){0, 0, 0};
	if (g_scene->error != 2)
		p->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	if (g_scene->error != 2)
		p->height = getfloat(props[2], true, (float []){INT16_MAX / 3, \
		0}, 1);
	if (g_scene->error != 2)
		p->diameter = getfloat(props[3], true, (float []){INT16_MAX / 3, \
		0}, 1);
	if (g_scene->error != 2)
		color = getvec4(props[4], true, 255, 0);
	p->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

t_pa	*newparaboloid(int type, char **props)
{
	t_pa	*p;

	if (count_args(&props[1], 4, 7))
		return (uptadeerror("Invalid arguments paraboloid\n"), NULL);
	p = (t_pa *)newobject(sizeof(t_pa), (t_values (*)(t_obj *, t_ray)) \
		paraboloidcollision);
	if (!p)
		return (NULL);
	fill_data(props, p);
	p->type = type;
	if (props[5])
	{
		p->specular = getfloat(props[5], true, (float []){10000, 0}, 1);
		p->reflection = getfloat(props[6], true, (float []){1, 0}, 0);
		p->checkerboard = getfloat(props[7], true, (float []){3, 0}, 0);
	}
	return ((t_pa *)errhandler((t_obj *)p, "-> Invalid Paraboloid\n"));
}
