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
Vec4 getBackgroundColor(Ray raytrace);
Vec3 normalCalc(Object *obj, Vec3 p);

Object *getClosestObject(Ray *rayTrace, double maxDistance, double minDistance, bool updateData)
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
		else if ((rayTrace->val.t1 > minDistance && rayTrace->val.t1 < maxDistance) && rayTrace->val.t1 < ct)
		{
			closest = lst;
			ct = rayTrace->val.t1;
		}
	}
    if(updateData){
        rayTrace->normal = normalCalc(closest, Add(rayTrace->o, Mul(rayTrace->d, ct)));
        rayTrace->ct = ct;
        rayTrace->HitPoint = Add(rayTrace->o, Mul(rayTrace->d, ct));
    }
	return closest;
}

double calculateLighting(Vec3 point, Vec3 normal, Vec3 Hitpoint)
{
	Light *l = scene->lights;
	if (!l)
		return 0;
	double intensity = 0;
	double length_n = Length(normal); // Corrected typo
	Vec3 vec_l;

	while (l)
	{
		if (l->type == AMBIENT)
			intensity += l->intensity;
		else
		{
			vec_l = Sub(l->o, Hitpoint);
			vec_l = Normalize(vec_l);
            Ray lightVector;

            lightVector.o = Hitpoint;
            lightVector.d = Sub(l->o, Hitpoint);
            
			if(getClosestObject(&lightVector, 1, 0.001, false)){
				l = (Light *)l->next;
				continue;
			}
			double n_dot_l = Dot(normal, vec_l);
			if (n_dot_l > 0.001)
				intensity += l->intensity * n_dot_l / (Length(vec_l) * length_n);
		}
		l = (Light *)l->next;
	}
	return intensity;
}

Vec4 RayColor(Ray rayTrace)
{
	Vec4 CurrentColor = getBackgroundColor(rayTrace);
	// Vec4 CurrentColor = (Vec4){0, 0, 0, 0};
	Object *obj = getClosestObject(&rayTrace, INFINITY, 0, true);
	if (!obj)
		return Mul4(CurrentColor, 0.2);
	Vec4 objectColor = obj->color;
	if (Dot(rayTrace.d, rayTrace.normal) > 0)
		rayTrace.normal = Mul(rayTrace.normal, -1);
	double i = calculateLighting(rayTrace.o, rayTrace.normal, rayTrace.HitPoint);
	objectColor.r *= i;
	objectColor.g *= i;
	objectColor.b *= i;

	return objectColor;
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
#define SPACE 49
#else
#define SPACE 32 // 49
#define UP 65362	// 126
#define DOWN 65364	// 125
#define LEFT 65361	// 123
#define RIGHT 65363 // 124
#define ESC 65307	// 53
#define W 119		// 13
#define A 97		// 0
#define S 115		// 1 D // 2
#define D 100
#endif


Object *selected = NULL;

void changeSelector(int keycode) {
    static int selector = 0;

    if (keycode == SPACE) {
        selector++;
        printf("Changing Selector %d\n", selector);
        if (selector == 3) {
            selector = 0;
            printf("Restructuring selector the value to 0\n");
        }
    }
    if (selector == 0)
        selected = (Object *) scene->lights;
    if (selector == 1)
        selected = scene->objects;
    if(selector == 2)
        selected = (Object *)scene->camera;
}
int keyhook(int keycode)
{
	printf("keycode: %d\n", keycode);
    if(keycode == SPACE || selected == NULL)
        changeSelector(keycode);
	if (keycode == UP)
		selected->o.z += 0.1;
	if (keycode == DOWN)
        selected->o.z -= 0.1;
	if (keycode == LEFT)
        selected->o.x -= 0.1;
	if (keycode == RIGHT)
        selected->o.x += 0.1;
	if (keycode == W)
        selected->o.y += 0.1;
	if (keycode == S)
        selected->o.y -= 0.1;
	if (keycode == ESC)
	{
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
#ifndef __APPLE__
		mlx_destroy_display(scene->mlx->mlx);
#endif
		free(scene->mlx->mlx);
		free(scene->mlx);
		exit(0);
	}
    if(keycode == SPACE || keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT || keycode == W || keycode == S)
        renderFrame();
	return 0;
}

int main(void)
{
	scene = init_MainStruct(250, 250);
    if(!scene)
        return 1;

    objectAdd(
            (Object *)newCamera(
                    (Vec3){1, 3, 0},
                    (Vec3){0, -1, 0},
                    90,
                    (Vec3){0, 0, 0}),
            (Object **)&scene->camera);
    objectAdd(
            (Object *)newCylinder(
                    (Vec3){1, 3, 5},
                    Normalize((Vec3){1, 1, 1}),
                    1.5,
                    2,
                    (Vec4){0, 255, 255, 0},
                    (Vec3){0, 0, 0},
                    cylinderColision),
            (Object **)&scene->objects);
	/*objectAdd(
			(Object *)newSphere(
					(Vec3){1, 3, 5},
					(Vec3){0, 0, 0},
					(Vec4){0, 255, 255, 0},
					(Vec3){0, 0, 0},
					1,
					sphereColision),
			(Object **)&scene->objects);*/
    objectAdd(
            (Object *)newLight(
                    (Vec3){2, 3, 1},
                    (Vec3){0, 0, 0},
                    (Vec4){0, 255, 255, 255},
                    (Vec3){0, 0, 0},
                    0.5,
                    POINT),
            (Object **)&scene->lights);
    objectAdd(
            (Object *)newLight(
                    (Vec3){0, 0, 0},
                    (Vec3){0, 0, 0},
                    (Vec4){0, 255, 255, 255},
                    (Vec3){0, 0, 0},
                    0.1,
                    AMBIENT),
            (Object **)&scene->lights);

    renderFrame();
	mlx_key_hook(scene->mlx->win, keyhook, scene->mlx);
	// mlx_loop_hook(scene->mlx->mlx, keyhook, NULL);
	mlx_loop(scene->mlx->mlx);
	return 0;
}