#include "3DMath.h"

float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void	normalized(t_vector *a)
{
	float	length;

	length = sqrt(dot(*a, *a));
	a->x /= length;
	a->y /= length;
	a->z /= length;
}


float Max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}