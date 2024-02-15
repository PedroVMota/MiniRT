/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:30:24 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 08:23:37 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_sp	*newsphere(int type, char **props)
{
	t_sp		*s;
	t_vector	color;

	color = (t_vector){0, 0, 0};
	s = (t_sp *)newobject(sizeof(t_sp), spherecolision);
	if (g_scene->error != 2)
		s->o = getvec4(props[1], true, INT16_MAX, -INT16_MAX);
	if (g_scene->error != 2)
		s->diameter = getfloat(props[2], true, (float []){INT16_MAX / 3, 0}, 1);
	if (g_scene->error != 2)
		color = getvec4(props[3], true, 255, 0);
	s->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	s->type = type;
	if (props[4])
	{
		s->specular = (int)getfloat(props[4], true, (float []){1000, 0}, 1);
		if (!g_scene->error && props[5])
			s->reflection = getfloat(props[5], true, (float []){1, 0}, 0);
	}
	s->next = NULL;
	return ((t_sp *)object_error_handler((t_obj *)s, \
	(void **)props, "-> Invalid sphere\n"));
}
