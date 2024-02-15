/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:26:52 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/15 16:15:25 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_vec4	mul4(t_vec4 a, double b)
{
	t_vec4	result;

	result.r = a.r * b;
	result.g = a.g * b;
	result.b = a.b * b;
	return (result);
}

t_vector	reflect(t_vector incident, t_vector normal)
{
	return (sub(incident, mul(normal, 2 * dot(incident, normal))));
}

t_vector	rotate(t_vector point, t_vector axis, double angle)
{
	double		costheta;
	double		sintheta;
	t_vector	u;
	t_vector	rotatedpoint;

	costheta = cos(angle);
	sintheta = sin(angle);
	u = norm(axis);
	rotatedpoint.x = (costheta + u.x * u.x * (1 - costheta)) * point.x \
	+ (u.x * u.y * (1 - costheta) - u.z * sintheta) * point.y \
	+ (u.x * u.z * (1 - costheta) + u.y * sintheta) * point.z;
	rotatedpoint.y = (u.y * u.x * (1 - costheta) + u.z * sintheta) * point.x \
	+ (costheta + u.y * u.y * (1 - costheta)) * point.y \
	+ (u.y * u.z * (1 - costheta) - u.x * sintheta) * point.z;
	rotatedpoint.z = (u.z * u.x * (1 - costheta) - u.y * sintheta) * point.x \
	+ (u.z * u.y * (1 - costheta) + u.x * sintheta) * point.y \
	+ (costheta + u.z * u.z * (1 - costheta)) * point.z;
	return (rotatedpoint);
}
