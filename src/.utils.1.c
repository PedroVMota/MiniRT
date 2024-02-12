/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .utils.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:36:02 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/12 17:28:14 by pedro            ###   ########.fr       */
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
	ray.d.x = ((x) / g_scene->width) * cam->width;
	ray.d.y = ((y) / g_scene->height) * cam->height;
	ray.d.z = 1;
	ray.o = cam->o;
	ray.val = (tValues){.t0 = INFINITY, .t1 = INFINITY};
	ray.objc = NULL;
	return (ray);
}


void lights(Light *l, Light **lst)
{
    Light *head;

    head = *lst;
    if(!*lst) {
        *lst = l;
        return;
    }
    while(*lst && (*lst)->next)
        (*lst) = (Object *)(*lst)->next;
    (*lst)->next = l;
    *lst = head;
}

void	objects(Object *l, Object **lst)
{
	Object	*head;

	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = l;
	*lst = head;
}

void	camera(Camera *l, Camera **lst)
{
	Camera	*head;

	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while ((*lst)->next)
		(*lst) = (Camera *)(*lst)->next;
	(*lst)->next = l;
	*lst = head;
}

void	objectadd(Object *nObj, void **list)
{
	if (nObj->type == POINT || nObj->type == AMBIENT)
		lights((Light *)nObj, (Light **)list);
	else if (nObj->type == CAMERA)
		camera((Camera *)nObj, (Camera **)list);
	else if (nObj->type == SPHERE || nObj->type == PLANE || \
	nObj->type == CYLINDER || nObj->type == PARABOLOID)
		objects(nObj, (Object **)list);
}
