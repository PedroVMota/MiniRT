/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:04:30 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 00:27:25 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

double	dot(Vec3 a, Vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	length(Vec3 v)
{
	return (sqrt(dot(v, v)));
}

Vec3	normalize(Vec3 v)
{
	double	len;

	len = length(v);
	return ((Vec3){v.x / len, v.y / len, v.z / len});
}

Vec3	add(Vec3 a, Vec3 b)
{
	return ((Vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

Vec3	sub(Vec3 a, Vec3 b)
{
	return ((Vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}
