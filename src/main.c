/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/11 20:31:07 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

gscene	*g_scene = NULL;

int	compcolor(int obj_color, Vec4 objectColor)
{
	int	r;
	int	g;
	int	b;

	r = ((obj_color >> 16 & 255)) * objectColor.r;
	g = ((obj_color >> 8 & 255)) * objectColor.g;
	b = ((obj_color & 255)) * objectColor.b;
	return (newrgb(r, g, b));
}


int utils_ray_color(int lc, int refc, double reflection) {
    return newrgb((int)(mulcomp(lc, 16, 1 - reflection)
                + mulcomp(refc, 16, reflection)),
            (int)(mulcomp(lc, 8, 1 - reflection)
                + mulcomp(refc, 8, reflection)),
            (int)(mulcomp(lc, 0, 1 - reflection)
                + mulcomp(refc, 0, reflection)));
}

int	raycolor(Ray rayTrace, int depth)
{
	int		lc;
	Object	*obj;
	Vec3	reflected;
	Ray		refr;
	int		refc;

	if (rayTrace.d.z == 0)
		return 0;
	lc = 0;
	obj = intersections(&rayTrace, INFINITY, 0, true);
	if (!obj)
		return (0);
	if (dot(rayTrace.d, rayTrace.normal) > 0)
		rayTrace.normal = mul(rayTrace.normal, -1);
	lc = compcolor(obj->color, calcligh(rayTrace.HitPoint, \
		rayTrace.normal, rayTrace.d, obj->specular));
	if (obj->reflection <= 0 || obj->specular <= 0 || depth <= 0)
		return (lc);
	reflected = reflect(rayTrace.d, rayTrace.normal);
	refr = (Ray){add(rayTrace.HitPoint, mul(reflected, 0.001)),
		reflected};
	refc = raycolor(refr, depth - 1);
	lc = utils_ray_color(lc, refc, obj->reflection);
	return (lc);
}

#include <pthread.h>

#define NUM_THREADS 20

typedef struct {
    double start_y;
    double end_y;
} ThreadData;

void* renderFrameThread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    Ray ray;
    int color;

    for (double y = data->start_y; y > data->end_y; y--) {
        for (double x = -g_scene->width / 2; x < g_scene->width / 2; x++) {
            ray = getraydir((g_scene->camera)->o, x, y);
            color = raycolor(ray, g_scene->depth);
            my_mlx_pixel_put(tocanvas(x, false), tocanvas(y, true), color);
        }
    }

    return NULL;
}

void renderFrame(void) {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    double step = g_scene->height / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].start_y = g_scene->height / 2 - i * step;
        threadData[i].end_y = threadData[i].start_y - step;
        pthread_create(&threads[i], NULL, renderFrameThread, &threadData[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    mlx_put_image_to_window(g_scene->mlx->mlx, g_scene->mlx->win, g_scene->mlx->img, 0, 0);
    printf("\rDone.\n");
}

void	del(Object **lsg)
{
	if (!lsg)
		return ;
	if (!*lsg)
		return ;
	del(&(*lsg)->next);
	free(*lsg);
}

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
        selected = (Object *) g_scene->lights;
    if (selector == 1)
        selected = g_scene->objects;
    if(selector == 2)
        selected = (Object *)g_scene->camera;
}
int key_hook(int keycode)
{
	printf("keycode: %d\n", keycode);
    if(keycode == SPACE || selected == NULL)
        changeSelector(keycode);
    printf("selected %f\n", selected->o.y);
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
		mlx_clear_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_image(g_scene->mlx->mlx, g_scene->mlx->img);
		free(g_scene->mlx->mlx);
		free(g_scene->mlx);
		exit(0);
	}
    if(keycode == SPACE || keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT || keycode == W || keycode == S)
        renderFrame();
	return 0;
}

int	main(void)
{
	g_scene = init_main(1000, 1000, 1);
	if (!g_scene)
		return (1);
	objectadd((Object *)newCamera((Vec3){1, 1, -10}, (Vec3){0, 0, 1}, 53.3,
			(Vec3){0, 0, 0}), (Object **)&g_scene->camera);
	/*objectadd((Object *)newParaboloid((Vec3){0, 10, -50}, (Vec4){255, 0, 0}, 1, 1, 1, paraboloidCollision, 0, 32), (Object **)&g_scene->objects);
	objectadd((Object *)newPlane((Vec3){0, -55, 0}, (Vec3){0, 1, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 10, planecolision, 0.3, 4, 0),
		(Object **)&g_scene->objects);*/
		objectadd((Object *)newSphere((Vec3){-1, 0, 0}, (Vec3){0, 0, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 0.5, spherecolision, 0, 32),
        (Object **)&g_scene->objects);
	objectadd((Object *)newSphere((Vec3){0, 0, -14}, (Vec3){0, 0, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 0.5, spherecolision, 0, 32),
		(Object **)&g_scene->objects);
	objectadd((Object *)newCylinder((Vec3){0, 0, 0}, (Vec3){0, 1, 0}, 1, 3,
			(Vec4){255, 255, 255}, (Vec3){0, 0, 0}, cylindercolision, 0, 32),
		(Object **)&g_scene->objects);
	objectadd((Object *)newSphere((Vec3){1, 0, 0}, (Vec3){0, 0, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 0.5, spherecolision, 0, 32),
		(Object **)&g_scene->objects);
	objectadd((Object *)newSphere((Vec3){0, 0, 0}, (Vec3){0, 0, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 0.5, spherecolision, 0, 32),
		(Object **)&g_scene->objects);
	objectadd((Object *)newSphere((Vec3){0, 3, 0}, (Vec3){0, 0, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 0.5, spherecolision, 0, 32),
		(Object **)&g_scene->objects);
	objectadd((Object *)newLight((Vec3){1, -2, -2}, (Vec3){0, 0, 0}, (Vec4){255,
			0, 0}, (Vec3){0, 0, 0}, 0.2, AMBIENT), (Object **)&g_scene->lights);
	objectadd((Object *)newLight((Vec3){1, 2, -2}, (Vec3){0, 0, 0}, (Vec4){255,
			255, 0}, (Vec3){0, 0, 0}, 1, POINT), (Object **)&g_scene->lights);
	objectadd((Object *)newLight((Vec3){-1, 2, -2}, (Vec3){0, 0, 0}, (Vec4){0,
			0, 255}, (Vec3){0, 0, 0}, 1, POINT), (Object **)&g_scene->lights);
	objectadd((Object *)newLight((Vec3){-1, -2, -2}, (Vec3){0, 0, 0},
			(Vec4){255, 255, 0}, (Vec3){0, 0, 0}, 0.2, AMBIENT),
		(Object **)&g_scene->lights);
	objectadd((Object *)newPlane((Vec3){0, -1, 0}, (Vec3){0, 1, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 10, planecolision, 0, 0.2, 0),
		(Object **)&g_scene->objects);
	objectadd((Object *)newPlane((Vec3){-2, 0, 0}, (Vec3){1, 0, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 10, planecolision, 0.5, 0, 0),
		(Object **)&g_scene->objects);
	objectadd((Object *)newPlane((Vec3){2, 0, 0}, (Vec3){1, 0, 0}, (Vec4){255,
			255, 255}, (Vec3){0, 0, 0}, 10, planecolision, 0, 0, 0),
		(Object **)&g_scene->objects);
	if (!g_scene->objects || !g_scene->lights || !g_scene->camera)
		return (1);
	mlx_key_hook(g_scene->mlx->win, key_hook, NULL);
	renderFrame();
	mlx_loop(g_scene->mlx->mlx);
	return (0);
}
