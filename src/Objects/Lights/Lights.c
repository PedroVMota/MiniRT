/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:56:30 by pedro             #+#    #+#             */
/*   Updated: 2024/02/10 17:16:56 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StandarLibrarys.h>

Object *newObject(size_t targetsize);
void *object_error_handler(Object *obj, void **ptr, char *msg);

// SECTION - AMBIENT LIGHT
static void	setup_am(char **p, Light *l)
{
	Vec3	color;

	l->i = getFloat(p[1], true, (float []){1, 0}, 0);
	color = getVec4(p[2], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	l->next = NULL;
}

// SECTION - POINT LIGHT
static void	setup_p(char **p, Light *l)
{
	Vec3	color;

	l->o = getVec4(p[1], true, INT16_MAX, -INT16_MAX);
	l->i = getFloat(p[2], true, (float []){1, 0}, 0);
	color = getVec4(p[3], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

Light	*newlight(int type, char **props)
{
	Light	*l;

	l = (Light *)newObject(sizeof(Light));
	l->type = type;
	if (type == POINT)
		setup_p(props, l);
	else if (type == AMBIENT)
		setup_am(props, l);
	l->next = NULL;
	return 	((Light *)object_error_handler((Object *)l, (void **)props, "-> Invalid sphere"));
}
// ANCHOR - LIGHTS.C IS OK