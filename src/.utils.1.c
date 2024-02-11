/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .utils.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:36:02 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 11:39:02 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StandarLibrarys.h>

Ray	getraydir(Vec3 o, double x, double y)
{
	Camera	*cam;
	Ray		ray;

	cam = g_scene->camera;
	ray.o = o;
	ray.d.x = x / g_scene->width * cam->width;
	ray.d.y = y / g_scene->height;
	ray.d.z = 1;
	ray.o = cam->o;
	ray.val = (tValues){.t0 = INFINITY, .t1 = INFINITY};
	ray.ObjectClosest = NULL;
	return (ray);
}
