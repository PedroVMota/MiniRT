/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:14:25 by pedro             #+#    #+#             */
/*   Updated: 2023/12/25 23:53:44 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_function.h>

/// @brief Creates a trgb color
/// @param color The color to be converted
/// @return The trgb color
int	convert_color_to_int(t_color *color)
{

	return (0 << 24 | color->r << 16 | color->g << 8 | color->b);
}

/// @brief Puts a pixel on the screen
/// @param x X Pixel
/// @param y Y Pixel
/// @param color Color struct that will be converted to int
void	my_mlx_pixel_put(int x, int y, t_color color)
{
	char	*dst;

	dst = scene()->mlx_data->addr + (y * scene()->mlx_data->line_length + x * (scene()->mlx_data->bits_per_pixel
				/ 8));
	color.r = Min(255, Max(color.r, 0));
	color.g = Min(255, Max(color.g, 0));
	color.b = Min(255, Max(color.b, 0));


	*(unsigned int *)dst = convert_color_to_int(&color);
}

/// @brief  Initializes the mlx library
/// @return  true if the initialization was successful, false otherwise
bool	initialize_mlx(void)
{
	scene()->mlx_data->mlx = mlx_init();
	scene()->mlx_data->win = mlx_new_window(scene()->mlx_data->mlx, WIDTH,HEIGHT, "miniRT");
	scene()->mlx_data->img = mlx_new_image(scene()->mlx_data->mlx, WIDTH,HEIGHT);
	scene()->mlx_data->addr = mlx_get_data_addr(scene()->mlx_data->img, &scene()->mlx_data->bits_per_pixel,
			&scene()->mlx_data->line_length, &scene()->mlx_data->endian);
	scene()->mutex  = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(scene()->mutex, NULL);
	return (true);
}
