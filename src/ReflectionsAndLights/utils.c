/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:03:09 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/08 11:39:02 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <StandarLibrarys.h>

static void	setdata(Object *obj, Ray *ray)
{
	ray->normal = normalcalc(obj, add(ray->o, mul(ray->d, ray->ct)));
	ray->HitPoint = add(ray->o, mul(ray->d, ray->ct));
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
	Object	*temp;
	tValues	t;

	t.t0 = INFINITY;
	t.t1 = INFINITY;
	temp = g_scene->objects;
	while (temp)
	{
		t = temp->colision(temp, (Ray){.o = origin, .d = dir});
		if (t.t0 > t_min && t.t0 < t_max)
			return (1);
		if (t.t1 > t_min && t.t1 < t_max)
			return (1);
		temp = temp->next;
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
		rt->val = spherecolision(o, *rt);
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
