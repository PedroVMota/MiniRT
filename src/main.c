/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/29 18:51:19 by pedro            ###   ########.fr       */
/*                                                \                            */
/* ************************************************************************** */

#include "center.h"

gscene *scene = NULL;



int computeColor(int obj_color, Vec4 objectColor)
{
	int r;
	int g;
	int b;

	r = ((obj_color >> 16 & 255)) * objectColor.r;
	g = ((obj_color >> 8 & 255)) * objectColor.g;
	b = ((obj_color & 255)) * objectColor.b;
	return newrgb(r, g, b);
}

int RayColor(Ray rayTrace, int depth)
{
	int localColor = 0;
	Object *obj = intersections(&rayTrace, INFINITY, 0, true);
	if (!obj)
		return 0;
	if (dot(rayTrace.d, rayTrace.normal) > 0)
		rayTrace.normal = mul(rayTrace.normal, -1);
	Vec4 objectColor = calcligh(rayTrace.HitPoint, rayTrace.normal,rayTrace.d, obj->specular);
	localColor = computeColor(obj->color, objectColor);
	if(obj->reflection <= 0 || obj->specular <= 0 || depth <= 0)
		return localColor;
	double reflection = obj->reflection;
	Vec3 reflected = reflect(rayTrace.d, rayTrace.normal);
	Ray reflectedRay = (Ray){add(rayTrace.HitPoint, mul(reflected, 0.001)), \
		reflected};
	int reflectedColor = RayColor(reflectedRay, depth - 1);
	localColor = newrgb(
		(int)(mulcomp(localColor, 16, 1 - reflection) + mulcomp(reflectedColor, 16, reflection)),
		(int)(mulcomp(localColor, 8, 1 - reflection) + mulcomp(reflectedColor, 8, reflection)),
		(int)(mulcomp(localColor, 0, 1 - reflection) + mulcomp(reflectedColor, 0, reflection)));
	return localColor;
}

void renderFrame()
{
	clock_t start = clock();
	for (double y = scene->height / 2; y > -scene->height / 2; y--)
	{
		for (double x = -scene->width / 2; x < scene->width / 2; x++)
		{
			Ray ray = getraydir((scene->camera)->o, x, y);
			int color = RayColor(ray, scene->depth);
			my_mlx_pixel_put(tocanvas(x, false), tocanvas(y, true), color);
		}
	}
	printf("Time to render: %f\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img, 0, 0);
	printf("\rDone.\n");
}


void del(Object **lsg)
{
	if(!lsg)
		return;
	if(!*lsg)
		return;
	del(&(*lsg)->next);
	free(*lsg);
}

// int key_hook(int keycode)
// {
// 	printf("Keycode: %d\n", keycode);
// 	if (keycode == ESC)
// 	{
// 		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
// 		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
// 		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
// 		// mlx_destroy_display(scene->mlx->mlx);
// 		free(scene->mlx->mlx);
// 		free(scene->mlx);
// 		del((Object **)&scene->objects);
// 		del((Object **)&scene->lights);
// 		del((Object **)&scene->camera);
// 		del((Object **)&scene->am);
// 		del(NULL);
// 		free(scene);
// 		exit(0);
// 	}
// 	return 0;
// }


int main(void)
{
	scene = init_main(500, 500, 0);
	if (!scene)
		return 1;
	objectadd(
		(Object *)newCamera(
			(Vec3){0, 0, -5},
			(Vec3){0, 0, 0},
			53.3,
			(Vec3){0, 0, 0}),
		(Object **)&scene->camera);
	
	objectadd((Object *)newSphere((Vec3){-1, 0, 0},(Vec3){0, 0, 0},(Vec4){255, 255, 255},(Vec3){0, 0, 0},0.5,spherecolision,0, 32), (Object **)&scene->objects);
	objectadd((Object *)newCylinder((Vec3){0, 0, 0},(Vec3){0, 1, 0},1, 3, (Vec4){255, 255, 255},(Vec3){0, 0, 0},cylindercolision,0, 32), (Object **)&scene->objects);
	objectadd((Object *)newSphere((Vec3){1, 0, 0},(Vec3){0, 0, 0},(Vec4){255, 255, 255},(Vec3){0, 0, 0},0.5,spherecolision,0, 32), (Object **)&scene->objects);
	objectadd((Object *)newSphere((Vec3){0, 0, 0},(Vec3){0, 0, 0},(Vec4){255, 255, 255},(Vec3){0, 0, 0},0.5,spherecolision,0, 32), (Object **)&scene->objects);
	objectadd((Object *)newSphere((Vec3){0, 3, 0},(Vec3){0, 0, 0},(Vec4){255, 255, 255},(Vec3){0, 0, 0},0.5,spherecolision,0, 32), (Object **)&scene->objects);
	objectadd((Object *)newLight((Vec3){1, -2, -2}, (Vec3){0,0,0}, (Vec4){255,0,0}, (Vec3){0,0,0}, 0.2, AMBIENT), (Object **)&scene->lights);
	objectadd((Object *)newLight((Vec3){1, 2, -2}, (Vec3){0,0,0}, (Vec4){0,255,0}, (Vec3){0,0,0}, 1, POINT), (Object **)&scene->lights);
	objectadd((Object *)newLight((Vec3){-1, 2, -2}, (Vec3){0,0,0}, (Vec4){0,0,255}, (Vec3){0,0,0}, 1, POINT), (Object **)&scene->lights);
	objectadd((Object *)newLight((Vec3){-1, -2, -2}, (Vec3){0,0,0}, (Vec4){255,255,255}, (Vec3){0,0,0}, 0.2, AMBIENT), (Object **)&scene->lights);
	objectadd((Object *)newPlane((Vec3){0, -1, 0}, (Vec3){0, 1, 0}, (Vec4){255, 255, 255}, (Vec3){0, 0, 0}, 10, planecolision, 1, 0.2, 0), (Object **)&scene->objects);
	objectadd((Object *)newPlane((Vec3){-2, 0, 0}, (Vec3){1, 0, 0}, (Vec4){255, 255, 255}, (Vec3){0, 0, 0}, 10, planecolision, 0.5, 0, 0), (Object **)&scene->objects);
	objectadd((Object *)newPlane((Vec3){2, 0, 0}, (Vec3){1, 0, 0}, (Vec4){255, 255, 255}, (Vec3){0, 0, 0}, 10, planecolision, 0.5, 0, 0), (Object **)&scene->objects);
	if(!scene->objects || !scene->lights || !scene->camera)
		return 1;
	// mlx_key_hook(scene->mlx->win, key_hook, NULL);
	renderFrame();
	mlx_loop(scene->mlx->mlx);

	return 0;
}

