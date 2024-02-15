/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:12:42 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 08:22:14 by pedro            ###   ########.fr       */
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
