/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2023/12/29 02:46:39 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>
#include <time.h>
// parsing notes
bool parse_data(char *file);
t_vector get_ray_direction(t_camera *camera, int x, int y);
t_vector vector_sub(t_vector *a, t_vector *b);
float dot(t_vector a, t_vector b);
void normilized(t_vector *vector);
void render();

void *render_thread(void *arg)
{
	t_thread_data *data = (t_thread_data *)arg;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = data->start_x; x < data->end_x; x++)
		{
			pthread_mutex_lock(scene()->mutex);
			t_vector rayDirection = get_ray_direction((t_camera *)scene()->camera, x, y);
			t_object *object = scene()->objects;
			t_object *closest_object = NULL;
			t_values closest_values = {INFINITY, INFINITY};
			struct s_values values = {INFINITY, INFINITY};
			while (object)
			{
				values = object->intersect(object, &rayDirection);
				if (values.t1 < closest_values.t1 && values.t1 > 0.0001)
				{
					closest_values = values;
					closest_object = object;
				}
				object = object->next;
			}
			if (closest_values.t1 == closest_values.t2 && closest_values.t1 != INFINITY)
				my_mlx_pixel_put(x, y, (t_color){150, 150, 255});
			else if (closest_object && closest_values.t1 != closest_values.t2)
				my_mlx_pixel_put(x, y, closest_object->color);
			else
				my_mlx_pixel_put(x, y, (t_color){0, 0, 0});
			pthread_mutex_unlock(scene()->mutex);
		}
	}
	return NULL;
}

int key_hook(int keycode, void *param)
{
	printf("keycode: %d\n", keycode);
	// 65354 down
	// 65362 up
	// 65361 left
	// 65363 right
	sucess("Key Event Pressed");
	(void)param;
	if (keycode == 65364)
		scene()->camera->vector.y -= 0.2;
	if (keycode == 65362)
		scene()->camera->vector.y += 0.2;
	if (keycode == 65361)
		scene()->camera->vector.x -= 0.2;
	if (keycode == 65363)
		scene()->camera->vector.x += 0.2;
	if (keycode == 122)
		scene()->camera->vector.z += 0.2;
	if (keycode == 120)
		scene()->camera->vector.z -= 0.2;
	if (keycode == 65364 || keycode == 65362 || keycode == 65361 || keycode == 65363 || keycode == 122 || keycode == 120)
	{
		mlx_clear_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		render();
	}
	if (keycode == 65307)
	{
		mlx_clear_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_image(scene()->mlx_data->mlx, scene()->mlx_data->img);
		mlx_destroy_display(scene()->mlx_data->mlx);
		remove_object_list();
		free(scene()->mutex);
		free(scene()->mlx_data->mlx);
		free(scene()->mlx_data);

		exit(0);
	}
	return (0);
}

void render()
{
	clock_t start = clock();
	int columns_per_thread = WIDTH / NUM_THREADS;
	for (int i = 0; i < NUM_THREADS; i++)
	{
		scene()->thread_data[i].id = i;
		scene()->thread_data[i].start_x = i * columns_per_thread;
		scene()->thread_data[i].end_x = (i == NUM_THREADS - 1) ? WIDTH : (i + 1) * columns_per_thread;
		pthread_create(&scene()->threads[i], NULL, render_thread, &scene()->thread_data[i]);
	}
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(scene()->threads[i], NULL);
	clock_t end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	mlx_put_image_to_window(scene()->mlx_data->mlx, scene()->mlx_data->win, scene()->mlx_data->img, 0, 0);
	printf("Time spent: %f\n", time_spent);
}

void initialize_structs()
{
	scene()->mlx_data = malloc(sizeof(t_mlxdata));
	scene()->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(scene()->mutex, NULL);
	initialize_mlx();
	scene()->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	scene()->scale = tan(((t_camera *)scene()->camera)->fov * 0.5 * M_PI / 180);
}

int main(int ac, char **av)
{
	if (ac < 2 || ac > 2)
		write(2, "Invalid number arguments\n", 26);
	else if (!ft_strnstr(av[1], ".rt", ft_strlen(av[1])))
		err("Error: Invalid file format");
	else if (parse_data(av[1]))
		return (1);
	initialize_structs();
	render();
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	mlx_loop(scene()->mlx_data->mlx);
}
