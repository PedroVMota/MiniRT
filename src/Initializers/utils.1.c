/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:32:45 by pedro             #+#    #+#             */
/*   Updated: 2024/02/05 21:43:05 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static void	*err(gscene **s)
{
	free(*s);
	return (NULL);
}

bool	initialize_mlx(gscene *s)
{
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
	return (true);
}

gscene	*init_main(int width, int height, int depth)
{
	gscene	*m;

	m = malloc(sizeof(gscene));
	if (!m)
		return (NULL);
	m->depth = depth;
	m->width = width;
	m->height = height;
	m->camera = NULL;
	m->objects = NULL;
	m->lights = NULL;
	m->am = NULL;
	m->mlx = malloc(sizeof(t_mlxdata));
	if (!m->mlx)
		return ((gscene *)err(&m));
	if (!initialize_mlx(m))
		return ((gscene *)err(&m));
	return (m);
}
