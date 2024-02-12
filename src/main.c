/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/12 17:58:52 by pedro            ###   ########.fr       */
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
	lc = compcolor(obj->color, calcligh(rayTrace._hit, \
		rayTrace.normal, rayTrace.d, obj->specular));
	if (obj->reflection <= 0 || obj->specular <= 0 || depth <= 0)
		return (lc);
	reflected = reflect(rayTrace.d, rayTrace.normal);
	refr = (Ray){add(rayTrace._hit, mul(reflected, 0.001)),
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

int	sysclean(int res)
{
	del((Object **)&g_scene->lights);
	del((Object **)&g_scene->objects);
	del((Object **)&g_scene->camera);
	del((Object **)&g_scene->am);
	free(g_scene);
	return (res);
}

int	main(int argc, char **argv)
{
	g_scene = init_main(1000, 1000, 1);
	if (!g_scene)
		return (1);
	if (argc != 2)
		return (1);
	g_scene = init_main(1000, 500, 2);
	if (!g_scene)
		return (sysclean(1));
	if ((!parse(argv[1])))
		return (sysclean(1));
	if (!g_scene->am || !g_scene->camera || g_scene->error)
		return (sysclean(1));
	if (!initialize_mlx(g_scene))
		return (sysclean(1));
	// mlx_key_hook(g_scene->mlx->win, key_hook, NULL);
	renderFrame();
	mlx_loop(g_scene->mlx->mlx);
	return (0);
}
