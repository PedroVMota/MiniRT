#include <center.h>

float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void normilized(t_vector *vector){
	float length = sqrt((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));

	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

t_vector vector_sub(t_vector *a, t_vector *b)
{
	t_vector result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;

	return result;
}

void QuadraticFormula(float a, float b, float c, t_values *t)
{
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		t->t1 = INFINITY;
		t->t2 = INFINITY;
		return;
	}
	t->t1 = (-b + sqrt(discriminant)) / (2 * a);
	t->t2 = (-b - sqrt(discriminant)) / (2 * a);
}

/// @brief get the vector direction. 
/// @param camera Camera details
/// @param x Pixel X axis position
/// @param y Pixel Y axis position
/// @return return a (x,y,z) vector direction. 
t_vector rayDir(t_camera *camera, int x, int y)
{
    float pixel_x = (2 * ((x) / (float)WIDTH) - 1) * scene()->aspect_ratio * scene()->scale;
    float pixel_y = (1 - 2 * ((y) / (float)HEIGHT)) * scene()->scale ;
    t_vector direction;
    // Subtract the camera's position from the pixel position
    direction.x = pixel_x - ((camera->vector.x / 10) * -1);
    direction.y = pixel_y - ((camera->vector.y / 10) * -1);
    direction.z = 1 - ((camera->vector.z / 10) * -1);
    normilized(&direction);
    return direction;
}

// Length of a 3D vector.
float Lenght(t_vector a)
{
	return(sqrt(dot(a, a)));
}

t_vector Multiply(float k,  t_vector vec){
  return (t_vector){k * vec.x, k * vec.y, k * vec.z};
}

t_vector add(t_vector v1, t_vector v2){
  return (t_vector){v1.x + v2.x , v1.y + v2.y , v1.z + v2.z };
}


float Max(float a, float b)
{
	if (a > b)
		return a;
	return b;
}

float Min(float a, float b)
{
	if(a < b)
		return a;
	return b;
}