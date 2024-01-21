/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/21 19:46:33 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>
#include <time.h>

typedef struct s_closest
{
	t_object *object;
	t_values t;
} t_closest;

void ConvertRayDirToPixelRangeViewPort(t_vector *ray, int *x, int *y)
{
	*x = ray->x * WIDTH / 2;
	*y = ray->y * HEIGHT / 2;
}

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
	if (discriminant < 0)
		return (t_values){INFINITY, INFINITY};
	return ((t_values){(-b + sqrt(discriminant)) / (2 * a), (-b - sqrt(discriminant)) / (2 * a)});
}
// ====================================== FUNCOES DE INTERCEPCOES DA ESFERA ======================================
// ====================================== FUNCOES DE INTERCEPCOES DA PLANO ======================================

float calculate_d(t_plane *plane)
{
	float a;

	a = (float)plane->o.x * plane->direction.x;
	a += (float)plane->o.y * plane->direction.y;
	a += (float)plane->o.z * plane->direction.z;
	return -a;
}

// t_values plane_intersect(t_plane *plane, t_vector *ray)
// {

// 	float a = calculate_d(plane);

// 	// Plane Direction x,y,z can be acessed: plane->direction.xyz
// 	// Plane origin can be acessed by: plane->o.xyz
// 	// Camera origin can be acessed by: scene()->camera->o.xyz

// 	a = -a - (
// 		plane->direction.x * scene()->camera->o.x + \
// 		plane->direction.y * scene()->camera->o.y + \
// 		plane->direction.z * scene()->camera->o.z
// 	);
// 	// printf("%f __ %f __ %d\n", a, num, a == num);
// 	// print_vector(*ray);
// 	a /= (plane->direction.x * ray->x + plane->direction.y * ray->y + plane->direction.z * ray->z);
// 	bool print = false;
// 	if(print && fork() == 0)
// 	{
// 		int fd = open("plane_intersect" , O_RDWR | O_CREAT | O_APPEND);
// 		int dup = dup2(fd, 1);
// 		printf("The Ray position is at the center of the screen\n");
// 		printf("PLd(x,y,z)= [%fx,%fy,%fz]\n", ray->x, ray->y, ray->z);
// 		printf("The variable a is: %f\n", a);
// 		printf("PLo(x,y,z)= [%fx,%fy,%fz]\n", plane->o.x, plane->o.y, plane->o.z);
// 		int x = -999;
// 		int y = -999;
// 		ConvertRayDirToPixelRangeViewPort(ray, &x, &y);
// 		printf("Screen ViewPort: [%d, %d]\n", x, y);
// 		close(fd);
// 		exit(1);
// 	}
// 	else
// 		wait(NULL);
// 	// printf("%f\n", a);
// 	// exit(1);
// 	return (t_values){-a, 0};
// }

t_values plane_intersect(t_vector o, t_plane plane, t_vector ray)
{
	double a;
	t_values val;

	a = 0;
	a += plane.o.x * (o.x - plane.o.x);
	a += plane.o.y * (o.y - plane.o.y);
	a += plane.o.z * (o.z - plane.o.z);
	a *= -1;
	val.t2 = a / (ray.x * plane.o.x + ray.y * plane.o.y + ray.z * plane.o.z);
	val.t1 = INFINITY;
	return val;
}
// ====================================== FUNCOES DE INTERCEPCOES DA PLANO ======================================

// ====================================== FUNCAO PARA OBTER O OBJECT MAIS PROXIMO ======================================
t_values intersection(t_vector origin, t_vector dir, t_object *object)
{
	if (object->type == SPHERE)
		return sphere_colisions(origin, dir, *(t_sphere *)(object));
	if (object->type == PLANE)
		return plane_intersect(origin, *(t_plane *)object, dir);
	return ((t_values){INFINITY, INFINITY});
}

t_object *closestObject(t_vector origin, t_vector dir, float min_l, float max_l, double *ct)
{
	t_object *obj;
	t_values val;
	t_object *closest = NULL;

	obj = scene()->objects;
	if (!obj)
		return NULL;
	while (obj)
	{
		val = intersection(origin, dir, obj);
		if (val.t2 >= min_l && val.t1 < max_l && val.t1 < *ct)
		{
			closest = obj;
			*ct = val.t1;
		}
		if (val.t2 > min_l && val.t2 < max_l && val.t2 < *ct)
		{
			closest = obj;
			*ct = val.t2;
		}
		obj = obj->next;
	}
	return closest;
}
// ====================================== FUNCAO PARA OBTER O OBJECT MAIS PROXIMO ======================================

t_vector screen_to_viewport(double x, double y)
{
	t_vector viewport;

	viewport.x = x / WIDTH;
	viewport.y = y / HEIGHT * ((float)WIDTH / HEIGHT);
	viewport.z = 1;
	return viewport;
}

double toCanvas(double c, bool isheight)
{
	if (isheight)
		return HEIGHT / 2 + c;
	return WIDTH / 2 + c;
}

// t_vector getNormal(t_object *model, t_vector point, double t, t_vector dir)
// {
// 	t_vector normal;

// 	(void)t;
// 	(void)dir;
// 	if((model->type = SPHERE))
// 	{
// 		normal = operation(SUBTRACT, point, model->o);
// 		normal = operation(DIVISION, normal, (t_vector){Lenght(normal),Lenght(normal),Lenght(normal)});
// 	}
// 	else if(model->type == PLANE)
// 		normal = model->o;
// 	return normal;
// }

t_color throw_ray(t_vector o, t_vector dir, double min_t, double max_t)
{
	double closest_t = INFINITY;
	t_object *closest = closestObject(o, dir, min_t, max_t, &closest_t);
	if (!closest)
		return (t_color){0, 0, 0};
	t_vector point;
	// t_vector normal;
	point = operation(ADD, o, operation(MULTIPLY, dir, ((t_vector){closest_t, closest_t, closest_t})));
	// normal = getNormal(closest, point, closest_t, dir);
	return (closest->rgb);
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
	double avg;
	static long executed = 0;
	
	clock_t start = clock();
	for (int pixel_x = (-WIDTH / 2); pixel_x < (WIDTH / 2); pixel_x += 1.0)
	{
		for (int pixel_y = (-HEIGHT / 2); pixel_y < (HEIGHT / 2); pixel_y++)
		{
			t_vector dir = screen_to_viewport(pixel_x, -pixel_y);
			t_color finalColor = throw_ray(scene()->camera->o, dir, 1, INFINITY);
			my_mlx_pixel_put(toCanvas(pixel_x, false), toCanvas(pixel_y, true), finalColor);
		}
	}
	avg += (double)(clock() - start) / CLOCKS_PER_SEC;
	float avg_time = avg / ++executed;
	system("clear");
	printf("Time spent: %f\n", avg_time);
	sucess("Congrats your program didn\'crash");
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