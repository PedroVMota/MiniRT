/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/28 20:00:28 by pedro            ###   ########.fr       */
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

Object *getClosestObject(Ray *rayTrace, double maxDistance, double minDistance)
{
	double ct = INFINITY;
	Object *closest = NULL;
	for (Object *lst = scene->objects; lst; lst = lst->next)
	{
		rayTrace->val = lst->colision(lst, *rayTrace);
		if ((rayTrace->val.t0 > minDistance && rayTrace->val.t0 < maxDistance) && rayTrace->val.t0 < ct)
		{
			closest = lst;
			ct = rayTrace->val.t0;
		}
		if ((rayTrace->val.t1  > minDistance && rayTrace->val.t1 < maxDistance) && rayTrace->val.t1 < ct)
		{
			closest = lst;
			ct = rayTrace->val.t1;
		}
	}
	return closest;
}

Vec4 RayColor(Ray rayTrace)
{

	Vec4 CurrentColor = getBackgroundColor(rayTrace);
	Object *obj =  getClosestObject(&rayTrace, INFINITY, 0);
	if (!obj)
		return CurrentColor;
	printf("Closest Object Address: %p\n", obj);
	return obj->color;
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

#ifdef __APPLE__
	#define UP 126
	#define DOWN 125
	#define LEFT 123
	#define RIGHT 124
	#define ESC 53
	#define W 13
	#define A 0
	#define S 1
	#define D 2
#else
	#define UP 126
	#define DOWN 125
	#define LEFT 123
	#define RIGHT 124
	#define ESC 53
	#define W 13
	#define A 0
	#define S 1
	#define D 2
#endif

int keyhook(int keycode, t_mlxdata *mlx)
{
    if (keycode == 0xFF1B) // Escape key
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
	switch (keycode)
	{
	case UP:
		scene->camera->o.z += 0.1;
		renderFrame();
		break;
	case DOWN:
		scene->camera->o.z -= 0.1;
		renderFrame();
		break;
	case LEFT:
		scene->camera->o.x -= 0.1;
		renderFrame();
		break;
	case RIGHT:
		scene->camera->o.x += 0.1;
		renderFrame();
		break;
	case W:
		scene->camera->o.y += 0.1;
		renderFrame();
		break;
	case S:
		scene->camera->o.y -= 0.1;
		renderFrame();
		break;
	default:
		break;
	}
    return 0;
}

int main(void)
{
	scene = malloc(sizeof(gscene));
	if (!scene)
		return 1;
	scene->width = 300;
	scene->height = 300;
	scene->camera = NULL;
	scene->objects = NULL;
	scene->lights = NULL;

	scene->mlx = malloc(sizeof(t_mlxdata));
	if (!scene->mlx)
		return 1;

	objectAdd(
		(Object *)newCamera(
			(Vec3){0, 0, -5},
			(Vec3){0, 0, 1},
			90,
			(Vec3){0, 0, 0}),
		(Object **)&scene->camera);

	objectAdd(
		(Object *)newSphere(
			(Vec3){0, 0, 0},
			(Vec3){0, 0, 1},
			(Vec4){0, 0, 255, 0},
			(Vec3){0, 0, 0},
			1,
			sphereColision),
		(Object **)&scene->objects);
	objectAdd(
		(Object *)newSphere(
			(Vec3){2, 0, 0},
			(Vec3){0, 0, 1},
			(Vec4){0, 255, 255, 0},
			(Vec3){0, 0, 0},
			1,
			sphereColision),
		(Object **)&scene->objects);
	objectAdd(
		(Object *)newSphere(
			(Vec3){-2, 0, 0},
			(Vec3){0, 0, 1},
			(Vec4){0, 255, 0, 255},
			(Vec3){0, 0, 0},
			1,
			sphereColision),
		(Object **)&scene->objects);

	if (!scene->camera)
		return printf("No camera found\n"), 1;
	if (!initialize_mlx())
		return printf("Error initializing mlx\n"), 1;

	renderFrame();
	mlx_key_hook(scene->mlx->win, keyhook, scene->mlx);
	mlx_loop(scene->mlx->mlx);
	return 0;
}