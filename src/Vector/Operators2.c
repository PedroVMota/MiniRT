/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:18:23 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/14 20:55:14 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_vector	mul(t_vector a, double b)
{
	return ((t_vector){a.x * b, a.y * b, a.z * b});
}

t_vector	divv(t_vector a, double b)
{
	return ((t_vector){a.x / b, a.y / b, a.z / b});
}

t_vector	unitvector(t_vector v)
{
	double	l;

	l = len(v);
	return ((t_vector){v.x / l, v.y / l, v.z / l});
}

t_vector	cross(t_vector a, t_vector b)
{
	return ((t_vector){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, \
	a.x * b.y - a.y * b.x});
}

t_vec4	add4(t_vec4 a, t_vec4 b)
{
	t_vec4	result;

	result.r = minval(a.r + b.r, 255);
	result.g = minval(a.g + b.g, 255);
	result.b = minval(a.b + b.b, 255);
	return (result);
}
