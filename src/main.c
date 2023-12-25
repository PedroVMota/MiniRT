/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2023/12/25 17:13:11 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>
#include <time.h>
//parsing notes
bool	parse_data(char *file);

typedef struct s_thread_data
{
    int id;
    int start_x;
    int end_x;
    t_scene *scene;
} t_thread_data;


pthread_mutex_t *mutex = NULL;

void *render_thread(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    int color;
    switch(data->id)
    {
        case 0: color = 0x00FFFFFF; break; // white
        case 1: color = 0x000000FF; break; // blue
        case 2: color = 0x00FF0000; break; // red
        case 3: color = 0x0000FF00; break; // green
        case 4: color = 0x00FFFF00; break; // yellow
        case 5: color = 0x00FF00FF; break; // magenta
        case 6: color = 0x0000FFFF; break; // cyan
        case 7: color = 0x00808080; break; // gray
        case 8: color = 0x00800000; break; // maroon
        case 9: color = 0x00008080; break; // teal
        case 10: color = 0x00808000; break; // olive
        case 11: color = 0x00000080; break; // navy
        default: color = 0x00FFFFFF; break; // default to white
    }

    for(int x = data->start_x; x < data->end_x; x++)
        for(int y = 0; y < HEIGHT; y++)
        {
            pthread_mutex_lock(mutex);
            mlx_pixel_put(scene()->mlx_data->mlx, scene()->mlx_data->win, x, y, color);
            pthread_mutex_unlock(mutex);
        }

    return NULL;
}


void render()
{
    mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    scene()->mlx_data = malloc(sizeof(t_mlxdata));
    clock_t start = clock();
    initialize_mlx();

    pthread_t threads[NUM_THREADS];
    t_thread_data thread_data[NUM_THREADS];
    int columns_per_thread = WIDTH / NUM_THREADS;

    for(int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].id = i;
        thread_data[i].start_x = i * columns_per_thread;
        thread_data[i].end_x = (i == NUM_THREADS - 1) ? WIDTH : (i + 1) * columns_per_thread;
        thread_data[i].scene = scene();
        pthread_create(&threads[i], NULL, render_thread, &thread_data[i]);
    }

    for(int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);
	mlx_loop(scene()->mlx_data->mlx);
    free(mutex);
}

void no_threads_render()
{
	scene()->mlx_data = malloc(sizeof(t_mlxdata));
	clock_t start = clock();
	initialize_mlx();
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
			my_mlx_pixel_put(x, y, &(t_color){255, 0, 0});
	clock_t end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Time spent: %f\n", time_spent);
	mlx_put_image_to_window(scene()->mlx_data->mlx, scene()->mlx_data->win, scene()->mlx_data->img, 0, 0);
	mlx_loop(scene()->mlx_data->mlx);
}

int	main(int ac, char **av)
{
	if (ac < 2 || ac > 2)
		write(2, "Invalid number arguments\n", 26);
	else if (!ft_strnstr(av[1], ".rt", ft_strlen(av[1])))
		err("Error: Invalid file format");
	else if (parse_data(av[1]))
	{
		err("Error");
		return (1);
	}
	printf("rendering with %d threads\n", NUM_THREADS);
	render();
	printf("rendering without threads\n");
	no_threads_render();
}
