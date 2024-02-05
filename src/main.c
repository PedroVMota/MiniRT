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

void blend(Vec4 *a, int lightColor, double brightness)
{
    a->r += plusComponent(lightColor, 16, brightness) / 255;
    a->g += plusComponent(lightColor, 8, brightness) / 255;
    a->b += plusComponent(lightColor, 0, brightness) / 255;
}

// p = HITPOINT
// n = NORMAL
// v = VIEW
// d = DEPTH

Vec3 reflect_ray(Vec3 light, Vec3 normal)
{
    Vec3 result;

    double dot_product = normal.x * light.x + normal.y * light.y + normal.z * light.z;

    result.x = light.x - 2 * normal.x * dot_product;
    result.y = light.y - 2 * normal.y * dot_product;
    result.z = light.z - 2 * normal.z * dot_product;

    return result;
}

double to_reflect(Vec3 light, Vec3 n, Vec3 vect, Vec3 *reflected)
{
    double r_dot_v;

    *reflected = reflect_ray(light, n);
    r_dot_v = reflected->x * vect.x + reflected->y * vect.y + reflected->z * vect.z;

    return r_dot_v;
}


double compute_refl(Vec3 data, Vec3 reflected, Vec3 vect)
{
    double bright;
    double length_reflected = sqrt(reflected.x * reflected.x + reflected.y * reflected.y + reflected.z * reflected.z);
    double length_vect = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);

    bright = data.x * pow(data.y / (length_reflected * length_vect), data.z);

    return bright;
}


Vec4 calculateLighting(Vec3 p, Vec3 n, Vec3 v, double spec)
{
    Vec4 Combined; // Combinação de cores
    double r_dot_v; // Reflexão da luz
    Light *light; // Luz 
    Vec3 p_v_l;  // Vetor da luz (ponto - luz)
    Vec3 reflected; // Reflexão da luz

    Combined = (Vec4){0, 0, 0};
    light = scene->lights;
    if(light == NULL)
        return Combined;
    while (light)
    {
        if(light->type == AMBIENT)
        {
            blend(&Combined, light->color, light->intensity);
            break;
        }
        p_v_l = Sub(light->o, p);
        Ray localSimulation; // Simulação local
        localSimulation.o = p;
        localSimulation.d = Normalize(p_v_l);
        if(getClosestObject(&localSimulation, 1, 0.001, false))
        {
            light = (Light *)light->next;
            continue;
        }
        double n_dot_l = Dot(n, Normalize(p_v_l));
        if (n_dot_l > 0.001)
        {
            double brithness = light->intensity * n_dot_l / (Length(n) * Length(p_v_l));
            blend(&Combined, light->color, brithness);
        }

        // Calculate specular light
        r_dot_v = to_reflect(light->o, n, v, &reflected);
        if (spec > 0 && r_dot_v > 0)
        {
            double brightness = compute_refl((Vec3){light->intensity, r_dot_v, spec}, reflected, v);
            blend(&Combined, light->color, brightness);
        }
        light = (Light *)light->next;
    }
    if (Combined.r >= 1)
        Combined.r = 1;
    if (Combined.g >= 1)
        Combined.g = 1;
    if (Combined.b >= 1)
        Combined.b = 1;
    return Combined;
}

Vec4 checkerboardColor(Vec3 point, Vec4 color1, Vec4 color2, double size) {
    if ((int)(floor(point.x / size) + floor(point.y / size) + floor(point.z / size)) % 2 == 0)
        return color1;
    else
        return color2;
}


 
int RayColor(Ray rayTrace, int depth)
{
    int localColor = 0;
    if (depth < 1)
        return 0;
    Object *obj = getClosestObject(&rayTrace, INFINITY, 0, true);
    if (!obj)
        return 0;
    Vec4 objectColor = calculateLighting(rayTrace.HitPoint, rayTrace.normal, rayTrace.d, depth);

    int r = ((obj->color >> 16 & 255)) * objectColor.r;
    int g = ((obj->color >> 8 & 255)) * objectColor.g;
    int b = ((obj->color & 255)) * objectColor.b ;
    

    //returning objectColor

    // return ((int)(round(objectColor.r * 255)) << 16) | ((int)(round(objectColor.g * 255)) << 8) | (int)(round(objectColor.b * 255));
    return rgbGetter(r, g, b);
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
			int color = RayColor(ray, 200);
            // printf("Color: %d\n", color);
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
#elif __linux__
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
        if (selector == 3)
            selector = 0;
        printf("Changing Selector %d\n", selector);
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
		selected->o.z += 2;
	if (keycode == DOWN)
        selected->o.z -= 2;
	if (keycode == LEFT)
        selected->o.x -= 2;
	if (keycode == RIGHT)
        selected->o.x += 2;
	if (keycode == W)
        selected->o.y += 2;
	if (keycode == S)
        selected->o.y -= 2;
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

// int main(void)
// {
// 	scene = init_MainStruct(250, 250);
//     if(!scene)
//         return 1;

//     objectAdd(
//             (Object *)newCamera(
//                     (Vec3){0, 0, -200},
//                     (Vec3){0, -1, 0},
//                     90,
//                     (Vec3){0, 0, 0}),
//             (Object **)&scene->camera);
//    objectAdd(
//             (Object *)newPlane(
//                     (Vec3){0, -1, 0},
//                     (Vec3){0, 1, 0},
//                     (Vec4){0, 255, 255, 255},
//                     (Vec3){0, 0, 0},
//                     1,
//                     planeColision, 0.9, 1),
//             (Object **)&scene->objects);
//     objectAdd(
// 			(Object *)newSphere(
// 					(Vec3){0, 0, -6},
// 					(Vec3){0, 0, 0},
// 					(Vec4){0, 255, 255, 0},
// 					(Vec3){0, 0, 0},
// 					1,
// 					sphereColision, 0.7),
// 			(Object **)&scene->objects);
//     objectAdd(
//     (Object *)newPyramid(
//         (Vec3){0, 0, -5}, // posição da pirâmide
//         (Vec3){1, 1, 0}, // direção da pirâmide (não usada neste caso)
//         2, // largura da base da pirâmide
//         5, // altura da pirâmide
//         (Vec4){255, 0, 0, 255}, // cor da pirâmide
//         23 * M_PI / 180, // rotação da pirâmide (não usada neste caso)
//         pyramidCollision, 0.6),
//     (Object **)&scene->objects);
//     /*objectAdd(
//             (Object *)newCylinder(
//                     (Vec3){2, 0, -5},
//                     Normalize((Vec3){0, 1, 0}),
//                     1.5,
//                     7,
//                     (Vec4){0, 255, 255, 0},
//                     (Vec3){0, 0, 0},
//                     cylinderColision, 0.8),
//             (Object **)&scene->objects);
//     objectAdd(
// 			(Object *)newSphere(
// 					(Vec3){0, 0, 1},
// 					(Vec3){0, 0, 0},
// 					(Vec4){0, 255, 0, 0},
// 					(Vec3){0, 0, 0},
// 					1,
// 					sphereColision, 0.5),
// 			(Object **)&scene->objects);*/
//     objectAdd(
// 			(Object *)newSphere(
// 					(Vec3){-5, 0, -190},
// 					(Vec3){0, 0, 0},
// 					(Vec4){0, 0, 255, 0},
// 					(Vec3){0, 0, 0},
// 					1,
// 					sphereColision, 0.4),
// 			(Object **)&scene->objects);
//     objectAdd(
//             (Object *)newLight(
//                     (Vec3){-5, 3, -190},
//                     (Vec3){0, 0, 0},
//                     (Vec4){0, 0, 0, 255},
//                     (Vec3){0, 0, 0},
//                     0.9,
//                     POINT),
//             (Object **)&scene->lights);
//     objectAdd(
//             (Object *)newLight(
//                     (Vec3){0, 3, -190},
//                     (Vec3){0, 0, 0},
//                     (Vec4){0, 255, 0, 0},
//                     (Vec3){0, 0, 0},
//                     0.9,
//                     POINT),
//             (Object **)&scene->lights);
//     objectAdd(
//             (Object *)newLight(
//                     (Vec3){5, 3, -190},
//                     (Vec3){0, 0, 0},
//                     (Vec4){0, 0, 255, 0},
//                     (Vec3){0, 0, 0},
//                     0.9,
//                     POINT),
//             (Object **)&scene->lights);
// 	objectAdd(
//     (Object *)newLight(
//         (Vec3){0, 0.0, 0},  // Direction of the directional light
//         (Vec3){0, 0, 0},
//         (Vec4){0, 255, 255, 255},
//         (Vec3){0, 0, 0},
//         0.2,  // Intensity of the directional light
//         POINT),  // Type of the light
//     (Object **)&scene->lights);

//     renderFrame();
// 	mlx_key_hook(scene->mlx->win, keyhook, scene->mlx);
// 	// mlx_loop_hook(scene->mlx->mlx, keyhook, NULL);
// 	mlx_loop(scene->mlx->mlx);
// 	return 0;
// }

int main(void)
{
	scene = init_MainStruct(250, 250);
    if(!scene)
        return 1;

    objectAdd(
            (Object *)newCamera(
                    (Vec3){0, 0, -5},
                    (Vec3){0, 0, 0},
                    53.3,
                    (Vec3){0, 0, 0}),
            (Object **)&scene->camera);
    objectAdd((Object *)newSphere((Vec3){-1,0,1}, (Vec3){0,0,0}, (Vec4){100,255,0}, (Vec3){0,0,0}, 1, sphereColision, 0.8), (Object **)&scene->objects);
    objectAdd((Object *)newSphere((Vec3){1,0,1}, (Vec3){0,0,0}, (Vec4){255,255,255}, (Vec3){0,0,0}, 1, sphereColision, 0.8), (Object **)&scene->objects);
    objectAdd((Object *)newLight((Vec3){0,2,-2}, (Vec3){0,2,0}, (Vec4){255,0,255}, (Vec3){0,0,0}, 1, POINT), (Object **)&scene->lights);
    objectAdd((Object *)newLight((Vec3){0,0,-2}, (Vec3){0,0,0}, (Vec4){255,255,255}, (Vec3){0,0,0}, 0.5, AMBIENT), (Object **)&scene->lights);
    objectAdd((Object *)newPlane((Vec3){0,-1,0}, (Vec3){0,1,0}, (Vec4){255,255,255}, (Vec3){0,0,0}, 1, planeColision, 0, 0), (Object **)&scene->objects);
    
  

    renderFrame();
	mlx_key_hook(scene->mlx->win, keyhook, scene->mlx);
	// mlx_loop_hook(scene->mlx->mlx, keyhook, NULL);
	mlx_loop(scene->mlx->mlx);
	return 0;
}

/* 

    UPDATES:


        All the colors object are now in format int:

        Functions Created:
            -> int rgbGetter(int r, int g, int b)                                   mlx/utils.c
            -> double plusComponent(int color, int shifting, double intensity)      mlx/utils.c
            -> int convertLightColor(int color, double intensity)                   mlx/utils.c
            -> void blend(Vec4 *a, int lightColor, double brightness)               main.c

        Functions Updated:
            -> newObject(size_t ModelType, Vec3 o, Vec3 d, Vec4 color, Vec3 theta)  Objects/Create.c


        Functions Updated:
            -> Vec4 RayColor(Ray rayTrace, int depth)                               main.c
            -> Vec4 calculateLighting(Vec3 p, Vec3 n, Vec3 v, double depth)         main.c
            -> Vec4 RayColor(Ray rayTrace, int depth

        Reason:
            Losing information. The colors are now in int format, so we can use the bitwise operations to get the colors and the intensity of the light.
            ITS MOR EASY TO WORK WITH INTS THAN WITH VECTORS
*/