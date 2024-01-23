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
t_values sphereColisions(t_vector o, t_vector dir, t_sphere sphere)
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
// ====================================== FUNCOES DE INTERCEPCOES DA PLANO ======================================

float calculate_d(t_plane *plane) {
	float a;

	a = (float)plane->o.x * plane->direction.x;
	a += (float)plane->o.y * plane->direction.y;
	a += (float)plane->o.z * plane->direction.z;
	return 	-a;
}


t_values planeColisions(t_plane *plane, t_vector *ray)
{

	float a = calculate_d(plane);

	//Plane Direction x,y,z can be acessed: plane->direction.xyz
	//Plane origin can be acessed by: plane->o.xyz
	//Camera origin can be acessed by: scene()->camera->o.xyz

	a = -a -(plane->direction.x * scene()->camera->o.x + plane->direction.y * scene()->camera->o.y + plane->direction.z * scene()->camera->o.z);
	float num = plane->direction.x * (plane->o.x - scene()->camera->o.x);
	num += plane->direction.y * (plane->o.y - scene()->camera->o.y);
	num += plane->direction.z * (plane->o.z - scene()->camera->o.z);
	// printf("%f __ %f __ %d\n", a, num, a == num);
	// print_vector(*ray);
	a /= (plane->direction.x * ray->x + plane->direction.y * ray->y + plane->direction.z * ray->z);
	// printf("%f\n", a);
	// exit(1);
	return (t_values) {-a, INFINITY};
}






// t_values planeColisions(t_vector o, t_plane plane, t_vector ray)
// {
// 	double numerator;
// 	t_values val;

// 	numerator = 0;
// 	numerator += plane.o.x * (o.x - plane.o.x);
// 	numerator += plane.o.y * (o.y - plane.o.y);
// 	numerator += plane.o.z * (o.z - plane.o.z);
// 	numerator *= -1;
// 	val.t1 = numerator / (ray.x * plane.o.x + ray.y * plane.o.y + ray.z * plane.o.z);
// 	val.t2 = 0;
// 	return val;
// }
// ====================================== FUNCOES DE INTERCEPCOES DA PLANO ======================================


// ====================================== FUNCAO PARA OBTER O OBJECT MAIS PROXIMO ======================================
t_values intersection(t_vector origin, t_vector dir, t_object *object)
{
	if(object->type == SPHERE)
		return sphereColisions(origin, dir, *(t_sphere *) (object));
	if(object->type == PLANE)
		return planeColisions((t_plane *) object, &dir);
	return ((t_values){INFINITY, INFINITY});
}

t_object *closestObject(t_vector origin, t_vector dir, float min_l, float max_l, double *closest_distance)
{
	t_object *obj; 
	t_values val;
	t_object *closest = NULL;
	
	obj = scene()->objects;
	if(!obj)
		return NULL;
	while(obj)
	{
		val = intersection(origin, dir, obj);
		if(val.t2 >= min_l && val.t1 < max_l && val.t1 < *closest_distance)
		{
			closest = obj;
			*closest_distance = val.t1;
		}
		if(val.t2 > min_l && val.t2 < max_l && val.t2 < *closest_distance)
		{
			closest = obj;
			*closest_distance = val.t2;
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
	if(isheight)
		return HEIGHT / 2 + c;
	return WIDTH / 2 + c;
}


t_vector getNormal(t_object *model, t_vector point, double t, t_vector dir)
{
	t_vector normal; 

	if(model->type == SPHERE)
	{
		normal = operation(SUBTRACT, point, model->o);
		normal = operation(DIVISION, normal, (t_vector){Lenght(normal),Lenght(normal),Lenght(normal)});
	}
	if(model->type == PLANE)
		normal = model->o;
	return normal;
}

t_color throw_ray(t_vector o, t_vector dir, double min_t, double max_t)
{
	double t = INFINITY;
    t_vector normal;
	t_object *closest = closestObject(o, dir, min_t, max_t, &t);
	if(!closest)
		return (t_color){0,0,0};
	t_vector point;
	point = operation(ADD, o, operation(MULTIPLY, dir, ((t_vector){t, t,t})));
	normal = getNormal(closest, point, t, dir);
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
	clock_t start = clock();
	for(int pixel_x = (-WIDTH / 2); pixel_x < (WIDTH / 2); pixel_x += 1.0)
	{
		for(int pixel_y = (-HEIGHT / 2); pixel_y < (HEIGHT / 2); pixel_y++)
		{
			t_vector dir = screen_to_viewport(pixel_x, -pixel_y);
			
			if(pixel_x == -100 && pixel_y == 200)
				printf("%f,%f,%f\n", dir.x, dir.y, dir.z);
			t_color finalColor = throw_ray(scene()->camera->o, dir, 1, INFINITY);
			my_mlx_pixel_put(toCanvas(pixel_x, false), toCanvas(pixel_y, true), finalColor);
		}
	}
	sucess("Congrats your program didn\'crash");
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	mlx_put_image_to_window(scene()->mlx_data->mlx, scene()->mlx_data->win, scene()->mlx_data->img, 0, 0);
}
int main(int ac, char **av)
{
	if (ac < 2 || ac > 2)
	{
		write(2, "Invalid number arguments\n", 26);
		return 1;
	}
	else if (!ft_strnstr(av[1], ".rt", ft_strlen(av[1])))
	{
		err("Error: Invalid file format");
		return 1;
	}
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