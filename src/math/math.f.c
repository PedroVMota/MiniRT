/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 04:44:42 by pedro             #+#    #+#             */
/*   Updated: 2023/12/28 05:17:45 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_values QuadraticFormula(float a, float b, float c)
{
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (t_values){INFINITY, INFINITY};
	static int i =0;
	if (sqrt(discriminant) == 0 && i == 0)
	{
		info("Discriminant is zero");
		printf("HitX: %f\n", -b / (2 * a));
		printf("HitY: %f\n", -b / (2 * a));
		i++;
	}
	return (t_values){ ((-b - sqrt(discriminant)) / (2 * a)), ((-b + sqrt(discriminant)) / (2 * a))};
}

/// @brief get the vector direction. 
/// @param camera Camera details
/// @param x Pixel X axis position
/// @param y Pixel Y axis position
/// @return return a (x,y,z) vector direction. 
t_vector get_ray_direction(t_camera *camera, int x, int y)
{
    float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float scale = tan(camera->fov * 0.5 * M_PI / 180);
    float pixel_x = (2 * ((x + 0.5) / (float)WIDTH) - 1) * aspect_ratio * scale;
    float pixel_y = (1 - 2 * ((y + 0.5) / (float)HEIGHT)) * scale ;

    t_vector direction;

    // Subtract the camera's position from the pixel position
    direction.x = pixel_x - camera->vector.x;
    direction.y = pixel_y - camera->vector.y;
    direction.z = 1 - camera->vector.z;

	static int show = 0;

    normilized(&direction);
	if (show == 0)
	{
		printf("Camera vector:\n");
		printf("\tx: %f\n", camera->vector.x);
		printf("\ty: %f\n", camera->vector.y);
		printf("\tz: %f\n", camera->vector.z);
		printf("pixel_x: %f\n", pixel_x);
		printf("pixel_y: %f\n", pixel_y);
		printf("direction.x: %f\n", direction.x);
		printf("direction.y: %f\n", direction.y);
		printf("direction.z: %f\n", direction.z);
		show = 1;
	}
    return direction;
}