/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/12 21:44:56 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"
#include <pthread.h>


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

int	utils_ray_color(int lc, int refc, double reflection)
{
	return (
		newrgb((int)(
			mulcomp(lc, 16, 1 - reflection) \
			+ mulcomp(refc, 16, reflection)), \
			(int)(mulcomp(lc, 8, 1 - reflection) \
			+ mulcomp(refc, 8, reflection)), \
			(int)(mulcomp(lc, 0, 1 - reflection) \
				+ mulcomp(refc, 0, reflection)))
);
}


int	raycolor(Ray rayTrace, int depth)
{
    int localColor = 0;
    Object *obj = intersections(&rayTrace, INFINITY, 0, true);
    if (!obj)
        return 0;
    if (dot(rayTrace.d, rayTrace.normal) > 0)
        rayTrace.normal = mul(rayTrace.normal, -1);
    Vec4 objectColor = calcligh(rayTrace._hit, rayTrace.normal, rayTrace.d, obj->specular);
    localColor = compcolor(obj->color, objectColor);
    if(obj->reflection <= 0 || obj->specular <= 0 || depth <= 0)
		return localColor;
    double reflection = obj->reflection;
    Vec3 reflected = reflect(rayTrace.d, rayTrace.normal);
    Ray reflectedRay = (Ray){add(rayTrace._hit, mul(reflected, 0.001)), reflected};
    int reflectedColor = raycolor(reflectedRay, depth - 1);
    localColor = newrgb(
        (int)(mulcomp(localColor, 16, 1 - reflection) + mulcomp(reflectedColor, 16, reflection)),
        (int)(mulcomp(localColor, 8, 1 - reflection) + mulcomp(reflectedColor, 8, reflection)),
        (int)(mulcomp(localColor, 0, 1 - reflection) + mulcomp(reflectedColor, 0, reflection)));
    return localColor;
}

#define NUM_THREADS 12


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
	if(g_scene->props)
		delprops(&g_scene->props);
	if(g_scene->lights)
		del((Object **)&g_scene->lights);
	if(g_scene->objects)
		del((Object **)&g_scene->objects);
	if(g_scene->camera)
		del((Object **)&g_scene->camera);
	if(g_scene->am)
		del((Object **)&g_scene->am);
	if(g_scene->mlx)
	{
		mlx_clear_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_image(g_scene->mlx->mlx, g_scene->mlx->img);
		free(g_scene->mlx->mlx);
		free(g_scene->mlx);
	}
	free(g_scene);
	if(res != -1)
		exit(res);
	return (res);
}

int key_hook(int keycode, void *param)
{
	printf("Keycode: %d\n", keycode);
	if (keycode == 65307)
		sysclean(0);
	if (keycode == 65361)
		g_scene->lights->o.x -= 0.5;
	if (keycode == 65363)
		g_scene->lights->o.x += 0.5;
	if (keycode == 65362)
		g_scene->lights->o.y += 0.5;
	if (keycode == 65364)
		g_scene->lights->o.y -= 0.5;
	if (keycode == 65360)
		g_scene->lights->o.z += 0.5;
	if (keycode == 65367)
		g_scene->lights->o.z -= 0.5;
	renderFrame();
	return (0);
}

int	main(int argc, char **argv)
{
	g_scene = init_main(1000, 1000, 9);
	if (!g_scene)
		return (sysclean(1));
	if ((!parse(argv[1])))
		return (sysclean(1));
	if (!g_scene->am || !g_scene->camera || g_scene->error)
		return (sysclean(1));
	if (!initialize_mlx(g_scene))
		return (sysclean(1));
	renderFrame();
	mlx_loop(g_scene->mlx->mlx);
	return (0);
}
