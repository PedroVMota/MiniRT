/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:12:01 by pedro             #+#    #+#             */
/*   Updated: 2024/02/12 19:12:54 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	distributeobject(int type, char **props)
{
	if (type == UNKNOWN)
		return (updateError("Unknown object type"), delprops(&props), false);
	if (type == SPHERE)
		objectadd((Object *)newSphere(type, props), (void **)&g_scene->objects);
	if (type == PLANE)
		objectadd((Object *)newPlane(type, props), (void **)&g_scene->objects);
	if (type == CAMERA)
		objectadd((Object *)newCamera(type, props), (void **)&g_scene->camera);
	if (type == POINT)
		objectadd((Object *)newlight(type, props), (void **)&g_scene->lights);
	if (type == AMBIENT)
		objectadd((Object *)newlight(type, props), (void **)&g_scene->am);
	if (type == CYLINDER)
		objectadd((Object *)newCylinder(type, props),
			(void **)&g_scene->objects);
	if (type == PARABOLOID)
		objectadd((Object *)newParaboloid(type, props),
			(void **)&g_scene->objects);
	return (true);
}

/*ANCHOR - 
	Norminette: OK
	Compilation: OK
	Tests: OK
*/