/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_function.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:15:09 by pedro             #+#    #+#             */
/*   Updated: 2023/12/25 16:23:01 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MLX_FUNCTIONS_H
#define MLX_FUNCTIONS_H

#include <center.h>

int	convert_color_to_int(t_color *trgb);
void	my_mlx_pixel_put(int x, int y, t_color *color);
bool	initialize_mlx(void);
#endif