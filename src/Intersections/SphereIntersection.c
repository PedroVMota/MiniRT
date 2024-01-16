#include <center.h>

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