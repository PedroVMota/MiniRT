/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:12:42 by pedro             #+#    #+#             */
/*   Updated: 2024/02/13 19:46:02 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

Vec4	checkerboardcolor(Vec3 point, Vec4 color1, Vec4 color2, double size)
{
	if ((int)(floor(point.x / size) + floor(point.y / size) + floor(point.z \
				/ size)) % 2 == 0)
		return (color1);
	else
		return (color2);
}
