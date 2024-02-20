/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:27:09 by pedro             #+#    #+#             */
/*   Updated: 2024/02/20 11:25:21 by pvital-m         ###   ########.fr       */
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
		x = -(gscene())->width / 2;
		while (x < (gscene())->width / 2)
		{
			ray = getraydir(((gscene())->camera)->o, x, y);
			rot((gscene())->camera->theta, &ray.d);
			color = raycolor(ray, (gscene())->depth);
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
	(gscene())->camera->theta = applyrot((t_vector){0, 0, 1}, \
		(gscene())->camera->d);
	while (i < NUM_THREADS)
	{
		threadData[i].start_y = (gscene())->height / 2 - i * step;
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

char *gettype(int type)
{
	if(type == SPHERE)
		return "SPHERE";
	if(type == CYLINDER)
		return "CYLINDER";
	if(type == PLANE)
		return "PLANE";
	if(type == PARABOLOID)
		return "PARABOLOID";
	if(type == CAMERA)
		return "CAMERA";
	return "NOT SELECTING";
}

void menu()
{
	write(1, "\033[2J", 5);
	write(1, "Welcome to MiniRT\n", 19);
	write(1, "W/A/S/D/Q/E to move along the 3 axis\n", 38);
	write(1, "Right mouse button to select the object\n", 41);
	write(1, "Left mouse button to select the camera\n", 40);
	
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
	mlx_put_image_to_window((gscene())->mlx->mlx, (gscene())->mlx->win, \
	(gscene())->mlx->img, 0, 0);
}
