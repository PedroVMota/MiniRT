/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colisions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 01:06:59 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/15 08:18:01 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_values	spherecolision(t_obj *s, t_ray raydata)
{
	t_values	t;
	t_vector	oc;
	t_sp		*sphere;

	sphere = (t_sp *)s;
	oc = sub(raydata.o, sphere->o);
	t = quadraticsolver(dot(raydata.d, raydata.d), 2 * dot(oc, raydata.d), \
	dot(oc, oc) - (sphere->diameter));
	return (t);
}

t_values	planecolision(t_pl *plane, t_ray ray)
{
	double		numerator;
	t_values	t;

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

t_values	cylindercolision(t_cy *cylinder, t_ray ray)
{
	t_vector	oc;
	t_values	t;
	t_vector	p1;
	t_vector	p2;
	t_values	planecolisions;

	oc = sub(ray.o, cylinder->o);
	t = calculatetvalues(oc, ray, cylinder);
	p1 = add(ray.o, mul(ray.d, t.t0));
	p2 = add(ray.o, mul(ray.d, t.t1));
	checkheight(&t, p1, p2, cylinder);
	planecolisions = calculateplanecolisions(ray, cylinder);
	t.t0 = minval(t.t0, planecolisions.t0);
	return (calculatenormals(t, p1, p2, cylinder));
}

t_values	paraboloidcollision(t_pa *paraboloid, t_ray ray)
{
	t_values	t;
	t_vector	intersection1;
	t_vector	intersection2;

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
