/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:27:09 by pedro             #+#    #+#             */
/*   Updated: 2024/02/20 16:43:24 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

double	canvastovp(double x, bool height)
{
	if (height)
		return (x / (gscene())->height);
	return (x / (gscene())->width);
}

void	*renderframethread(void *arg)
{
	t_threadata	*data;
	t_ray		ray;
	int			color;
	double		x;
	double		y;

	data = (t_threadata *)arg;
	x = data->start_x;
	// printf("Range [%d]: %f - %f\n", data->id, data->start_x, data->end_x);
	while (x < data->end_x)
	{
		y = -(gscene())->height / 2;
		while (y < (gscene())->height / 2)
		{
			ray = getraydir(((gscene())->camera)->o, x, y);
			rot((gscene())->camera->theta, &ray.d);
			color = raycolor(ray, (gscene())->depth);
			my_mlx_pixel_put(tocanvas(x, false), tocanvas(y, true), color);
			y++;
		}
		x++;
	}
	return (NULL);
}

void	setroutine(pthread_t threads[], t_threadata threadData[], double step)
{
	int		i;
	double	width_per_thread;

	width_per_thread = gscene()->width / (double)NUM_THREADS;
	i = 0;
	(gscene())->camera->theta = applyrot((t_vector){0, 0, 1},
			(gscene())->camera->d);
	while (i < NUM_THREADS)
	{
		threadData[i].start_x = -gscene()->width / 2 + i * width_per_thread;
		threadData[i].end_x = threadData[i].start_x + width_per_thread;
		if (i == NUM_THREADS - 1)
			// Ensure the last thread covers the remaining width
			threadData[i].end_x = gscene()->width / 2;
		threadData[i].id = i;
		printf("Thread %d: %f - %f\n", i, threadData[i].start_x,
			threadData[i].end_x);
		pthread_create(&threads[i], NULL, renderframethread, &threadData[i]);
		i++;
	}
}

void	jointhreads(pthread_t threads[])
{
	int	i;

	i = -1;
	while (++i < NUM_THREADS)
	{
		mlx_put_image_to_window((gscene())->mlx->mlx, (gscene())->mlx->win, \
	(gscene())->mlx->img, 0, 0);
		pthread_join(threads[i], NULL);
	}
}

void	menu(void)
{
	write(1, "\033[2J", 5);
	write(1, "Welcome to MiniRT\n", 19);
	write(1, "\n", 1);
	write(1, "W/A/S/D/Q/E to move along the 3 axis\n", 38);
	write(1, "Right mouse button to select the object\n", 41);
	write(1, "Left mouse button to select the camera\n", 40);
	write(1, "R/F rotate in X axys (Just objects)", 36);
	write(1, "T/G rotate in Y axys (Just objects)", 36);
	write(1, "Y/H rotate in Z axys (Just objects)", 36);
}

void	renderframe(void)
{
	pthread_t	threads[NUM_THREADS];
	t_threadata	threaddata[NUM_THREADS];
	double		step;

	step = (gscene())->height / NUM_THREADS;
	setroutine(threads, threaddata, step);
	jointhreads(threads);
	// menu();
}
