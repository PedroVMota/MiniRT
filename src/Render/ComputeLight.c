/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ComputeLight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:18:22 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 14:21:44 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

int	shadow(t_vector origin, t_vector dir, double t_min, double t_max)
{
	t_obj		*list;
	t_values	val;
	t_ray		ray;

	list = g_scene->objects;
	while (list)
	{
		ray.o = origin;
		ray.d = norm(dir);
		val = list->colision(list, ray);
		if (val.t0 > t_min && val.t0 < t_max)
			return (1);
		if (val.t1 > t_min && val.t1 < t_max)
			return (1);
		list = (t_obj *)list->next;
	}
	return (0);
}

double	refl(t_vector data, t_vector reflected, t_vector vect)
{
	double	bright;
	double	length_reflected;
	double	length_vect;

	length_reflected = sqrt(reflected.x * reflected.x + reflected.y * \
	reflected.y + reflected.z * reflected.z);
	length_vect = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
	bright = data.x * pow(data.y / (length_reflected * length_vect), data.z);
	return (bright);
}

void	diffusion(t_vec4 *combined, t_vector normal, t_vector light, t_li *src)
{
	double	n_dot_l;
	double	bright;

	n_dot_l = dot(normal, light);
	if (n_dot_l > 0)
	{
		bright = src->i * n_dot_l / (len(normal) * len(light));
		calc_combined(combined, src->color, bright);
	}
}

t_vec4	calcligh(t_vector p, t_vector n, t_vector v, int spec)
{
	t_vec4		c;
	double		rdv;
	t_li		*l;
	t_vector	pvl;
	t_vector	reflected;

	c = (t_vec4){0, 0, 0};
	l = g_scene->lights;
	calc_combined(&c, g_scene->am->color, g_scene->am->i);
	while (l)
	{
		pvl = sub(l->o, p);
		if (shadow(p, pvl, 0.001, len(pvl)) && skip(&l))
			continue ;
		diffusion(&c, n, pvl, l);
		rdv = to_reflect(l->o, n, v, &reflected);
		if (spec > 0 && rdv > 0)
			calc_combined(&c, l->color, refl((t_vector){(l->i / (len(pvl) * \
				len(pvl))), rdv, spec}, reflected, v));
		l = (t_li *)l->next;
	}
	return (limit(c));
}
