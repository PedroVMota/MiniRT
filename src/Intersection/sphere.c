#include <center.h>
#include <stdbool.h>

t_vector vector_sub(t_vector *a, t_vector *b);
float dot(t_vector a, t_vector b);
t_values QuadraticFormula(float a, float b, float c);

t_vector getcoordssphere(t_vector *ray, float shortest_distance, t_sphere *sphere)
{
	t_vector values;
	values.x = ray->x * shortest_distance + sphere->vector.x;
	values.y = ray->y * shortest_distance + sphere->vector.y;
	values.z = ray->z * shortest_distance + sphere->vector.z;
	return ((t_vector){values.x, values.y, values.z});
}

t_values sphere_intersect(t_sphere *sphere, t_vector *ray)
{
	t_vector oc = vector_sub(ray, &sphere->vector);
	float a = dot(*ray, *ray);
	float b = 2.0 * dot(oc, *ray);
	float c = dot(oc, oc) - sphere->diameter * sphere->diameter;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (t_values){INFINITY, INFINITY};
	return QuadraticFormula(a, b, c);
}
