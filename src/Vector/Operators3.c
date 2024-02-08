/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:26:52 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 00:33:57 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

Vec4	mul4(Vec4 a, double b)
{
	Vec4	result;

	result.r = a.r * b;
	result.g = a.g * b;
	result.b = a.b * b;
	return (result);
}

Vec3	reflect(Vec3 incident, Vec3 normal)
{
	return (sub(incident, mul(normal, 2 * dot(incident, normal))));
}

Vec3	rotate(Vec3 point, Vec3 axis, double angle)
{
	double	costheta;
	double	sintheta;
	Vec3	u;
	Vec3	rotatedpoint;

	costheta = cos(angle);
	sintheta = sin(angle);
	u = normalize(axis);
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
