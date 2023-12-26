#include <center.h>

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

t_vector get_ray_direction(t_camera *camera, int x, int y)
{
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float scale = tan(camera->fov * 0.5 * M_PI / 180);
    float pixel_x = (2 * ((x + 0.5) / (float)WIDTH) - 1) * aspect_ratio * scale;
    float pixel_y = (1 - 2 * ((y + 0.5) / (float)HEIGHT)) * scale ;

    t_vector direction;
    direction.x = pixel_x;
    direction.y = pixel_y;
    direction.z = -1; // the image plane is one unit away from the camera


    // Normalize the direction vector
    // normilized(&direction);

    return direction;
}