/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/29 18:51:19 by pedro            ###   ########.fr       */
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

Vec3 normalCalc(Object *obj, Vec3 p)
{
	Vec3 normal;
	normal = (Vec3){0, 0, 0};
	if (!obj)
		return normal;
	if (obj->type == SPHERE)
	{
		normal = Sub(p, (obj)->o);
		normal = Normalize(normal);
	}
	else if (obj->type == PLANE)
		normal = ((Plane *)obj)->d;
	return normal;
}

bool isObjectMiddle(Vec3 intersection, Light *light, double maxDistance, double minDistance)
{
	Ray shadowRay;
	shadowRay.o = intersection;
	shadowRay.d = Sub(light->o, intersection);
    double ct = INFINITY;
    Object *object = NULL;

	Object *lst = scene->objects;
	while (lst)
	{
		shadowRay.val = lst->colision(lst, shadowRay);
		if ((shadowRay.val.t0 > minDistance && shadowRay.val.t0 < maxDistance) && shadowRay.val.t0 < ct){
            ct = shadowRay.val.t0;
            object = lst;
        }
		if ((shadowRay.val.t1 > minDistance && shadowRay.val.t1 < maxDistance)&& shadowRay.val.t1 < ct)
        {
            ct = shadowRay.val.t1;
            object = lst;
        }
		lst = lst->next;
	}
    if(object)
         return true;
	return false;
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
		else if ((rayTrace->val.t1 > minDistance && rayTrace->val.t1 < maxDistance) && rayTrace->val.t1 < ct)
		{
			closest = lst;
			ct = rayTrace->val.t1;
		}
	}

	rayTrace->normal = normalCalc(closest, Add(rayTrace->o, Mul(rayTrace->d, ct)));
	rayTrace->ct = ct;
	rayTrace->HitPoint = Add(rayTrace->o, Mul(rayTrace->d, ct));
	return closest;
}

float calculateLighting(Vec3 point, Vec3 normal, Vec3 Hitpoint)
{
	Light *l = scene->lights;
	if (!l)
		return 0;
	double intensity = 0;
	double length_n = Length(normal); // Corrected typo
	Vec3 vec_l;
	Light *cur;

	while (l)
	{
		cur = l;
		if (cur->type == AMBIENT)
			intensity += cur->intensity;
		else
		{
			vec_l = Sub(l->o, Hitpoint);
			vec_l = Normalize(vec_l);
			if (isObjectMiddle(Hitpoint, cur, 1, 0.001))
			{
				l = (Light *)l->next;
				continue;
			}
			double n_dot_l = Dot(normal, vec_l);
			if (n_dot_l > 0)
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
	Object *obj = getClosestObject(&rayTrace, INFINITY, 0);
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
        if (selector == 2) {
            selector = 0;
            printf("Restructuring selector the value to 0\n");
        }
    }
    if (selector == 0)
        selected = (Object *) scene->lights;
    if (selector == 1)
        selected = scene->objects;
}
int keyhook(int keycode)
{
	printf("keycode: %d\n", keycode);
    if(keycode == SPACE || selected == NULL)
        changeSelector(keycode);
	if (keycode == UP)
	{
		selected->o.z += 0.1;
		renderFrame();
	}
	if (keycode == DOWN)
	{
        selected->o.z -= 0.1;
		renderFrame();
	}
	if (keycode == LEFT)
	{
        selected->o.x -= 0.1;
		renderFrame();
	}
	if (keycode == RIGHT)
	{
        selected->o.x += 0.1;
		renderFrame();
	}
	if (keycode == W)
	{
        selected->o.y += 0.1;
		renderFrame();
	}
	if (keycode == S)
	{
        selected->o.y -= 0.1;
		renderFrame();
	}
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
			(Vec3){0, 2, 0},
			(Vec3){0, 0, 1},
			90,
			(Vec3){0, 0, 0}),
		(Object **)&scene->camera);

	// objectAdd(
	// 	(Object *)newPlane(
	// 		(Vec3){-5, 0, 0},
	// 		(Vec3){-1, 0, 0},
	// 		(Vec4){0, 0, 255, 0},
	// 		(Vec3){0, 0, 0},
	// 		1,
	// 		planeColision),
	// 	(Object **)&scene->objects);

	// // Box Plane | - |

    objectAdd(
            (Object *)newPlane(
                    (Vec3){0, 10, 0},
                    (Vec3){0, 1, 0},
                    (Vec4){0, 255, 0, 0},
                    (Vec3){0, 0, 0},
                    1,
                    planeColision),
            (Object **)&scene->objects);

     objectAdd(
     	(Object *)newPlane(
     		(Vec3){0, -1, 0},
     		(Vec3){0, 1, 0},
     		(Vec4){0, 255, 0, 0},
     		(Vec3){0, 0, 0},
	 		1,
	 		planeColision),
	 	(Object **)&scene->objects);





	// Vertical Plane on -10 and 19


	//3 sphere 1 on -3,0,5 red 1 on 0,-1,3 green 1 on 3,0,5 blue
	objectAdd(
		(Object *)newSphere(
			(Vec3){-2, 0, 5},
			(Vec3){0, 0, 0},
			(Vec4){0, 255, 0, 0},
			(Vec3){0, 0, 0},
			1,
			sphereColision),
		(Object **)&scene->objects);

    objectAdd(
            (Object *)newSphere(
                    (Vec3){2, 0, 5},
                    (Vec3){0, 0, 0},
                    (Vec4){0, 255, 255, 0},
                    (Vec3){0, 0, 0},
                    1,
                    sphereColision),
            (Object **)&scene->objects);


    objectAdd(
            (Object *)newSphere(
                    (Vec3){0, 0, 7},
                    (Vec3){0, 0, 0},
                    (Vec4){0, 255, 255, 255},
                    (Vec3){0, 0, 0},
                    1,
                    sphereColision),
            (Object **)&scene->objects);

    objectAdd(
            (Object *)newSphere(
                    (Vec3){0, 0, 3},
                    (Vec3){0, 0, 0},
                    (Vec4){0, 255, 0, 255},
                    (Vec3){0, 0, 0},
                    1,
                    sphereColision),
            (Object **)&scene->objects);

	// Ambient Light
	objectAdd(
		(Object *)newLight(
			(Vec3){0, 1, 5},
			(Vec3){0, 0, 0},
			(Vec4){0, 255, 255, 255},
			(Vec3){0, 0, 0},
			1,
			POINT),
		(Object **)&scene->lights);
	objectAdd(
		(Object *)newLight(
			(Vec3){0, 0, 0},
			(Vec3){0, 0, 0},
			(Vec4){0, 255, 255, 255},
			(Vec3){0, 0, 0},
			0.2,
			AMBIENT),
		(Object **)&scene->lights);
	if (!scene->camera)
		return printf("No camera found\n"), 1;
	if (!initialize_mlx())
		return printf("Error initializing mlx\n"), 1;

	renderFrame();
	mlx_key_hook(scene->mlx->win, keyhook, scene->mlx);
	// mlx_loop_hook(scene->mlx->mlx, keyhook, NULL);
	mlx_loop(scene->mlx->mlx);
	return 0;
}