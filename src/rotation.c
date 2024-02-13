/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:47:06 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 19:49:59 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static	void	rotation_x(Vec3 *vec, Vec3 *theta)
{
	double	temp_z;
	double	temp_y;

	temp_z = vec->z;
	temp_y = vec->y;
	vec->y = temp_y * cos(theta->x) + temp_z * sin(theta->x);
	vec->z = -temp_y * sin(theta->x) + temp_z * cos(theta->x);
}

static	void	rotation_y(Vec3 *vec, Vec3 *theta)
{
	double	temp_x;
	double	temp_z;

	temp_x = vec->x;
	temp_z = vec->z;
	vec->x = temp_x * cos(theta->y) + temp_z * sin(theta->y);
	vec->z = -temp_x * sin(theta->y) + temp_z * cos(theta->y);
}

static	void	rotation_z(Vec3 *vec, Vec3 *theta)
{
	double	temp_x;
	double	temp_y;

	temp_x = vec->x;
	temp_y = vec->y;
	vec->x = temp_x * cos(theta->z) - temp_y * sin(theta->z);
	vec->y = temp_x * sin(theta->z) + temp_y * cos(theta->z);
}

void	rotation(Vec3 *v, Vec3 *theta)
{
	rotation_x(v, theta);
	rotation_y(v, theta);
	rotation_z(v, theta);
}
