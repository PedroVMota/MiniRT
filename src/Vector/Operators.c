/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:04:30 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 10:58:46 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

double	dot(Vec3 a, Vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	len(Vec3 v)
{
	return (sqrt(dot(v, v)));
}

Vec3	norm(Vec3 v)
{
	double	nor;

	nor = len(v);
	return ((Vec3){v.x / nor, v.y / nor, v.z / nor});
}

Vec3	add(Vec3 a, Vec3 b)
{
	return ((Vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

Vec3	sub(Vec3 a, Vec3 b)
{
	return ((Vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}
