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

static void setdata(Object *obj, double ct, Ray *ray)
{
	ray->normal = normalcalc(obj, add(ray->o, mul(ray->d, ct)));
	ray->ct = ct;
	ray->HitPoint = add(ray->o, mul(ray->d, ct));
}

Object *getClosestObject(Ray *rt, double md, double d, bool set)
{
	double ct = INFINITY;
	Object *closest = NULL;

	ct = INFINITY;
	closest = NULL;
	for (Object *lst = scene->objects; lst; lst = lst->next)
	{
		rt->val = lst->colision(lst, *rt);
		if ((rt->val.t0 > d && rt->val.t0 < md) && rt->val.t0 < ct)
		{
			closest = lst;
			ct = rt->val.t0;
		}
		else if ((rt->val.t1 > d && rt->val.t1 < md) && rt->val.t1 < ct)
		{
			closest = lst;
			ct = rt->val.t1;
		}
	}
	if (set)
		setdata(closest, ct, rt);
	return closest;
}



int skip(Light **l)
{
	*l = (Light *)(*l)->next;
	return 1;
}

Vec4 limit(Vec4 v)
{
	if(v.r > 1)
		v.r = 1;
	if(v.g > 1)
		v.g = 1;
	if(v.b > 1)
		v.b = 1;
	if(v.r < 0)
		v.r = 0;
	if(v.g < 0)
		v.g = 0;
	if(v.b < 0)
		v.b = 0;
	return (v);
}


Vec4 calculateLighting(Vec3 p, Vec3 n, Vec3 v, double spec)
{
	Vec4 Combined;
	double r_dot_v;
	Light *light;
	Vec3 p_v_l;
	Vec3 reflected;

	Combined = (Vec4){0, 0, 0};
	light = scene->lights;
	calc_combined(&Combined, scene->am->color, scene->am->intensity);
	if (light == NULL)
		return Combined;
	while (light)
	{
		p_v_l = sub(light->o, p);
		if (shadow(p, normalize(p_v_l), 0.001, 1) && skip(&light))
			continue;
		diffusion(&Combined, n, p_v_l, light);
		r_dot_v = to_reflect(light->o, n, v, &reflected);
		if (spec > 0 && r_dot_v > 0)
		{
			double i = light->intensity / (length(p_v_l) * length(p_v_l));
			double b = refl((Vec3){i, r_dot_v, spec}, reflected, v);
			calc_combined(&Combined, light->color, b);
		}
		light = (Light *)light->next;
	}
	return (limit(Combined));
}

Vec4 checkerboardColor(Vec3 point, Vec4 color1, Vec4 color2, double size)
{
	if ((int)(floor(point.x / size) + floor(point.y / size) + floor(point.z / size)) % 2 == 0)
		return color1;
	else
		return color2;
}

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
	Object *obj = getClosestObject(&rayTrace, INFINITY, 0, true);
	if (!obj)
		return 0;
	if (dot(rayTrace.d, rayTrace.normal) > 0)
		rayTrace.normal = mul(rayTrace.normal, -1);
	Vec4 objectColor = calculateLighting(rayTrace.HitPoint, rayTrace.normal,rayTrace.d, obj->specular);
	localColor = computeColor(obj->color, objectColor);
	if(obj->reflection <= 0 || obj->specular <= 0 || depth <= 0)
		return localColor;
	double reflection = obj->reflection;
	Vec3 reflected = reflect(rayTrace.d, rayTrace.normal);
	Ray reflectedRay = (Ray){add(rayTrace.HitPoint, mul(reflected, 0.001)), reflected};
	int reflectedColor = RayColor(reflectedRay, depth - 1);
	localColor = newrgb(
		(int)(mulcomp(localColor, 16, 1 - reflection) + mulcomp(reflectedColor, 16, reflection)),
		(int)(mulcomp(localColor, 8, 1 - reflection) + mulcomp(reflectedColor, 8, reflection)),
		(int)(mulcomp(localColor, 0, 1 - reflection) + mulcomp(reflectedColor, 0, reflection)));
	return localColor;
}

void renderFrame()
{
	printf("%sRendering Settings:%s\n", MAGB, RESET);
	printf("Resolution: %dx%d\n", scene->width, scene->height);
	printf("Camera: %f\n", scene->camera->fov);
	printf("Reflection Depth: %d\n", scene->depth);

	clock_t start = clock();
	for (double y = scene->height / 2; y > -scene->height / 2; y--)
	{
		for (double x = -scene->width / 2; x < scene->width / 2; x++)
		{
			Ray ray = getraydir((scene->camera)->o, x, y);
			int color = RayColor(ray, scene->depth);
			my_mlx_pixel_put(tocanvas(x, false), tocanvas(y, true), color);
			//printf("\rRendering frame... %d%%", (int)((scene->height / 2 - y) / scene->height * 100));
		}
		//printf("\rRendering frame... %d%%", (int)((scene->height / 2 - y) / scene->height * 100));
	}
	printf("Time to render: %f\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	mlx_put_image_to_window(scene->mlx->mlx, scene->mlx->win, scene->mlx->img, 0, 0);
	printf("\rDone.\n");
}

Object *selected = NULL;

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
#elif __linux__
#define SPACE 32    // 49
#define UP 65362    // 126
#define DOWN 65364  // 125
#define LEFT 65361  // 123
#define RIGHT 65363 // 124
#define ESC 65307   // 53
#define W 119       // 13
#define A 97        // 0
#define S 115       // 1 D // 2
#define D 100
#endif

void del(Object **lsg)
{
	if(!lsg)
		return;
	if(!*lsg)
		return;
	del(&(*lsg)->next);
	free(*lsg);
}

int key_hook(int keycode)
{
	printf("Keycode: %d\n", keycode);
	if (keycode == ESC)
	{
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
		// mlx_destroy_display(scene->mlx->mlx);
		free(scene->mlx->mlx);
		free(scene->mlx);
		del((Object **)&scene->objects);
		del((Object **)&scene->lights);
		del((Object **)&scene->camera);
		del((Object **)&scene->am);
		del(NULL);
		free(scene);
		exit(0);
	}
	return 0;
}


int main(void)
{
	scene = init_main(500, 500, 2);
	if (!scene)
		return 1;
	objectadd(
		(Object *)newCamera(
			(Vec3){0, 0, -10},
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
	mlx_key_hook(scene->mlx->win, key_hook, NULL);
	renderFrame();
	mlx_loop(scene->mlx->mlx);

	return 0;
}

