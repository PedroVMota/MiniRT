/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:14:30 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 08:22:54 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_vector	reflect_ray(t_vector light, t_vector normal);

double	to_reflect(t_vector light, t_vector n, t_vector vect,
	t_vector *reflected)
{
	double	r_dot_v;

	*reflected = reflect_ray(light, n);
	r_dot_v = reflected->x * vect.x + reflected->y * vect.y + reflected->z
		* vect.z;
	return (r_dot_v);
}

t_vec4	limit(t_vec4 v)
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

int	skip(t_li **l)
{
	*l = (t_li *)(*l)->next;
	return (1);
}
