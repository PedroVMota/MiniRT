/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:03:09 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/15 15:48:06 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static void	setdata(t_obj *obj, t_ray *ray)
{
	ray->normal = normalcalc(obj, add(ray->o, mul(ray->d, ray->ct)));
	ray->_hit = add(ray->o, mul(ray->d, ray->ct));
}

t_vector	reflect_ray(t_vector light, t_vector normal)
{
	t_vector	result;
	double		dot_product;

	dot_product = normal.x * light.x + normal.y * light.y + normal.z * light.z;
	result.x = light.x - 2 * normal.x * dot_product;
	result.y = light.y - 2 * normal.y * dot_product;
	result.z = light.z - 2 * normal.z * dot_product;
	return (result);
}

t_obj	*intersections(t_ray *rt, double md, double d, bool set)
{
	t_obj	*closest;
	t_obj	*o;

	rt->ct = INFINITY;
	closest = NULL;
	o = g_scene->objects;
	while (o)
	{
		rt->val = o->colision(o, *rt);
		if ((rt->val.t0 > d && rt->val.t0 < md) && rt->val.t0 < rt->ct)
		{
			closest = o;
			rt->ct = rt->val.t0;
		}
		else if ((rt->val.t1 > d && rt->val.t1 < md) && rt->val.t1 < rt->ct)
		{
			closest = o;
			rt->ct = rt->val.t1;
		}
		o = (t_obj *)o->next;
	}
	if (set)
		setdata(closest, rt);
	return (closest);
}

double	specular(t_vector data, t_vector reflected, t_vector vect)
{
	double	bright;
    double	distance = len(reflected);

    bright = (data.x / (distance * distance)) * \
            pow(data.y / (len(reflected) * len(vect)), \
            data.z);
    return (bright);
}