/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/14 14:10:45 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

gscene	*g_scene = NULL;

int	sysclean(int res)
{
	if (g_scene->props)
		delprops(&g_scene->props);
	if (g_scene->lights)
		del((Object **)&g_scene->lights);
	if (g_scene->objects)
		del((Object **)&g_scene->objects);
	if (g_scene->camera)
		del((Object **)&g_scene->camera);
	if (g_scene->am)
		del((Object **)&g_scene->am);
	if (g_scene->mlx)
	{
		mlx_clear_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_image(g_scene->mlx->mlx, g_scene->mlx->img);
		free(g_scene->mlx->mlx);
		free(g_scene->mlx);
	}
	free(g_scene);
	if (res != -1)
		exit(res);
	return (res);
}

int	main(int argc, char **argv)
{
	g_scene = init_main(250, 250, 0);
	if (!g_scene)
		return (sysclean(1));
	if ((!parse(argv[1])))
		return (sysclean(1));
	if (!g_scene->am || !g_scene->camera || g_scene->error)
		return (sysclean(1));
	if (!initialize_mlx(g_scene))
		return (sysclean(1));
	renderframe();
	mlx_loop(g_scene->mlx->mlx);
	return (0);
}
