#include <center.h>

float calculate_d(t_plane *plane) {
	float a;

	a = (float)plane->vector.x * plane->direction.x;
	a += (float)plane->vector.y * plane->direction.y;
	a += (float)plane->vector.z * plane->direction.z;
	return 	-a;
}

t_values plane_intersect(t_plane *plane, t_vector *ray)
{

	float a = calculate_d(plane);

	a = -a -(plane->direction.x * scene()->camera->vector.x + plane->direction.y * scene()->camera->vector.y + plane->direction.z * scene()->camera->vector.z);
	float num = plane->direction.x * (plane->vector.x - scene()->camera->vector.x);
	num += plane->direction.y * (plane->vector.y - scene()->camera->vector.y);
	num += plane->direction.z * (plane->vector.z - scene()->camera->vector.z);
	// printf("%f __ %f __ %d\n", a, num, a == num);
	// print_vector(*ray);
	a /= (plane->direction.x * ray->x + plane->direction.y * ray->y + plane->direction.z * ray->z);
	// printf("%f\n", a);
	// exit(1);
	return (t_values) {-a, INFINITY};
}