/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:04:30 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/14 20:54:24 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	len(t_vector v)
{
	return (sqrt(dot(v, v)));
}

t_vector	norm(t_vector v)
{
	double	nor;

	nor = len(v);
	return ((t_vector){v.x / nor, v.y / nor, v.z / nor});
}

t_vector	add(t_vector a, t_vector b)
{
	return ((t_vector){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector	sub(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y, a.z - b.z});
}
