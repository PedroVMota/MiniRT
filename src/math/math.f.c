/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 04:44:42 by pedro             #+#    #+#             */
/*   Updated: 2023/12/29 02:42:36 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void normilized(t_vector *vector)
{
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
	return (t_values){
		((-b - sqrt(discriminant)) / (2 * a)),
		((-b + sqrt(discriminant)) / (2 * a))};
}

/// @param x Pixel X axis position
/// @param y Pixel Y axis position
/// @return return a (x,y,z) vector direction.
t_vector get_ray_direction(t_camera *camera, int x, int y)
{
	t_vector direction;
	float pixel_x;
	float pixel_y;

	pixel_x = (2 * ((x + 0.5) / (float)WIDTH) - 1) * scene()->aspect_ratio * scene()->scale;
	pixel_y = (1 - 2 * ((y + 0.5) / (float)HEIGHT)) * scene()->scale;
	direction.x = pixel_x - camera->vector.x;
	direction.y = pixel_y - camera->vector.y;
	direction.z = 1 - camera->vector.z;
	// normilized(&direction);
	return direction;
}