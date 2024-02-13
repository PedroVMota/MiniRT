/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:12:01 by pedro             #+#    #+#             */
/*   Updated: 2024/02/13 19:40:34 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	distributeobject(int type, char **props)
{
	if (type == UNKNOWN)
		return (uptadeerror("Unknown object type"), delprops(&props), false);
	if (type == SPHERE)
		objectadd((Object *)newsphere(type, props), (void **)&g_scene->objects);
	if (type == PLANE)
		objectadd((Object *)newplane(type, props), (void **)&g_scene->objects);
	if (type == CAMERA)
		objectadd((Object *)newcamera(type, props), (void **)&g_scene->camera);
	if (type == POINT)
		objectadd((Object *)newlight(type, props), (void **)&g_scene->lights);
	if (type == AMBIENT)
		objectadd((Object *)newlight(type, props), (void **)&g_scene->am);
	if (type == CYLINDER)
		objectadd((Object *)newcylinder(type, props),
			(void **)&g_scene->objects);
	if (type == PARABOLOID)
		objectadd((Object *)newparaboloid(type, props),
			(void **)&g_scene->objects);
	return (true);
}

/*ANCHOR - 
	Norminette: OK
	Compilation: OK
	Tests: OK
*/