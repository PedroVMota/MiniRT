/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:12:42 by pedro             #+#    #+#             */
/*   Updated: 2024/02/16 18:02:11 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>


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

int checkerboard_logic2(t_ray rayTrace, t_obj *obj, int lc)
{
    if (obj->type == SPHERE) 
    {
        t_sp *sphere = (t_sp *)obj;
        if (sphere->checkerboard == 1)
        {
            t_vec4 color1 = int_to_vec4(sphere->color); // Red
            t_vec4 color2 = {0, 0, 0}; // Green
            double size = 0.0001;

            t_vec4 checkerboard_color = checkerboardcolor(rayTrace._hit, color1, color2, size);
            lc = vec4_to_int(checkerboard_color);
        }
		else if (sphere->checkerboard == 2)
		{
            t_vec4 color = sinwave(rayTrace, obj); // Apply the sinwave logic
        	lc = vec4_to_inttest(color);
        }
    }
    // Similar checks for CYLINDER, PLANE, and PARABOLOID...
    return lc;
}
int checkerboard_logic(t_ray rayTrace, t_obj *obj, int lc)
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
            lc = vec4_to_int(checkerboard_color);
        }
		else if (plane->checkerboard == 2) {
            t_vec4 color = sinwave(rayTrace, obj); // Apply the sinwave logic
        	lc = vec4_to_inttest(color);
        }
    }
    if (obj->type == SPHERE)
	    lc = checkerboard_logic2(rayTrace, obj,lc);
    // Similar checks for CYLINDER, PLANE, and PARABOLOID...
    return lc;
}
