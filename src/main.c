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

typedef struct s_closest{
	t_object *object;
	t_values t;
} t_closest;

// ====================================== FUNCOES DE INTERCEPCOES DA ESFERA ======================================
t_values sphere_colisions(t_vector o, t_vector dir, t_sphere sphere)
{
	t_vector oc;
	double a, b, c, discriminant;

	oc = operation(SUBTRACT, o, sphere.o);
	a = dot(dir, dir);
	b = 2 * dot(oc, dir);
	c = dot(oc, oc) - (sphere.diameter);
	discriminant = (b * b) - (4 * a * c);
	if(discriminant < 0)
		return (t_values){INFINITY, INFINITY};
	return ((t_values){(-b + sqrt(discriminant)) / (2 * a),(-b - sqrt(discriminant)) / (2 * a)});
}
// ====================================== FUNCOES DE INTERCEPCOES DA ESFERA ======================================

// ====================================== FUNCAO PARA OBTER O OBJECT MAIS PROXIMO ======================================
t_values intersection(t_vector origin, t_vector dir, t_object *object)
{
	if(object->type == sphere_colisions)
		return sphere_colisions(origin, dir, *(t_sphere *)(object));
}

t_closest *object(t_vector origin, t_vector dir, float min_l, float max_l, float *closest_t)
{
	t_object *obj; 
	t_closest *data;
	t_values val;

	data = malloc(sizeof(t_closest));
	obj = scene()->objects;
	if(!obj)
		return NULL;
	while(obj)
	{
		val = intersection(origin, dir, obj);
		if(val.t2 > min_l && val.t1 > max_l && val.t1 < *closest_t)
		{
			data->object = obj;
			data->t = val;
			*closest_t = val.t1;
		}
		if(val.t2 > min_l && val.t2 > max_l && val.t2 < *closest_t)
		{
			data->object = obj;
			data->t = val;
			*closest_t = val.t2;
		}
		obj = obj->next;
	}
	return data;
}
// ====================================== FUNCAO PARA OBTER O OBJECT MAIS PROXIMO ======================================


t_vector screen_to_viewport(double x, double y)
{
	t_vector viewport;

	viewport.x = x / WIDTH * (2 * tan(((t_camera *)(scene()->camera))->fov / 2.0 * M_PI / 180.0f));
	viewport.y = y / HEIGHT * ((float)WIDTH / HEIGHT);
	viewport.z = 1;
	return viewport;
}

double toCanvas(double c, bool isheight)
{
	if(isheight)
		return HEIGHT / 2 + c;
	return WIDTH / 2 + c;
}

t_color throw_ray(t_vector o, t_vector dir, double min_t, double max_t)
{
	return (t_color){0,0,0};
}

/*
Primeiro passo transformar o with por exemplo 1280 720

verificar se estamos entao no topo mais esquerdo

+-----------+ WIDTH = 1280
|			|
|			|
|			|
+-----------+
HEIGHT = 720;

neste caso queremos ter o range the ([-640, 640], [-320, 320])

(-640, 320)  +----------------------------------+ (640, 320)
				|									|
				|									|
				|									|
				|									|
				|				(0,0)				|
				|									|
				|									|
				|									|
				|									|
(-640, -320) +-----------------------------------+ (640, -320)
*/

	

void render()
{
	clock_t start = clock();
	for(int pixel_x = (-WIDTH / 2); pixel_x < (WIDTH / 2); pixel_x += 1.0)
	{
		for(int pixel_y = (-HEIGHT / 2); pixel_y < (HEIGHT / 2); pixel_y++)
		{
			my_mlx_pixel_put(toCanvas(pixel_x, false),toCanvas(pixel_y, true), (t_color){76,255,140});
		}
	}
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	mlx_put_image_to_window(scene()->mlx_data->mlx, scene()->mlx_data->win, scene()->mlx_data->img, 0, 0);
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
	scene()->mlx_data = malloc(sizeof(t_mlxdata));
	initialize_mlx();
	render();
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	mlx_loop(scene()->mlx_data->mlx);
}