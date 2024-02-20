/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:32:35 by pedro             #+#    #+#             */
/*   Updated: 2024/02/20 11:27:10 by pvital-m         ###   ########.fr       */
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
	p->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	p->height = getfloat(props[2], true, (float []){INT16_MAX / 3, 0}, 1);
	p->diameter = getfloat(props[3], true, (float []){INT16_MAX / 3, 0}, 1);
	p->zmin = getfloat(props[4], true, (float []){INT16_MAX / 3, 0}, 1);
	p->zmax = getfloat(props[5], true, (float []){INT16_MAX / 3, 0}, 1);
	color = getvec4(props[6], true, 255, 0);
	p->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

t_pa	*newparaboloid(int type, char **props)
{
	t_pa	*p;

	if (count_args(&props[1], 6, 6))
		return (delprops(&props), uptadeerror("Invalid arguments paraboloid\n"), NULL);
	p = (t_pa *)newobject(sizeof(t_pa), (t_values (*)(t_obj *, t_ray)) \
		paraboloidcollision);
	if (!p)
		return (NULL);
	fill_data(props, p);
	p->type = type;
	return (delprops(&props), (t_pa *)errhandler((t_obj *)p, "-> Invalid Paraboloid\n"));
}
