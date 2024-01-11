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
	unsigned int r = color->r * 255.0f;
	unsigned int g = color->g * 255.0f;
	unsigned int b = color->b * 255.0f;
	return (0 << 24 | r << 16 | g << 8 | b);
}
static void clamp(t_color *color)
{
	if(color->r < 0.0f)
		color->r = 0.0f;
	if(color->g < 0.0f)
		color->g = 0.0f;
	if(color->b < 0.0f)
		color->b = 0.0f;
	if(color->r > 1.0f)
		color->r = 1.0f;
	if(color->g > 1.0f)
		color->g = 1.0f;
	if(color->b > 1.0f)
		color->b = 1.0f;
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

	clamp(&color);
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
