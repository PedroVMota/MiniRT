/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CameraRotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:25:38 by pedro             #+#    #+#             */
/*   Updated: 2024/02/18 10:26:20 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	rotx(double theta, t_vector *dir)
{
	double	temp;

	temp = dir->y;
	dir->y = dir->y * cos(theta) + dir->z * sin(theta);
	dir->z = -temp * sin(theta) + dir->z * cos(theta);
}

void	roty(double theta, t_vector *dir)
{
	double	temp;

	temp = dir->x;
	dir->x = dir->x * cos(theta) + dir->z * sin(theta);
	dir->z = -temp * sin(theta) + dir->z * cos(theta);
}

void	rot(t_vector theta, t_vector *viewport_pt)
{
	rotx(theta.x, viewport_pt);
	roty(theta.y, viewport_pt);
}
