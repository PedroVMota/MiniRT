/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/22 23:34:17 by pedro            ###   ########.fr       */
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

t_values plane_intersect(t_plane *plane, t_vector *ray)
{

	float a = calculate_d(plane); // a is used to calculate the t value
	a = -a - (
		plane->direction.x * scene()->camera->o.x + \
		plane->direction.y * scene()->camera->o.y + \
		plane->direction.z * scene()->camera->o.z
	);
	a /= (plane->direction.x * ray->x + plane->direction.y * ray->y + plane->direction.z * ray->z);
	return (t_values){a, 0};
}
// ====================================== FUNCOES DE INTERCEPCOES DA PLANO ======================================



// ====================================== FUNCAO DE INTERCEPCOES DO CILINDRO ======================================

t_values cylinder_intersection(t_vector origin, t_vector rayDir, t_cylinder obj)
{
    t_values values;
    t_vector oc;
    float a, b, c, discriminant;

    oc = operation(SUBTRACT, origin, obj.o);
    a = dot(rayDir, rayDir) - pow(dot(rayDir, obj.direction), 2);
    b = 2 * (dot(rayDir, oc) - (dot(rayDir, obj.direction) * dot(oc, obj.direction)));
    c = dot(oc, oc) - pow(dot(oc, obj.direction), 2) - pow(obj.diameter / 2, 2);
    discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
        return (t_values){INFINITY, INFINITY};
    values.t1 = (-b + sqrt(discriminant)) / (2 * a);
    values.t2 = (-b - sqrt(discriminant)) / (2 * a);

    // Check if the intersection points are within the bounds of the cylinder's height
    t_vector p1 = operation(ADD, origin, operation(MULTIPLY,rayDir, (t_vector){values.t1, values.t1, values.t1}));
    t_vector p2 = operation(ADD, origin, operation(MULTIPLY,rayDir, (t_vector){values.t2, values.t2, values.t2}));
    float h1 = dot(operation(SUBTRACT, p1, obj.o), obj.direction);
    float h2 = dot(operation(SUBTRACT, p2, obj.o), obj.direction);
    if (h1 < 0 || h1 > obj.height)
        values.t1 = INFINITY;
    if (h2 < 0 || h2 > obj.height)
        values.t2 = INFINITY;

    return values;
}
// ====================================== FUNCAO DE INTERCEPCOES DO CILINDRO ====================================== 



// ====================================== FUNCAO PARA OBTER O OBJECT MAIS PROXIMO ======================================
t_values intersection(t_vector origin, t_vector dir, t_object *object)
{
	if (object->type == SPHERE)
		return sphere_colisions(origin, dir, *(t_sphere *)(object));
	if (object->type == PLANE)
		return plane_intersect((t_plane *)(object), &dir);
	if (object->type == CYLINDER)
		return cylinder_intersection(origin, dir, *(t_cylinder *)(object));
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
		if ((val.t1 >= min_l && val.t1 < max_l) && val.t1 < *ct)
		{
			closest = obj;
			if(ct)
				*ct = val.t1;
		}
		if ((val.t2 > min_l && val.t2 < max_l) && val.t2 < *ct)
		{
			closest = obj;
			if(ct)
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

t_vector getNormal(t_object *model, t_vector point, double t, t_vector dir)
{
	t_vector normal;

	(void)t;
	(void)dir;
	if (model->type == SPHERE)
	{
		normal = operation(SUBTRACT, point, model->o);
		normal = operation(DIVISION, normal, (t_vector){Lenght(normal), Lenght(normal), Lenght(normal)});
	}
	if (model->type == PLANE)
		normal = model->o;
	return normal;
}

#define EPSILION 0.0001

float ComputeLight(t_vector point, t_vector normal)
{
	t_light *l = (t_light *)scene()->lights;
	if (!l)
		return 0;
	float intensity = 0;
	float length_n = Lenght(normal); // Corrected typo
	t_vector vec_l;
	t_light *cur;
	float max_t;

	while (l)
	{
		cur = l; // Removed redundant declaration
		if (cur->type == AMBIENT)
			intensity += cur->intensity;
		else
		{
			if (cur->type == POINT)
			{
				vec_l = operation(SUBTRACT, cur->o, point); // Corrected function name}
				max_t = 1;
			}
			else
			{
				vec_l = cur->o;
				max_t = INFINITY;
			}

			// Shadow
			// t_object *blocker = closestObject(point, vec_l, EPSILION, max_t, NULL);
			// if (blocker)
			// 	continue;

			// difuse
			float n_dot_l = dot(normal, vec_l); // Corrected function name
			if (n_dot_l > 0)
				intensity += cur->intensity * n_dot_l / (length_n * Lenght(vec_l)); // Corrected function name
		}
		l = (t_light *)l->next;
	}
	return intensity;
}

t_color throw_ray(t_vector o, t_vector dir, double min_t, double max_t)
{
	double closest_t = INFINITY;

	t_object *closest = closestObject(o, dir, min_t, max_t, &closest_t);
	if (!closest)
		return (t_color){0, 0, 0};
	t_vector point;
	t_vector normal;
	point = operation(ADD, o, operation(MULTIPLY, dir, ((t_vector){closest_t, closest_t, closest_t})));
	normal = getNormal(closest, point, closest_t, dir);

	float intensity = ComputeLight(point, normal);

	t_color color = closest->rgb;
	color.r *= intensity;
	color.g *= intensity;
	color.b *= intensity;

	return (color);
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

void printMenu()
{
	info("Press M to Toggle Menu");
	int localWidth = WIDTH / 3;
	int localXPadding = 10;
	int localYPadding = 10;
	int XWrite = 10;
	int YWrite = 10;
	printf("Menu %s\n", scene()->show_menu ? "ON" : "OFF");
	if (scene()->show_menu == false)
		return ;
	// Menu Background
	// for (int x = 0; x < localWidth; x++)
		// for (int y = 0; y < HEIGHT; y++)
			// my_mlx_pixel_put(x, y, (t_color){75,75,255});
	// Menu Title
	// for (int x = 0; x < localWidth; x++)
		// for (int y = 0; y < 50; y++)
			// my_mlx_pixe÷l_put(x, y, (t_color){255,255,255});
	// Menu Title Text
	printf("Menu Title Text\n");
	mlx_string_put(scene()->mlx_data->mlx, scene()->mlx_data->win, 10, 10, 0xfffffffff, "alksdjsalkjdlskajdlakjldjasldjka");
}
void render()
{
	double avg;
	static long executed = 0;
	mlx_clear_window(scene()->mlx_data->mlx, scene()->mlx_data->win);
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
	printMenu();
	
	avg += (double)(clock() - start) / CLOCKS_PER_SEC;
	float avg_time = avg / ++executed;
	printf("Time spent: %f\n", avg_time);
	sucess("Congrats your program didn\'crash");
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	mlx_put_image_to_window(scene()->mlx_data->mlx, scene()->mlx_data->win, scene()->mlx_data->img, 0, 0);
}
int main(int ac, char **av)
{
	scene()->show_menu = true;
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