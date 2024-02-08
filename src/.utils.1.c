/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .utils.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:36:02 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 17:14:55 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"


Vec3 rotatee(Vec3 v, Vec3 theta) {
    Vec3 rotated_v;
    double sin_x = sin(theta.x);
    double cos_x = cos(theta.x);
    double sin_y = sin(theta.y);
    double cos_y = cos(theta.y);
    double sin_z = sin(theta.z);
    double cos_z = cos(theta.z);

    // Rotação em torno do eixo x
    rotated_v.x = v.x;
    rotated_v.y = v.y * cos_x - v.z * sin_x;
    rotated_v.z = v.y * sin_x + v.z * cos_x;

    // Rotação em torno do eixo y
    v = rotated_v;
    rotated_v.x = v.x * cos_y + v.z * sin_y;
    rotated_v.z = -v.x * sin_y + v.z * cos_y;

    // Rotação em torno do eixo z
    v = rotated_v;
    rotated_v.x = v.x * cos_z - v.y * sin_z;
    rotated_v.y = v.x * sin_z + v.y * cos_z;

    return rotated_v;
}

Ray	getraydir(Vec3 o, double x, double y)
{
	Camera	*cam;
	Ray		ray;
	
	cam = g_scene->camera;
	ray.o = o;
	ray.d.x = (x / g_scene->width * cam->width);
	ray.d.y = (y / g_scene->height);
	ray.d.z = 1;
	ray.d = rotatee(ray.d, cam->d);
	ray.o = cam->o;
	ray.val = (tValues){INFINITY, INFINITY};
	ray.ObjectClosest = NULL;
	return (ray);
}

void	objectadd(Object *nObj, Object **lst)
{
	Object	*tmp;

	tmp = *lst;
	if (!nObj)
		return ;
	if (nObj->type == AMBIENT)
	{
		if (!g_scene->am)
			g_scene->am = (Light *)nObj;
		else
			free (nObj);
		return ;
	}
	if (!*lst)
	{
		*lst = nObj;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = nObj;
}
