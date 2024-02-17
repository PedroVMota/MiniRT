/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:12:42 by pedro             #+#    #+#             */
/*   Updated: 2024/02/17 20:43:46 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

/**
 * Multiplies two vec4 vectors component-wise.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The resulting vector after the multiplication.
 */
t_vec4	vec4_multiply(t_vec4 v1, t_vec4 v2){
	t_vec4	result;

	result.r = v1.r * v2.r;
	result.g = v1.g * v2.g;
	result.b = v1.b * v2.b;
	return (result);
}

/**
 * Adds two vec4 vectors component-wise.
 *
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return The resulting vector after the addition.
 */
t_vec4	vec4_normalize(t_vec4 v){
	double	len;
	t_vec4	result;

	len = sqrt(v.r * v.r + v.g * v.g + v.b * v.b);
	result.r = v.r / len;
	result.g = v.g / len;
	result.b = v.b / len;
	return (result);
}


/**
 * checkboard color
 *
 * @param point The first vector.
 * @param color1 The second vector.
 * @param color2 The second vector.
 * @param size The second vector.
 * @return The resulting vector after the addition.
 */
t_vec4	checkerboardcolor(t_vector point, t_vec4 color1, t_vec4 color2,
		double size)
{
	if ((int)(floor(point.x / size) + floor(point.y / size) + floor(point.z
				/ size)) % 2 == 0)
		return (color1);
	else
		return (color2);
}


/**
 * Converts a vec4 to an int.
 *
 * @param color The color to convert.
 * @return The resulting int.
 */
int	vec4_to_int(t_vec4 color){
	int	r;
	int	g;
	int	b;

	r = (int)(color.r) & 0xFF;
	g = (int)(color.g) & 0xFF;
	b = (int)(color.b) & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

/**
 * Converts a vec4 to an int.
 *
 * @param color The color to convert.
 * @return The resulting int.
 */
int	vec4_to_inttest(t_vec4 color){
	int	r;
	int	g;
	int	b;

	r = (int)(color.r * 255) & 0xFF;
	g = (int)(color.g * 255) & 0xFF;
	b = (int)(color.b * 255) & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

/**
 * Converts an int to a vec4.
 *
 * @param color The color to convert.
 * @return The resulting vec4.
 */
t_vec4	int_to_vec4(int color){
	t_vec4	vec;

	vec.r = (color >> 16) & 0xFF;
	vec.g = (color >> 8) & 0xFF;
	vec.b = color & 0xFF;
	return (vec);
}


int	checkerboard_logic(t_ray rayTrace, t_obj *obj, t_vec4 light)
{
	if (obj->checkerboard == 1)
	{
		t_vec4 checkerboard_color = checkerboardcolor(rayTrace._hit, int_to_vec4(obj->color),
				(t_vec4){0,0,0}, 0.5);
		checkerboard_color = vec4_multiply(checkerboard_color, light);
		return (vec4_to_int(checkerboard_color));
	}
	if(obj->checkerboard == 2)
	{
		t_vec4 checkerboard_color = checkerboardcolor(rayTrace._hit, (t_vec4){0,0,0},
				(t_vec4){150,150,150}, 0.001);
		checkerboard_color = vec4_multiply(checkerboard_color, light);
		return (vec4_to_int(checkerboard_color));
	}
	return (vec4_to_int(vec4_multiply(int_to_vec4(obj->color), light)));
}