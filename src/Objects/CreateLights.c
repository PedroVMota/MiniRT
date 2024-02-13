/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateLights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:28:56 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 19:38:56 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static void	setup_am(char **p, Light *l)
{
	Vec3	color;

	printf("Error: %d\n", g_scene->error);
	l->i = getfloat(p[1], true, (float []){1, 0}, 0);
	printf("Error: %d\n", g_scene->error);
	color = getvec4(p[2], true, 255, 0);
	printf("Error: %d\n", g_scene->error);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
	l->next = NULL;
}

// SECTION - POINT LIGHT
static void	setup_p(char **p, Light *l)
{
	Vec3	color;

	l->o = getvec4(p[1], true, INT16_MAX, -INT16_MAX);
	l->i = getfloat(p[2], true, (float []){1, 0}, 0);
	color = getvec4(p[3], true, 255, 0);
	l->color = newrgb((int)color.x, (int)color.y, (int)color.z);
}

Light	*newlight(int type, char **props)
{
	Light	*l;

	l = (Light *)newobject(sizeof(Light), NULL);
	l->type = type;
	if (type == POINT)
		setup_p(props, l);
	else if (type == AMBIENT)
		setup_am(props, l);
	l->next = NULL;
	return ((Light *)object_error_handler((Object *)l, \
	(void **)props, "-> Invalid Light\n"));
}
