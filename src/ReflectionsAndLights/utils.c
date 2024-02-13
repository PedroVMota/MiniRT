/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:03:09 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/12 17:06:33 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static void	setdata(Object *obj, Ray *ray)
{
	ray->normal = normalcalc(obj, add(ray->o, mul(ray->d, ray->ct)));
	ray->_hit = add(ray->o, mul(ray->d, ray->ct));
}

Vec3	reflect_ray(Vec3 light, Vec3 normal)
{
	Vec3	result;
	double	dot_product;

	dot_product = normal.x * light.x + normal.y * light.y + normal.z * light.z;
	result.x = light.x - 2 * normal.x * dot_product;
	result.y = light.y - 2 * normal.y * dot_product;
	result.z = light.z - 2 * normal.z * dot_product;
	return (result);
}

int	shadow(Vec3 origin, Vec3 dir, double t_min, double t_max)
{
	Object *list;
	double ct;
	tValues val;
	Ray ray;

	ct = INFINITY;
	list = g_scene->objects;
	while (list)
	{
		ray.o = origin;
		ray.d = norm(dir);
		val = list->colision(list, ray);
		if ((val.t0 > t_min && val.t0 < t_max) && val.t0 < ct)
			return (1);
		if ((val.t1 > t_min && val.t1 < t_max) && val.t1 < ct)
			return (1);
		list = list->next;
	}

	return (0);
}

Object	*intersections(Ray *rt, double md, double d, bool set)
{
	Object	*closest;
	Object	*o;

	rt->ct = INFINITY;
	closest = NULL;
	o = g_scene->objects;
	while (o)
	{
		//printf("o->type: %d\n", o->type);
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
		o = o->next;
	}
	if (set)
		setdata(closest, rt);
	return (closest);
}
