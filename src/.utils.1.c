/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .utils.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:36:02 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 01:02:47 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

Ray	getraydir(Vec3 o, double x, double y)
{
	Camera	*cam;
	Ray		ray;

	cam = scene->camera;
	ray.o = o;
	ray.d.x = x / scene->width * cam->width;
	ray.d.y = y / scene->height;
	ray.d.z = 1;
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
		if (!scene->am)
			scene->am = (Light *)nObj;
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
