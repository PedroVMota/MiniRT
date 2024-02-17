/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:32:45 by pedro             #+#    #+#             */
/*   Updated: 2024/02/17 23:35:54 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

int	sysclean(int res);

bool	initialize_mlx(t_scene *s)
{
	s->mlx = malloc(sizeof(t_mlxdata) * 1);
	s->mlx->mlx = mlx_init();
	if (!s->mlx->mlx)
		return (false);
	s->mlx->win = mlx_new_window(s->mlx->mlx, s->width, s->height, "miniRT");
	if (!s->mlx->win)
		return (false);
	s->mlx->img = mlx_new_image(s->mlx->mlx, s->width, s->height);
	if (!s->mlx->img)
		return (false);
	s->mlx->addr = mlx_get_data_addr(s->mlx->img, &s->mlx->bits_per_pixel, \
		&s->mlx->line_length, &s->mlx->endian);
	if (!s->mlx->addr)
		return (false);
	mlx_key_hook(g_scene->mlx->win, key_hook, NULL);
	mlx_hook(g_scene->mlx->win, 17, 0, sysclean, (void *)(1));
	return (true);
}

t_scene	*init_main(int width, int height, int depth)
{
	t_scene	*m;

	m = malloc(sizeof(t_scene));
	if (!m)
		return (NULL);
	m->depth = depth;
	m->width = width;
	m->height = height;
	m->camera = NULL;
	m->objects = NULL;
	m->lights = NULL;
	m->am = NULL;
	m->props = NULL;
	m->mlx = NULL;
	m->error = 0;
	
	return (m);
}
