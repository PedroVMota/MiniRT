/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalcalc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:01:58 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 19:57:58 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static	Vec3	normalcalcutilsone(Object *obj, Vec3 p)
{
	Vec3	normal;

	normal = (Vec3){0, 0, 0};
	if (!obj)
		return (normal);
	if (obj->type == SPHERE)
	{
		normal = sub(p, (obj)->o);
		normal = norm(normal);
	}
	else if (obj->type == PLANE)
		normal = ((Plane *)obj)->d;
	return (normal);
}

static	Vec3	normalcalccylinder(Object *obj, Vec3 p)
{
	Vec3		normal;
	Cylinder	*c;
	Vec3		oc;
	double		t;

	normal = (Vec3){0, 0, 0};
	if (!obj || obj->type != CYLINDER)
		return (normal);
	c = (Cylinder *)obj;
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

static	Vec3	normalcalcparaboloid(Object *obj, Vec3 p)
{
	Vec3		normal;
	Paraboloid	*paraboloid;
	Vec3		op;

	normal = (Vec3){0, 0, 0};
	if (!obj || obj->type != PARABOLOID)
		return (normal);
	paraboloid = (Paraboloid *)obj;
	op = sub(p, paraboloid->o);
	normal = (Vec3){2 * op.x, 2 * op.y, -1};
	normal = norm(normal);
	return (normal);
}

Vec3	normalcalc(Object *obj, Vec3 p)
{
	Vec3	normal;

	normal = normalcalcutilsone(obj, p);
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
		normal = normalcalccylinder(obj, p);
	if (normal.x == 0 && normal.y == 0 && normal.z == 0)
		normal = normalcalcparaboloid(obj, p);
	return (normal);
}
