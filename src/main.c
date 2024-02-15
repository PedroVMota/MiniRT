/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/02/15 16:19:34 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

t_scene	*g_scene = NULL;

int	sysclean(int res)
{
	if (g_scene->props)
		delprops(&g_scene->props);
	del((t_obj **)&g_scene->lights);
	del((t_obj **)&g_scene->objects);
	del((t_obj **)&g_scene->camera);
	del((t_obj **)&g_scene->am);
	if (g_scene->mlx)
	{
		mlx_clear_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_window(g_scene->mlx->mlx, g_scene->mlx->win);
		mlx_destroy_image(g_scene->mlx->mlx, g_scene->mlx->img);
		mlx_destroy_display(g_scene->mlx->mlx);
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
	g_scene = NULL;
	if (argc != 2)
		return (sysclean(1));
	g_scene = init_main(2, 2, 3);
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
