/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:30:24 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 11:34:45 by pedro            ###   ########.fr       */
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

static void	fill_data(char **props, t_sp *s)
{
	t_vector	color;

	color = (t_vector){0, 0, 0};
	s->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	s->diameter = getfloat(props[2], true, (float []){INT16_MAX / 3, 0}, 1);
	color = getvec4(props[3], true, 255, 0);
	s->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

t_sp	*newsphere(int type, char **props)
{
	t_sp		*s;

	if (count_args(&props[1], 3, 5))
		return (uptadeerror("Invalid arguments sphere\n"), NULL);
	s = (t_sp *)newobject(sizeof(t_sp), spherecolision);
	if (!s)
		return (NULL);
	s->type = type;
	fill_data(props, s);
	if (props[4])
	{
		s->specular = (int)getfloat(props[4], true, (float []){1000, 0}, 1);
		if (!g_scene->error && props[5])
			s->reflection = getfloat(props[5], true, (float []){1, 0}, 0);
	}
	s->next = NULL;
	return ((t_sp *)errhandler((t_obj *)s, "-> Invalid sphere\n"));
}
