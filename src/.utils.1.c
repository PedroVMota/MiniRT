/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .utils.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:36:02 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/10 17:05:57 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"


void	rotation_x(Vec3 *vec, Vec3 *theta)
{
    double	temp_z;
    double	temp_y;

    temp_z = vec->z;
    temp_y = vec->y;
    vec->y = temp_y * cos(theta->x) + temp_z * sin(theta->x);
    vec->z = -temp_y * sin(theta->x) + temp_z * cos(theta->x);
}

void	rotation_y(Vec3 *vec, Vec3 *theta)
{
    double	temp_x;
    double	temp_z;

    temp_x = vec->x;
    temp_z = vec->z;
    vec->x = temp_x * cos(theta->y) + temp_z * sin(theta->y);
    vec->z = -temp_x * sin(theta->y) + temp_z * cos(theta->y);
}

void	rotation_z(Vec3 *vec, Vec3 *theta)
{
    double	temp_x;
    double	temp_y;

    temp_x = vec->x;
    temp_y = vec->y;
    vec->x = temp_x * cos(theta->z) - temp_y * sin(theta->z);
    vec->y = temp_x * sin(theta->z) + temp_y * cos(theta->z);
}

void rotatee(Vec3 *v, Vec3 *theta) {
    rotation_x(v, theta);
    rotation_y(v, theta);
    rotation_z(v, theta);
}

Ray	getraydir(Vec3 o, double x, double y)
{
    Camera	*cam;
    Ray		ray;
    
    cam = g_scene->camera;
    ray.o = o;
    ray.d.x = (x / g_scene->width * cam->width) + cam->d.x;
    ray.d.y = (y / g_scene->height) + cam->d.y;
    ray.d.z = cam->d.z;
    //rotatee(&(ray.d), &(cam->d)); // Adiciona rotação aqui
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
