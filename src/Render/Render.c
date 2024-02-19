/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:27:09 by pedro             #+#    #+#             */
/*   Updated: 2024/02/19 22:41:45 by pvital-m         ###   ########.fr       */
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

void menu()
{
	printf("Menu\n");
	if (!gscene()->selected)
		return ;
	int type;
	printf("Menu checked\n");
	
	type = gscene()->selected->type;
	char *id = ft_itoa(type);
	char *msg = ft_strjoin("Type Selected: ", id);

	mlx_string_put(gscene()->mlx->mlx, gscene()->mlx->win, 10, 10, 0x00ffffff, msg);
	free(id);
	free(msg);
}

void	renderframe(void)
{
	pthread_t	threads[NUM_THREADS];
	t_threadata	threaddata[NUM_THREADS];
	double		step;

	step = (gscene())->height / NUM_THREADS;
	setroutine(threads, threaddata, step);
	jointhreads(threads);
	mlx_put_image_to_window((gscene())->mlx->mlx, (gscene())->mlx->win, \
	(gscene())->mlx->img, 0, 0);
	menu();
}
