/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:48:47 by pedro             #+#    #+#             */
/*   Updated: 2024/02/05 21:52:45 by pedro            ###   ########.fr       */
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

	dst = scene->mlx->addr + (((int)y) * \
		scene->mlx->line_length + ((int)x) * \
		(scene->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = rgb;
}
