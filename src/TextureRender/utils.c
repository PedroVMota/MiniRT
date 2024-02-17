/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:12:42 by pedro             #+#    #+#             */
/*   Updated: 2024/02/16 19:43:40 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_vec4 vec4_multiply(t_vec4 v1, t_vec4 v2) {
    t_vec4 result;
    result.r = v1.r * v2.r;
    result.g = v1.g * v2.g;
    result.b = v1.b * v2.b;
    return result;
}

t_vec4 vec4_normalize(t_vec4 v) {
    double len = sqrt(v.r * v.r + v.g * v.g + v.b * v.b);
    t_vec4 result;
    result.r = v.r / len;
    result.g = v.g / len;
    result.b = v.b / len;
    return result;
}

t_vec4	checkerboardcolor(t_vector point,
	t_vec4 color1, t_vec4 color2, double size)
{
	if ((int)(floor(point.x / size) + floor(point.y / size) + floor(point.z \
				/ size)) % 2 == 0)
		return (color1);
	else
		return (color2);
}

int vec4_to_int(t_vec4 color)
{
    int r = (int)(color.r) & 0xFF;
    int g = (int)(color.g) & 0xFF;
    int b = (int)(color.b ) & 0xFF;

    return  (r << 16) | (g << 8) | b;
}

int vec4_to_inttest(t_vec4 color)
{
    int r = (int)(color.r * 255) & 0xFF;
    int g = (int)(color.g * 255) & 0xFF;
    int b = (int)(color.b * 255) & 0xFF;

    return  (r << 16) | (g << 8) | b;
}

t_vec4 int_to_vec4(int color)
{
    t_vec4 vec;
    vec.r = (color >> 16) & 0xFF;
    vec.g = (color >> 8) & 0xFF;
    vec.b = color & 0xFF;
    return vec;
}

int checkerboard_logic2(t_ray rayTrace, t_obj *obj, int lc, t_vec4 light)
{
    if (obj->type == SPHERE) 
    {
        t_sp *sphere = (t_sp *)obj;
        if (sphere->checkerboard == 1)
        {
            t_vec4 color1 = int_to_vec4(sphere->color); // Red
            t_vec4 color2 = {0, 0, 0}; // Green
            double size = 1;

            t_vec4 checkerboard_color = checkerboardcolor(rayTrace._hit, color1, color2, size);
            checkerboard_color = vec4_multiply(checkerboard_color, light); // Apply light
            lc = vec4_to_int(checkerboard_color);
        }
		else if (sphere->checkerboard == 2)
        {
            t_vec4 color = sinwave(rayTrace, obj); // Apply the sinwave logic

            color = vec4_multiply(color, light);
            lc = compcolor(lc, light);
        }
        else{
            lc = compcolor(obj->color, light);
        }
    }
    // Similar checks for CYLINDER, PLANE, and PARABOLOID...
    return lc;
}



int checkerboard_logic(t_ray rayTrace, t_obj *obj, int lc, t_vec4 light)
{
    

    if (obj->type == PLANE)
    {
        t_pl *plane = (t_pl *)obj;
        if (plane->checkerboard == 1)
        {
            t_vec4 color1 = int_to_vec4(plane->color); // Red
            t_vec4 color2 = {0, 0, 0}; // Green
            double size = 1;

            t_vec4 checkerboard_color = checkerboardcolor(rayTrace._hit, color1, color2, size);
            checkerboard_color = vec4_multiply(checkerboard_color, light); // Apply light
            lc = vec4_to_int(checkerboard_color);
        }
        else if (plane->checkerboard == 2) {
            t_vec4 color = sinwave(rayTrace, obj); // Apply the sinwave logic
            color = add4(color, light); // Apply light
            lc = vec4_to_inttest(color);
        }
        else{
            lc = compcolor(plane->color, light);
        }
    }
    if (obj->type == SPHERE)
	    lc = checkerboard_logic2(rayTrace, obj,lc, light);
    // Similar checks for CYLINDER, PLANE, and PARABOLOID...
    return lc;
}
