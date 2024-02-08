/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:18:23 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 00:26:00 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

Vec3	mul(Vec3 a, double b)
{
	return ((Vec3){a.x * b, a.y * b, a.z * b});
}

Vec3	divv(Vec3 a, double b)
{
	return ((Vec3){a.x / b, a.y / b, a.z / b});
}

Vec3	unitvector(Vec3 v)
{
	double	len;

	len = length(v);
	return ((Vec3){v.x / len, v.y / len, v.z / len});
}

Vec3	cross(Vec3 a, Vec3 b)
{
	return ((Vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, \
	a.x * b.y - a.y * b.x});
}

Vec4	add4(Vec4 a, Vec4 b)
{
	Vec4	result;

	result.r = minval(a.r + b.r, 255);
	result.g = minval(a.g + b.g, 255);
	result.b = minval(a.b + b.b, 255);
	return (result);
}
