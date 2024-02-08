/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:48:47 by pedro             #+#    #+#             */
/*   Updated: 2024/02/08 11:39:02 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

/// @brief Create a new color
/// @param r  The red component of the color
/// @param g  The green component of the color
/// @param b  The blue component of the color
/// @return The new color
int	newrgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

/// @brief Multiply a color component by an intensity
/// @param color  The color to be modified
/// @param shifting  The shifting of the color
/// @param intensity  The intensity to be multiplied
/// @return The new value of the color
double	mulcomp(int color, int shifting, double intensity)
{
	return ((color >> shifting & 255) * intensity);
}

/// @brief Multiply a color by an intensity
/// @param color  The color to be modified
/// @param intensity  The intensity to be multiplied
/// @return The new value of the color
int	colmul(int color, double intensity)
{
	int	r;
	int	g;
	int	b;

	r = mulcomp(color, 16, intensity);
	g = mulcomp(color, 8, intensity);
	b = mulcomp(color, 0, intensity);
	return (newrgb(r, g, b));
}

/// @brief Put a pixel in the screen
/// @param x  The x coordinate of the pixel
/// @param y  The y coordinate of the pixel
/// @param rgb  The color of the pixel
void	my_mlx_pixel_put(double x, double y, int rgb)
{
	char	*dst;

	dst = g_scene->mlx->addr + (((int)y) * \
		g_scene->mlx->line_length + ((int)x) * \
		(g_scene->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = rgb;
}

/// @brief Convert a coordinate to the canvas
/// @param combined  The combined color
/// @param light_color  The color of the light
/// @param brightness The brightness of the light
void calc_combined(Vec4 *combined, int light_color, double brightness)
 {
	combined->r += mulcomp(light_color, 16, brightness) / 255;
	combined->g += mulcomp(light_color, 8, brightness) / 255;
	combined->b += mulcomp(light_color, 0, brightness) / 255;
}