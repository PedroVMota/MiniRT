/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/28 01:50:13 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

gscene *scene = NULL;

void objectAdd(Object *nObj, Object **lst)
{
	if (!*lst)
	{
		*lst = nObj;
		return;
	}
	Object *tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = nObj;
}

Vec4 getBackgroundColor(Ray raytrace)
{
	Vec4 color = (Vec4){0, 0, 0, 0};
	Vec3 unit_direction = unitVector(raytrace.d);
	double t = 0.5 * (unit_direction.y + 1.0);
	unsigned int white = 0xFFFFFF; // RGB white
	unsigned int blue = 0x7FB2FF;  // RGB blue
	color.r = (unsigned int)((1.0 - t) * ((white >> 16) & 0xFF) + t * ((blue >> 16) & 0xFF));
	color.g = (unsigned int)((1.0 - t) * ((white >> 8) & 0xFF) + t * ((blue >> 8) & 0xFF));
	color.b = (unsigned int)((1.0 - t) * (white & 0xFF) + t * (blue & 0xFF));
	return color;
}

Ray getClosestObject(Ray *rayTrace, double maxDistance, double minDistance)
{
	double closestDistance = INFINITY;
	for (Object *lst = scene->objects; lst; lst = lst->next)
	{
		rayTrace->val = lst->colision(lst, *rayTrace);
		if ((rayTrace->val.t0 > minDistance && rayTrace->val.t0 < maxDistance) && rayTrace->val.t0 < closestDistance)
		{
			rayTrace->ObjectClosest = lst;
			closestDistance = rayTrace->val.t0;
		}
		if ((rayTrace->val.t1  > minDistance && rayTrace->val.t1 < maxDistance) && rayTrace->val.t1 < closestDistance)
		{
			rayTrace->ObjectClosest = lst;
			closestDistance = rayTrace->val.t1;
		}
	}
	return *rayTrace;
}

Vec4 RayColor(Ray rayTrace)
{

	Vec4 CurrentColor = getBackgroundColor(rayTrace);
	rayTrace = getClosestObject(&rayTrace, INFINITY, 1);
	if (!rayTrace.ObjectClosest)
		return CurrentColor;
	return rayTrace.ObjectClosest->color;
}

void renderFrame()
{
	// Calculate teh vector across the horizontal and down the vertical viewport edges.
	// Calculate the horizontal and vertical delta vector form the pixel to pixel.
	// calculate the location of the upper left pixel.

	for (double y = scene->height / 2; y > -scene->height / 2; y--)
	{
		for (double x = -scene->width / 2; x < scene->width / 2; x++)
		{
			Ray ray = GetRayDir((scene->camera)->o, x, y);
			Vec4 color = RayColor(ray);
			my_mlx_pixel_put(toCanvas(x, false), toCanvas(y, true), color);
		}
	}
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img, 0, 0);
	printf("\rDone.\n");
}



int main(void)
{
	scene = malloc(sizeof(gscene));
	if (!scene)
		return 1;
	scene->width = 1000;
	scene->height = 500;
	scene->camera = NULL;
	scene->objects = NULL;

	scene->mlx = malloc(sizeof(t_mlxdata));
	if (!scene->mlx)
		return 1;

	objectAdd(
		(Object *)newCamera(
			(Vec3){0, 0, 0},
			(Vec3){0, 0, 1},
			90,
			(Vec3){0, 0, 0}),
		(Object **)&scene->camera);

	//plane | 
	objectAdd(
		(Object *)newPlane(
			(Vec3){5, 0, 0},
			(Vec3){1, 0, 0},
			(Vec4){0, 0, 255, 0},
			(Vec3){0, 0, 0},
			100,
			planeColision),
		(Object **)&scene->objects);

	objectAdd(
		(Object *)newPlane(
			(Vec3){-5, 0, 0},
			(Vec3){1, 0, 0},
			(Vec4){0, 255, 0, 0},
			(Vec3){0, 0, 0},
			100,
			planeColision),
		(Object **)&scene->objects);

	objectAdd(
		(Object *)newPlane(
			(Vec3){0, -5, 0},
			(Vec3){0, 1, 0},
			(Vec4){0, 150,150,150},
			(Vec3){0, 0, 0},
			100,
			planeColision),
		(Object **)&scene->objects);
	objectAdd(
		(Object *)newPlane(
			(Vec3){0, 5, 0},
			(Vec3){0, 1, 0},
			(Vec4){0, 150,150,150},
			(Vec3){0, 0, 0},
			100,
			planeColision),
		(Object **)&scene->objects);

	objectAdd(
		(Object *)newPlane(
			(Vec3){0, 0, 10},
			(Vec3){0, 0, -1},
			(Vec4){0, 255, 255, 255},
			(Vec3){0, 0, 0},
			100,
			planeColision),
		(Object **)&scene->objects);

	objectAdd(
	(Object *)newSphere(
		(Vec3){0, 0, 5},
		(Vec3){0, 0, 0},
		(Vec4){0, 15,163,234},
		(Vec3){0, 0, 0},
		1,
		sphereColision),
	(Object **)&scene->objects);
	


	if (!scene->camera)
		return printf("No camera found\n"), 1;
	if (!initialize_mlx())
		return printf("Error initializing mlx\n"), 1;

	for (Object *lst = scene->objects; lst; lst = lst->next)
	{
		printf("Current Object Address: %p\n", lst);
		printf("O[x, y, z]: [%f, %f, %f]\n", lst->o.x, lst->o.y, lst->o.z);
		printf("D[x, y, z]: [%f, %f, %f]\n", lst->d.x, lst->d.y, lst->d.z);
		printf("Color[r, g, b, ts]: [%u, %u, %u, %u]\n", lst->color.r, lst->color.g, lst->color.b, lst->color.t);
		printf("Theta[x, y, z]: [%f, %f, %f]\n", lst->theta.x, lst->theta.y, lst->theta.z);
		printf("Type: [%d]\n", lst->type);
		printf("Next Address: %p\n", lst->next);
	}

	for (Camera *lst = scene->camera; lst; lst = lst->next)
	{
		printf("Current Camera Address: %p\n", lst);
		printf("O[x, y, z]: [%f, %f, %f]\n", lst->o.x, lst->o.y, lst->o.z);
		printf("D[x, y, z]: [%f, %f, %f]\n", lst->d.x, lst->d.y, lst->d.z);
		printf("FOV: [%f]\n", lst->fov);
		printf("Theta[x, y, z]: [%f, %f, %f]\n", lst->theta.x, lst->theta.y, lst->theta.z);
		printf("Next Address: %p\n", lst->next);
	}
	renderFrame();
	mlx_loop(scene->mlx->mlx);
	return 0;
}