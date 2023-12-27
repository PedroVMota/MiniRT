/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2023/12/27 20:21:06 by pvital-m         ###   ########.fr       */
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
pthread_mutex_t *mutex = NULL;

typedef struct s_thread_data
{
	int id;
	int start_x;
	int end_x;
	t_vector direction;
} t_thread_data;

bool sphere_intersect(t_sphere *sphere, t_vector *ray, float *out_distance)
{
    t_vector oc = vector_sub(ray, &sphere->vector);
    float a = dot(*ray, *ray);
    float b = 2.0 * dot(oc, *ray);
    float c = dot(oc, oc) - sphere->diameter * sphere->diameter;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    else
    {
        float dist1 = (-b - sqrt(discriminant)) / (2.0 * a);
           float dist2 = (-b + sqrt(discriminant)) / (2.0 * a);
		*out_distance = (dist1 < dist2) ? dist1 : dist2;
        return true;
    }
}

void *render_thread(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = data->start_x; x < data->end_x; x++)
        {
            pthread_mutex_lock(mutex);
            t_vector rayDirection = get_ray_direction((t_camera *)scene()->camera, x, y);
            t_object *object = scene()->objects;
            t_object *closest_object = NULL;
            float closest_distance = INFINITY;

            while (object)
            {
                if (object->type == SPHERE)
                {
                    float distance;
                    if (sphere_intersect((t_sphere *)object, &rayDirection, &distance))
                    {
                        if (distance < closest_distance)
                        {
                            closest_distance = distance;
                            closest_object = object;
                        }
                    }
                }
                object = object->next;
            }

            if (closest_object)
                my_mlx_pixel_put(x, y, closest_object->color);
            else
                my_mlx_pixel_put(x, y, (t_color){0, 0, 0});

            pthread_mutex_unlock(mutex);
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
	(void)param;
	if(keycode == 65364)
	{
		scene()->camera->vector.y -= 0.3;
		render();
	}
	if(keycode == 65362)
	{
		scene()->camera->vector.y += 0.3;
		render();
	}
	if(keycode == 65361)
	{
		scene()->camera->vector.x -= 0.3;
		render();
	}
	if(keycode == 65363)
	{
		scene()->camera->vector.x += 0.3;
		render();
	}
	if(keycode == 122)
	{	scene()->camera->vector.z += 0.3;
		render();
	}
	if(keycode == 120)
	{	scene()->camera->vector.z -= 0.3;
		render();
	}
	
	return (0);
}

void render()
{
	mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	clock_t start = clock();
	pthread_t threads[NUM_THREADS];
	t_thread_data thread_data[NUM_THREADS];
	int columns_per_thread = WIDTH / NUM_THREADS;

	for (int i = 0; i < NUM_THREADS; i++)
	{
		thread_data[i].id = i;
		thread_data[i].start_x = i * columns_per_thread;
		thread_data[i].end_x = (i == NUM_THREADS - 1) ? WIDTH : (i + 1) * columns_per_thread;
		pthread_create(&threads[i], NULL, render_thread, &thread_data[i]);
	}
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);
	clock_t end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	mlx_put_image_to_window(scene()->mlx_data->mlx, scene()->mlx_data->win, scene()->mlx_data->img, 0, 0);
	printf("Time spent: %f\n", time_spent);
	free(mutex);
}

// void no_threads_render()
// {
// 	scene()->mlx_data = malloc(sizeof(t_mlxdata));
// 	clock_t start = clock();
// 	initialize_mlx();
// 	for (int y = 0; y < HEIGHT; y++)
// 		for (int x = 0; x < WIDTH; x++)
// 			my_mlx_pixel_put(x, y, 0x0000FF00);
// 	clock_t end = clock();
// 	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
// 	printf("Time spent: %f\n", time_spent);
// 	mlx_put_image_to_window(scene()->mlx_data->mlx, scene()->mlx_data->win, scene()->mlx_data->img, 0, 0);
// 	mlx_loop(scene()->mlx_data->mlx);
// }

int main(int ac, char **av)
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
	scene()->mlx_data = malloc(sizeof(t_mlxdata));
	initialize_mlx();
	printf("rendering with %d threads\n", NUM_THREADS);
	render();
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	mlx_loop(scene()->mlx_data->mlx);
	// printf("rendering without threads\n");
	// no_threads_render();
}
