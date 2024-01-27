/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:41:38 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/27 16:15:09 by pedro            ###   ########.fr       */
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
	return (t_values){a, INFINITY};
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
		if ((val.t1 > min_l && val.t1 < max_l) && val.t1 < *ct)
		{
			closest = obj;
			if(ct)
				*ct = val.t1;
		}
		if ((val.t2  > min_l && val.t2 <max_l) && val.t2 < *ct)
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


	viewport.y = (y / HEIGHT) * scene()->viewsettings.height;
	viewport.x = (x / WIDTH) * scene()->viewsettings.width;
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
		normal = ((t_plane *)model)->direction;
	return normal;
}

int advance_temp(t_light **temp)
{
    if (*temp)
    {
        *temp = (t_light *)(*temp)->next;
        return 1;
    }
    return 0;
}
#define EPSILION 0.001

int is_in_shadow(t_vector O, t_vector light_pos, double t_min, double t_max)
{
    t_object *temp;
    t_values t;

    temp = (scene()->objects);
    while (temp)
    {
        t = intersection(O, light_pos, temp);
    	if (t.t1 > t_min + EPSILION && t.t1 < t_max - EPSILION && t.t1 < Lenght(light_pos))
    		return 1;
		if (t.t2 > t_min + EPSILION && t.t2 < t_max - EPSILION && t.t2 < Lenght(light_pos))
    		return 1;
        temp = (temp->next);
    }
    return 0;
}

float ComputeLight(t_vector point, t_vector normal)
{
	t_light *l = (t_light *)scene()->lights;
	if (!l)
		return 0;
	float intensity = 0;
	float length_n = Lenght(normal); // Corrected typo
	t_vector vec_l;
	t_light *cur;

	while (l)
	{
    	cur = l;
    	if (cur->type == AMBIENT)
    	{
        	intensity += cur->intensity;
   	 	}
   	 	else
    	{
        	if (cur->type == POINT)
            	vec_l = operation(SUBTRACT, cur->o, point);
        	else
            	vec_l = cur->o;

			// normilized(&point);
        	if (is_in_shadow(point, vec_l, 0.001, 1) && advance_temp(&l))
	            continue;
			double n_dot_l = dot(vec_l, normal);
			intensity += cur->intensity * fmax(0.0f, n_dot_l / (length_n * Lenght(vec_l))); // Corrected function name}
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

	double intensity = ComputeLight(point, normal);

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

void RotateX(t_vector *rayDir, double theta)
{
	double temp = rayDir->y;
	rayDir->y = rayDir->y * cos(theta) + rayDir->z * sin(theta);
	rayDir->z = -temp * sin(theta) + rayDir->z * cos(theta);
}

void RotateY(t_vector *rayDir, double theta)
{
	double temp = rayDir->x;
	rayDir->x = rayDir->x * cos(theta) + rayDir->z * sin(theta);
	rayDir->z = -temp * sin(theta) + rayDir->z * cos(theta);
}

void RotateZ(t_vector *rayDir, double theta)
{
	double temp = rayDir->x;
	rayDir->x = rayDir->x * cos(theta) + rayDir->z * sin(theta);
	rayDir->z = -temp * sin(theta) + rayDir->z * cos(theta);
}

void rotation(t_scene *sc, t_vector *rayDir)
{
	RotateX(rayDir, sc->camera->theta.x);
	RotateY(rayDir, sc->camera->theta.y);
}

void render()
{

	clock_t start, end;

	start = clock();
	mlx_clear_window(scene()->mlx_data->mlx, scene()->mlx_data->win);

	printf("Rendering...\n");
	printf("Camera position: %f %f %f\n", scene()->camera->o.x, scene()->camera->o.y, scene()->camera->o.z);
	printf("Camera rotation: %f %f %f\n", scene()->camera->theta.x, scene()->camera->theta.y, scene()->camera->theta.z);
	for (double pixel_x = (-WIDTH / 2); pixel_x < (WIDTH / 2); pixel_x += 1.0)
	{
		for (double pixel_y = (-HEIGHT / 2); pixel_y < (HEIGHT / 2); pixel_y++)
		{
			t_vector dir = screen_to_viewport(pixel_x, -pixel_y);
			rotation(scene(), &dir);
			t_color finalColor = throw_ray(scene()->camera->o, dir, 1, INFINITY);
			my_mlx_pixel_put(toCanvas(pixel_x, false), toCanvas(pixel_y, true), finalColor);
		}
	}
	end = clock();
	printf("Time taken: %f\n", ((double)(end - start) / CLOCKS_PER_SEC));
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
	scene()->viewsettings.aspectratio = (float)WIDTH / (float)HEIGHT;
	scene()->viewsettings.height = (tan(((t_camera *)(scene()->camera))->fov / 2 * M_PI / 180) * 2);
	scene()->viewsettings.width = ((tan(((t_camera *)(scene()->camera))->fov / 2 * M_PI / 180) * 2)) * scene()->viewsettings.aspectratio;
	scene()->mlx_data = malloc(sizeof(t_mlxdata));
	initialize_mlx();
	render();
	mlx_key_hook(scene()->mlx_data->win, key_hook, NULL);
	// mlx_loop_hook(scene()->mlx_data->mlx, key_hook, NULL);
	mlx_loop(scene()->mlx_data->mlx);
}