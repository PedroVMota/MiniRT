/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:27:09 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 09:31:52 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	*renderframethread(void *arg)
{
	t_threadata	*data;
	t_ray		ray;
	int			color;
	double		y;
	double		x;

	data = (t_threadata *)arg;
	y = data->start_y;
	while (y > data->end_y)
	{
		x = -g_scene->width / 2;
		while (x < g_scene->width / 2)
		{
			ray = getraydir((g_scene->camera)->o, x, y);
			color = raycolor(ray, g_scene->depth);
			my_mlx_pixel_put(tocanvas(x, false), tocanvas(y, true), color);
			x++;
		}
		y--;
	}
	return (NULL);
}

void	setroutine(pthread_t threads[], t_threadata threadData[], double step)
{
	int	i;

	i = 0;
	while (i < NUM_THREADS)
	{
		threadData[i].start_y = g_scene->height / 2 - i * step;
		threadData[i].end_y = threadData[i].start_y - step;
		pthread_create(&threads[i], NULL, renderframethread, &threadData[i]);
		i++;
	}
}

void	jointhreads(pthread_t threads[])
{
	int	i;

	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
}

void	renderframe(void)
{
	pthread_t	threads[NUM_THREADS];
	t_threadata	threaddata[NUM_THREADS];
	double		step;

	step = g_scene->height / NUM_THREADS;
	setroutine(threads, threaddata, step);
	jointhreads(threads);
	mlx_put_image_to_window(g_scene->mlx->mlx, g_scene->mlx->win, \
	g_scene->mlx->img, 0, 0);
}