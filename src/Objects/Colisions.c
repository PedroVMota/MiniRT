/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colisions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:06:59 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 19:22:32 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

tValues	spherecolision(struct Object *s, Ray raydata)
{
	tValues	t;
	Vec3	oc;
	Sphere	*sphere;

	sphere = (Sphere *)s;
	oc = sub(raydata.o, sphere->o);
	t = quadraticsolver(dot(raydata.d, raydata.d), 2 * dot(oc, raydata.d), \
	dot(oc, oc) - (sphere->diameter));
	return (t);
}

tValues	planecolision(Plane *plane, Ray ray)
{
	double	numerator;
	tValues	t;

	numerator = 0;
	numerator = plane->d.x * (ray.o.x - plane->o.x);
	numerator += plane->d.y * (ray.o.y - plane->o.y);
	numerator += plane->d.z * (ray.o.z - plane->o.z);
	numerator *= -1;
	t.t0 = numerator / (plane->d.x * \
		ray.d.x + plane->d.y * \
		ray.d.y + plane->d.z * \
		ray.d.z);
	t.t1 = 0;
	return (t);
}

tValues	cylindercolision(Cylinder *cylinder, Ray ray)
{
	Vec3	oc;
	tValues	t;
	Vec3	p1;
	Vec3	p2;
	tValues	planecolisions;

	oc = sub(ray.o, cylinder->o);
	t = calculatetvalues(oc, ray, cylinder);
	p1 = add(ray.o, mul(ray.d, t.t0));
	p2 = add(ray.o, mul(ray.d, t.t1));
	checkheight(&t, p1, p2, cylinder);
	planecolisions = calculateplanecolisions(ray, cylinder);
	t.t0 = minval(t.t0, planecolisions.t0);
	return (calculatenormals(t, p1, p2, cylinder));
}

tValues	paraboloidcollision(Paraboloid *paraboloid, Ray ray)
{
	tValues	t;
	Vec3	intersection1;
	Vec3	intersection2;

	t = calculatevaluespbld(paraboloid, ray);
	intersection1 = add(ray.o, mul(ray.d, t.t0));
	intersection2 = add(ray.o, mul(ray.d, t.t1));
	if (!iswithinbounds(paraboloid, intersection1) || \
	iswithintopdisk(paraboloid, intersection1))
		t.t0 = -1;
	if (!iswithinbounds(paraboloid, intersection2) || \
	iswithintopdisk(paraboloid, intersection2))
		t.t1 = -1;
	return (t);
}
