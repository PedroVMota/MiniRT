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
    if (updateData)
    {
        rayTrace->normal = normalCalc(closest, Add(rayTrace->o, Mul(rayTrace->d, ct)));
        rayTrace->ct = ct;
        rayTrace->HitPoint = Add(rayTrace->o, Mul(rayTrace->d, ct));
    }
    return closest;
}

void calc_combined(Vec4 *combined, int light_color, double brightness)
{
    combined->r += plusComponent(light_color, 16, brightness) / 255;
    combined->g += plusComponent(light_color, 8, brightness) / 255;
    combined->b += plusComponent(light_color, 0, brightness) / 255;
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

void diffusion(Vec4 *combined, Vec3 normal, Vec3 light, Light *src)
{
    double n_dot_l;
    double bright;

    n_dot_l = Dot(normal, light);
    if (n_dot_l > 0)
    {
        bright = src->intensity * n_dot_l /
                 (Length(normal) * Length(light));
        calc_combined(combined, src->color, bright);
    }
}

Vec4 calculateLighting(Vec3 p, Vec3 n, Vec3 v, double spec)
{
    Vec4 Combined;  // Combinação de cores
    double r_dot_v; // Reflexão da luz
    Light *light;   // Luz
    Vec3 p_v_l;     // Vetor da luz (ponto - luz)
    Vec3 reflected; // Reflexão da luz

    Combined = (Vec4){0, 0, 0};
    light = scene->lights;
    if (light == NULL)
        return Combined;
    while (light)
    {
        if (light->type == AMBIENT)
        {
            calc_combined(&Combined, light->color, light->intensity);
            break;
        }
        p_v_l = Sub(light->o, p);
        Ray localSimulation; // Simulação local
        localSimulation.o = p;
        localSimulation.d = Normalize(p_v_l);
        if (getClosestObject(&localSimulation, 1, 0.001, false))
        {
            light = (Light *)light->next;
            continue;
        }
        // Calculate diffuse light
        diffusion(&Combined, n, p_v_l, light);

        // Calculate specular light
        r_dot_v = to_reflect(light->o, n, v, &reflected);
        if (spec > 0 && r_dot_v > 0)
        {
            double light_intensity = light->intensity / (Length(p_v_l) * Length(p_v_l));
            double brightness = compute_refl((Vec3){light_intensity, r_dot_v, spec}, reflected, v);
            calc_combined(&Combined, light->color, brightness);
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
    return rgbGetter(r, g, b);
}

int RayColor(Ray rayTrace, int depth)
{
    // printf("Raycolor depth: %d\n", depth);
    int localColor = 0;
    if (depth < 1)
        return 0;
    Object *obj = getClosestObject(&rayTrace, INFINITY, 0, true);
    if (!obj)
        return 0;
    if (Dot(rayTrace.d, rayTrace.normal) > 0)
        rayTrace.normal = Mul(rayTrace.normal, -1);
    Vec4 objectColor = calculateLighting(rayTrace.HitPoint, rayTrace.normal, Mul(rayTrace.d, -1), obj->specular);
    localColor = computeColor(obj->color, objectColor);
    if(obj->reflection <= 0)
        return localColor;
    double reflection = obj->reflection;
    Vec3 reflected = Reflect(rayTrace.d, rayTrace.normal);
    Ray reflectedRay = (Ray){Add(rayTrace.HitPoint, Mul(reflected, 0.001)), reflected};
    int reflectedColor = RayColor(reflectedRay, depth - 1);
    localColor = rgbGetter(
        (int)(plusComponent(localColor, 16, 1 - reflection) + plusComponent(reflectedColor, 16, reflection)),
        (int)(plusComponent(localColor, 8, 1 - reflection) + plusComponent(reflectedColor, 8, reflection)),
        (int)(plusComponent(localColor, 0, 1 - reflection) + plusComponent(reflectedColor, 0, reflection)));

    return localColor;
}

void renderFrame()
{
    for (double y = scene->height / 2; y > -scene->height / 2; y--)
    {
        for (double x = -scene->width / 2; x < scene->width / 2; x++)
        {
            Ray ray = GetRayDir((scene->camera)->o, x, y);
            int color = RayColor(ray, 2);
            my_mlx_pixel_put(toCanvas(x, false), toCanvas(y, true), color);
        }
    }
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

void changeSelector(int keycode)
{
    static int selector = 0;

    if (keycode == SPACE)
    {
        selector++;
        if (selector == 3)
            selector = 0;
        printf("Changing Selector %d\n", selector);
    }
    if (selector == 0)
        selected = (Object *)scene->lights;
    if (selector == 1)
        selected = scene->objects;
    if (selector == 2)
        selected = (Object *)scene->camera;
}

int keyhook(int keycode)
{
    printf("keycode: %d\n", keycode);
    if (keycode == SPACE || selected == NULL)
        changeSelector(keycode);
    if (keycode == UP)
        selected->o.z += 1;
    if (keycode == DOWN)
        selected->o.z -= 1;
    if (keycode == LEFT)
        selected->o.x -= 1;
    if (keycode == RIGHT)
        selected->o.x += 1;
    if (keycode == W)
        selected->o.y += 1;
    if (keycode == S)
        selected->o.y -= 1;
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
    if (keycode == SPACE || keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT || keycode == W || keycode == S)
        renderFrame();
    return 0;
}

int main(void)
{
    scene = init_MainStruct(1000, 1000);
    if (!scene)
        return 1;

    objectAdd(
        (Object *)newCamera(
            (Vec3){0, 0, -5},
            (Vec3){0, 0, 0},
            53.3,
            (Vec3){0, 0, 0}),
        (Object **)&scene->camera);
    objectAdd((Object *)newSphere((Vec3){0, 0, 0}, (Vec3){0, 0, 0}, (Vec4){0, 255, 0}, (Vec3){0, 0, 0}, 1, sphereColision, 0.8, 32), (Object **)&scene->objects);
    // objectAdd((Object *)newSphere((Vec3){1, 0, 1}, (Vec3){0, 0, 0}, (Vec4){255, 0, 255}, (Vec3){0, 0, 0}, 1, sphereColision, 0, 32), (Object **)&scene->objects);
    objectAdd((Object *)newLight((Vec3){-1, 0, -5}, (Vec3){0, 2, 0}, (Vec4){0, 255, 0}, (Vec3){0, 0, 0}, 1, POINT), (Object **)&scene->lights);
    // objectAdd((Object *)newLight((Vec3){1, 0, -5}, (Vec3){0, 0, 0}, (Vec4){0, 255, 0}, (Vec3){0, 0, 0}, 0.5, POINT), (Object **)&scene->lights);
    // objectAdd((Object *)newLight((Vec3){1, 0, -5}, (Vec3){0, 0, 0}, (Vec4){255, 255, 255}, (Vec3){0, 0, 0}, 0.2, AMBIENT), (Object **)&scene->lights);
    objectAdd((Object *)newPlane((Vec3){0, -1, 0}, (Vec3){0, 1, 0}, (Vec4){255, 255, 255}, (Vec3){0, 0, 0}, 1, planeColision, 0, 0, 0), (Object **)&scene->objects);

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
