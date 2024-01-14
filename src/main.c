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
void render();

typedef struct s_thread_data
{
	int id;
	int start_x;
	int end_x;
	t_vector direction;

} t_thread_data;


t_values sphere_intersect(t_sphere *sphere, t_vector *ray, float *out_distance)
{
    t_vector oc = vector_sub(&(scene()->camera->vector), &sphere->vector);
    float a = dot(*ray, *ray);
    float b = 2.0 * dot(oc, *ray);
    float c = dot(oc, oc) - sphere->diameter * sphere->diameter;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return (t_values){INFINITY, INFINITY};
    else
    {
        float dist1 = (-b - sqrt(discriminant)) / (2.0 * a);
        float dist2 = (-b + sqrt(discriminant)) / (2.0 * a);
		*out_distance = (dist1 < dist2) ? dist1 : dist2;
        return (t_values){dist1, dist2};
    }
}

t_color colorMultiply(t_color c, float d)
{
    t_color result;
    result.r = c.r * d;
    result.g = c.g * d;
    result.b = c.b * d;
    return result;
}

float ComputeLight(t_vector point, t_vector normal) {
  t_light *l = (t_light *)scene()->lights;
  if (!l)
    return 0;
  float intensity = 0;
  float length_n = Lenght(normal);  // Corrected typo
  t_vector vec_l;
  t_light *cur;

  while (l) {
    cur = l;  // Removed redundant declaration
    if (cur->type == AMBIENT)
      intensity += cur->intensity;
    else {
      if (cur->type == POINT)
        vec_l = vector_sub(&cur->vector, &point);  // Corrected function name
      else
        vec_l = cur->vector;
      
      float n_dot_l = dot(normal, vec_l);  // Corrected function name
      if (n_dot_l > 0)
        intensity += cur->intensity * n_dot_l / (length_n * Lenght(vec_l));  // Corrected function name
    }
    l = (t_light *)l->next;
  }
  return intensity;
}


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
			t_values val;
            float closest_distance = INFINITY;
            while (object)
            {
                if (object->type == SPHERE)
                {
                    float distance;
					val = sphere_intersect((t_sphere *)object, &rayDirection, &distance);
                    if (val.t1 != INFINITY && val.t2 != INFINITY)
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
            {
				t_color target = closest_object->color;
				t_vector hitPoint = add(scene()->camera->vector, Multiply(closest_distance, rayDirection));
				t_vector normal = vector_sub(&hitPoint, &closest_object->vector);
				normal = Multiply(1.0 / Lenght(normal), normal);
				float finalintensity = ComputeLight(hitPoint, normal);
				t_color c = colorMultiply(closest_object->color, finalintensity);
                my_mlx_pixel_put(x, y, c);
            }
            else
                my_mlx_pixel_put(x, y, (t_color){0,0,0});
            pthread_mutex_unlock(scene()->mutex);
        }
    }
	return NULL;
}

int key_hook(int keycode)
{
	printf("keycode: %d\n", keycode);
	/*
		65364: down
		65362: Up
		65361: left
		65363: right
		65307: ESC
	*/
	if(keycode == 65307)
	{
		mlx_clear_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
		mlx_destroy_image(scene()->mlx_data->mlx, scene()->mlx_data->img);
		mlx_destroy_display(scene()->mlx_data->mlx);
		remove_object_list();
		free(scene()->mlx_data->mlx);
		free(scene()->mlx_data);
		free(scene()->mutex);
		ft_exit();
	}
	if(keycode == 65362)
	{
		scene()->lights->vector.y += 1;
		render();
	}
	if(keycode == 65364)
	{
		scene()->lights->vector.y -= 1;
		render();
	}
	if(keycode == 65363)
	{
		scene()->lights->vector.x += 1;
		render();
	}
	if(keycode == 65361)
	{
		scene()->lights->vector.x -= 1;
		render();
	}
	if(keycode == 61)
	{
		scene()->lights->vector.z += 1;
		render();
	}
	if(keycode == 45)
	{
		scene()->lights->vector.z -= 1;
		render();
	}
	if(keycode == 93)
	{
		((t_sphere *)(scene()->objects))->diameter += 0.05;
		render();
	}
	if(keycode == 91)
	{
		((t_sphere *)(scene()->objects))->diameter -= 0.05;
		render();
	}
	return (0);
}

void render()
{
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
}

void DisplaySceneData()
{
	t_object *obj;

	obj = scene()->objects;

	int fd = open("data", O_CREAT | O_TRUNC | O_RDWR | 0644);
	if(fd == -1)
		return ;
	int STDOU = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	int i = 0;
	printf("======== OBJS ======== \n");
	while(obj)
	{
		printf("Object #%i\n", i);
		printf("Origin Point: %f %f %f\n", obj->vector.x, obj->vector.y, obj->vector.z);
		obj = obj->next;
	}
	i = 0;
	obj = scene()->lights;
	printf("======== Lights ======== \n");
	while(obj)
	{
		printf("Object #%i\n", i);
		printf("Origin Point: %f %f %f\n", obj->vector.x, obj->vector.y, obj->vector.z);
		obj = obj->next;
	}

	 i = 0;
	obj = scene()->camera;
	printf("======== Camera ======== \n");
	while(obj)
	{
		printf("Object #%i\n", i);
		printf("Origin Point: %f %f %f\n", obj->vector.x, obj->vector.y, obj->vector.z);
		obj = obj->next;
	}
	dup2(STDOU, STDOUT_FILENO);
	close(fd);
}

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
	DisplaySceneData();
	scene()->mlx_data = malloc(sizeof(t_mlxdata));
	scene()->mutex = NULL;
	initialize_mlx();
	render();
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	mlx_loop(scene()->mlx_data->mlx);
}
