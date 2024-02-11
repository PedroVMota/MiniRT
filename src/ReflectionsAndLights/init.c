/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:18:22 by pedro             #+#    #+#             */
/*   Updated: 2024/02/08 11:39:02 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StandarLibrarys.h>

double	refl(Vec3 data, Vec3 reflected, Vec3 vect)
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

void	diffusion(Vec4 *combined, Vec3 normal, Vec3 light, Light *src)
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

Vec4	calcligh(Vec3 p, Vec3 n, Vec3 v, double spec)
{
	Vec4	c;
	double	rdv;
	Light	*l;
	Vec3	pvl;
	Vec3	reflected;

	c = (Vec4){0, 0, 0};
	l = g_scene->lights;
	calc_combined(&c, g_scene->am->color, g_scene->am->i);
	while (l)
	{
		printf("%p and %p\n", l, l->next);
		pvl = sub(l->o, p);
		if (shadow(p, norm(pvl), 0.001, 1) && skip(&l))
			continue ;
		diffusion(&c, n, pvl, l);
		rdv = to_reflect(l->o, n, v, &reflected);
		if (spec > 0 && rdv > 0)
			calc_combined(&c, l->color, refl((Vec3){(l->i / (len(pvl) * \
				len(pvl))), rdv, spec}, reflected, v));
		l = (Light *)l->next;
	}
	return (limit(c));
}
