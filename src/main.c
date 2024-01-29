/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/28 20:36:40 by pedro            ###   ########.fr       */
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

	Object *lst = scene->objects;
	while(lst)
	{
		shadowRay.val = lst->colision(lst, shadowRay);
		if (shadowRay.val.t0 > minDistance && shadowRay.val.t0 < maxDistance)
			return true;
		if (shadowRay.val.t1 > minDistance && shadowRay.val.t1 < maxDistance)
			return true;
		lst = lst->next;
	}
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
	float intensity = 0;
	float length_n = Length(normal); // Corrected typo
	Vec3 vec_l;
	Light *cur;

	while (l)
	{
    	cur = l;
    	if (cur->type == AMBIENT)
        	intensity += cur->intensity;
   	 	else
    	{
        	if (cur->type == POINT)
			{
            	vec_l = Sub(cur->o, point);
			}
        	else
            	vec_l = cur->o;
			vec_l = Normalize(vec_l);

			if(isObjectMiddle(Hitpoint, cur, INFINITY, 0.001))
			{
				l = (Light *)l->next;
				continue;
			}
			double n_dot_l = Dot(vec_l, normal);
			if (n_dot_l > 0)
				intensity += cur->intensity * n_dot_l / (Length(vec_l) * length_n);

   		 }
    	l = (Light *)l->next;
		}	
	return intensity;
}

Vec4 RayColor(Ray rayTrace)
{
    // Vec4 CurrentColor = getBackgroundColor(rayTrace);
	Vec4 CurrentColor = (Vec4){0, 0, 0, 0};
    Object *obj = getClosestObject(&rayTrace, INFINITY, 0);
    if (!obj)
        return CurrentColor;
    Vec4 objectColor = obj->color;
	if(Dot(rayTrace.d, rayTrace.normal) > 0)
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
#else
#define UP 65362  //126
#define DOWN 65364  //125
#define LEFT 65361  //123
#define RIGHT 65363 //124
#define ESC 65307   //53
#define W 119    //13
#define A 97     //0
#define S 115    //1 D // 2
#define D 100	
#endif

int keyhook(int keycode)
{
	printf("keycode: %d\n", keycode);
	if (keycode == UP)
	{
		scene->lights->o.z += 0.1;
		renderFrame();
	}
	if (keycode == DOWN)
	{
		scene->lights->o.z -= 0.1;
		renderFrame();
	}
	if (keycode == LEFT)
	{
		scene->lights->o.x -= 0.1;
		renderFrame();
	}
	if (keycode == RIGHT)
	{
		scene->lights->o.x += 0.1;
		renderFrame();
	}
	if (keycode == W)
	{
		scene->lights->o.y += 0.1;
		renderFrame();
	}
	if (keycode == S)
	{
		scene->lights->o.y -= 0.1;
		renderFrame();
	}
	if (keycode == ESC)
	{
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
		mlx_destroy_display(scene->mlx->mlx);
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
            (Vec3){0, 0, -5},
            (Vec3){0, 0, 1},
            90,
            (Vec3){0, 0, 0}),
        (Object **)&scene->camera);

	objectAdd(
        (Object *)newPlane(
            (Vec3){-1, -3, 0}, // Posição do plano abaixo das esferas
            (Vec3){0, 1, 0}, // Direção do plano para cima
            (Vec4){255, 255, 255, 255},
            (Vec3){0, 0, 0},
            1,
            planeColision),
        (Object **)&scene->objects);

	objectAdd(
        (Object *)newPlane(
            (Vec3){0, 0, 10}, // Posição do plano abaixo das esferas
            (Vec3){0, 0, 1}, // Direção do plano para cima
            (Vec4){255, 255, 255, 255},
            (Vec3){0, 0, 0},
            1,
            planeColision),
        (Object **)&scene->objects);

	objectAdd(
        (Object *)newPlane(
            (Vec3){1, 3, 0}, // Posição do plano abaixo das esferas
            (Vec3){0, 1, 0}, // Direção do plano para cima
            (Vec4){255, 255, 255, 255},
            (Vec3){0, 0, 0},
            1,
            planeColision),
        (Object **)&scene->objects);

	objectAdd(
        (Object *)newPlane(
            (Vec3){-1, -3, 0}, // Posição do plano abaixo das esferas
            (Vec3){0, 1, 0}, // Direção do plano para cima
            (Vec4){255, 255, 255, 255},
            (Vec3){0, 0, 0},
            1,
            planeColision),
        (Object **)&scene->objects);

	objectAdd(
        (Object *)newPlane(
            (Vec3){5, 0, 0}, // Posição do plano abaixo das esferas
            (Vec3){1, 0, 0}, // Direção do plano para cima
            (Vec4){255, 255, 0, 0},
            (Vec3){0, 0, 0},
            1,
            planeColision),
        (Object **)&scene->objects);

	objectAdd(
        (Object *)newPlane(
            (Vec3){-5, 0, 0}, // Posição do plano abaixo das esferas
            (Vec3){1, 0, 0}, // Direção do plano para cima
            (Vec4){255, 0, 255, 0},
            (Vec3){0, 0, 0},
            1,
            planeColision),
        (Object **)&scene->objects);


	objectAdd(
        (Object *)newLight(
        (Vec3){0, 0, -5}, // Posição da luz acima das esferas
        (Vec3){0, 0, 0}, // Direção da luz para baixo
        (Vec4){255, 255, 255, 255},
           (Vec3){0, 0, 0},
        1,
        POINT),
    (Object **)&scene->lights);

	objectAdd(
        (Object *)newLight(
        (Vec3){0,0,0}, // Posição da luz acima das esferas
        (Vec3){0, 0, 0}, // Direção da luz para baixo
        (Vec4){255, 255, 255, 255},
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