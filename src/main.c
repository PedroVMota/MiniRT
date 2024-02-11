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

#include <StandarLibrarys.h>

gscene	*g_scene = NULL;
void ShowGeneralInfo(void);

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

void ShowSphere(Sphere *sphere);

int	raycolor(Ray rayTrace, int depth)
{
	int		lc;
	Object	*obj;
	Vec3	reflected;
	Ray		refr;
	int		refc;
	static int i = 0;
	lc = 0;

	if(i == 0)
		ShowSphere((Sphere *)g_scene->objects);
	i++;
	obj = intersections(&rayTrace, INFINITY, 0, true);
	if (!obj)
		return (0);
	if (dot(rayTrace.d, rayTrace.normal) > 0)
		rayTrace.normal = mul(rayTrace.normal, -1);
	lc = compcolor(obj->color, calcligh(rayTrace.HitPoint, \
		rayTrace.normal, rayTrace.d, obj->specular));
	// if (obj->reflection <= 0 || obj->specular <= 0 || depth <= 0)
	// 	return (lc);
	// reflected = reflect(rayTrace.d, rayTrace.normal);
	// refr = (Ray){.o = add(rayTrace.HitPoint, mul(reflected, 0.001)), .d =
	// 	reflected};
	// refc = raycolor(refr, depth - 1);
	// lc = newrgb((int)(mulcomp(lc, 16, 1 - obj->reflection)
	// 			+ mulcomp(refc, 16, obj->reflection)),
	// 		(int)(mulcomp(lc, 8, 1 - obj->reflection)
	// 			+ mulcomp(refc, 8, obj->reflection)),
	// 		(int)(mulcomp(lc, 0, 1 - obj->reflection)
	// 			+ mulcomp(refc, 0, obj->reflection)));
	return (lc);
}

void	renderFrame(void)
{
	clock_t	start;
	Ray		ray;
	int		color;

	(void)color;
	start = clock();
	for (double y = g_scene->height / 2; y > -g_scene->height / 2; y--)
	{
		for (double x = -g_scene->width / 2; x < g_scene->width / 2; x++)
		{
			ray = getraydir((g_scene->camera)->o, x, y);
			color = raycolor(ray, g_scene->depth);
			// ShowGeneralInfo();
			my_mlx_pixel_put(tocanvas(x, false), tocanvas(y, true), color);
		}
	}
	printf("Time to render: %f\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	mlx_put_image_to_window(g_scene->mlx->mlx, g_scene->mlx->win, g_scene->mlx->img,
		0, 0);
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

// int key_hook(int keycode)
// {
// 	printf("Keycode: %d\n", keycode);
// 	if (keycode == ESC)
// 	{
// 		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
// 		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
// 		mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
// 		// mlx_destroy_display(scene->mlx->mlx);
// 		free(scene->mlx->mlx);
// 		free(scene->mlx);
// 		del((Object **)&scene->objects);
// 		del((Object **)&scene->lights);
// 		del((Object **)&scene->camera);
// 		del((Object **)&scene->am);
// 		del(NULL);
// 		free(scene);
// 		exit(0);
// 	}
// 	return (0);
// }
// mlx_key_hook(scene->mlx->win, key_hook, NULL);

int sysclean(int res)
{
	del((Object **)&g_scene->lights);
	del((Object **)&g_scene->objects);
	del((Object **)&g_scene->camera);
	del((Object **)&g_scene->am);
	printf("System Call Exit...\n");
	return res;
}



int	main(int argc, char **argv)
{
	if(argc != 2)
		return (1);
	g_scene = init_main(500, 500, 0);
	if (!g_scene)
		return sysclean(1);
	if ((!parse(argv[1])))
		return sysclean(1);
	if (!g_scene->am|| !g_scene->camera || g_scene->error)
		return sysclean(1);
	if(!initialize_mlx(g_scene))
		return sysclean(1);
	renderFrame();
	mlx_loop(g_scene->mlx->mlx);
	return (0);
}
