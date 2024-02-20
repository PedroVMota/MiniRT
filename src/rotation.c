/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:47:06 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/14 20:54:24 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	rotation_x(double theta, t_vector *vec)
{
	double	temp;

	temp = vec->y;
	vec->y = vec->y * cos(theta) + vec->z * sin(theta);
	vec->z = -temp * sin(theta) + vec->z * cos(theta);
}

void	rotation_y(double theta, t_vector *vec)
{
	double	temp;

	temp = vec->x;
	vec->x = vec->x * cos(theta) + vec->z * sin(theta);
	vec->z = -temp * sin(theta) + vec->z * cos(theta);
}

void	rotation_z(double theta, t_vector *vec)
{
	double	temp;

	temp = vec->x;
	vec->x = vec->x * cos(theta) - vec->y * sin(theta);
	vec->y = temp * sin(theta) + vec->y * cos(theta);
}