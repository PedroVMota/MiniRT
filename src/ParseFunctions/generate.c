/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:12:01 by pedro             #+#    #+#             */
/*   Updated: 2024/02/14 20:56:23 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	distributeobject(int type, char **props)
{
	if (type == UNKNOWN)
		return (uptadeerror("Unknown object type"), delprops(&props), false);
	if (type == SPHERE)
		objectadd((t_obj *)newsphere(type, props), (void **)&g_scene->objects);
	if (type == PLANE)
		objectadd((t_obj *)newplane(type, props), (void **)&g_scene->objects);
	if (type == CAMERA)
		objectadd((t_obj *)newcamera(type, props), (void **)&g_scene->camera);
	if (type == POINT)
		objectadd((t_obj *)newlight(type, props), (void **)&g_scene->lights);
	if (type == AMBIENT)
		objectadd((t_obj *)newlight(type, props), (void **)&g_scene->am);
	if (type == CYLINDER)
		objectadd((t_obj *)newcylinder(type, props),
			(void **)&g_scene->objects);
	if (type == PARABOLOID)
		objectadd((t_obj *)newparaboloid(type, props),
			(void **)&g_scene->objects);
	return (true);
}

/*ANCHOR - 
	Norminette: OK
	Compilation: OK
	Tests: OK
*/