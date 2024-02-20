/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalcalc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:01:58 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/15 08:25:48 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static	t_vector	normalcalcutilsone(t_obj *obj, t_vector p)
{
	t_vector	normal;

	normal = (t_vector){0, 0, 0};
	if (!obj)
		return (normal);
	if (obj->type == SPHERE)
	{
		normal = sub(p, (obj)->o);
		normal = norm(normal);
	}
	else if (obj->type == PLANE)
		normal = ((t_pl *)obj)->d;
	return (normal);
}

static	t_vector	normalcalccylinder(t_obj *obj, t_vector p)
{
	t_vector		normal;
	t_cy			*c;
	t_vector		oc;
	double			t;

	normal = (t_vector){0, 0, 0};
	if (!obj || obj->type != CYLINDER)
		return (normal);
	c = (t_cy *)obj;
	oc = sub(p, c->o);
	t = dot(oc, c->d);
	if (t < 0.001 || t > c->height - 0.001)
		normal = (c->d);
	else
	{
		normal = sub(oc, mul(c->d, t));
		normal = norm(normal);
	}
	return (normal);
}

static	t_vector	normalcalcparaboloid(t_obj *obj, t_vector p)
{
	t_vector		normal;
	t_pa			*paraboloid;
	t_vector		op;

	normal = (t_vector){0, 0, 0};
	if (!obj || obj->type != PARABOLOID)
		return (normal);
	paraboloid = (t_pa *)obj;
	op = sub(p, paraboloid->o);
	normal = (t_vector){2 * op.x, 2 * op.y, -1};
	normal = norm(normal);
	return (normal);
}

t_vector	normalcalc(t_obj *obj, t_vector p)
{
	t_vector	normal;

	normal = normalcalcutilsone(obj, p);
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
		normal = normalcalccylinder(obj, p);
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
		normal = normalcalcparaboloid(obj, p);
	return (normal);
}
