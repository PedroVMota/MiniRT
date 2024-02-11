/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:14:30 by pedro             #+#    #+#             */
/*   Updated: 2024/02/08 11:33:52 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StandarLibrarys.h>

Vec3	reflect_ray(Vec3 light, Vec3 normal);

double	to_reflect(Vec3 light, Vec3 n, Vec3 vect, Vec3 *reflected)
{
	double	r_dot_v;

	*reflected = reflect_ray(light, n);
	r_dot_v = reflected->x * vect.x + reflected->y * vect.y + reflected->z
		* vect.z;
	return (r_dot_v);
}

Vec4	limit(Vec4 v)
{
	if (v.r > 1)
		v.r = 1;
	if (v.g > 1)
		v.g = 1;
	if (v.b > 1)
		v.b = 1;
	if (v.r < 0)
		v.r = 0;
	if (v.g < 0)
		v.g = 0;
	if (v.b < 0)
		v.b = 0;
	return (v);
}

int	skip(Light **l)
{
	*l = (Light *)(*l)->next;
	return (1);
}
