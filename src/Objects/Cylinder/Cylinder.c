/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:27:06 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 10:42:36 by pedro            ###   ########.fr       */
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

static void	full_half(t_cy *c, char **props)
{
	t_vector	color;

	color = (t_vector){0, 0, 0};
	if (g_scene->error != 2)
		c->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	if (g_scene->error != 2)
		c->d = norm(getvec4(props[2], true, 1, -1));
	if (g_scene->error != 2)
		c->diameter = getfloat(props[3], true, (float []){INT16_MAX / 3, 0}, 1);
	if (g_scene->error != 2)
		c->height = getfloat(props[4], true, (float []){INT16_MAX / 3, 0}, 1);
	color = ((t_vector){0, 0, 0});
	if (g_scene->error != 2)
		color = getvec4(props[5], true, 255, 0);
	c->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

static void	full_half2(t_cy *c, char **props)
{
	if (props[6])
	{
		c->specular = getfloat(props[6], true, (float []){1000, 0}, 0);
		c->reflection = getfloat(props[7], true, (float []){1, 0}, 0);
	}
}

t_cy	*newcylinder(int type, char **props)
{
	t_vector		color;
	t_cy			*c;

	if (count_args(&props[1], 5, 7))
		return (uptadeerror("Invalid arguments cylinder\n"), NULL);
	c = (t_cy *)newobject(sizeof(t_cy), (t_values (*)(t_obj *, t_ray)) \
		cylindercolision);
	c->type = CYLINDER;
	c->type = type;
	full_half(c, props);
	if (g_scene->error != 2)
		full_half2(c, props);
	return ((t_cy *)object_error_handler((t_obj *)c, \
		(void **)props, "-> Invalid Cylinder\n"));
}
