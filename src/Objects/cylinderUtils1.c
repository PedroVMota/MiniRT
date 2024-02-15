/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinderUtils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:58:48 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/15 11:32:07 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_values	quadraticsolver(double a, double b, double c)
{
	t_values		t;
	double			discriminant;

	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		t.t0 = (-b - sqrt(discriminant)) / (2 * a);
		t.t1 = (-b + sqrt(discriminant)) / (2 * a);
		return (t);
	}
	else
	{
		t.t0 = INFINITY;
		t.t1 = INFINITY;
	}
	return (t);
}

t_values	planecolisioncylinder(t_vector planep, t_vector planen, t_ray ray,
	double radius)
{
	t_values	t;
	double		denominador;
	double		numerator;
	t_vector	intersectionpoint;
	double		distance;

	denominador = dot(ray.d, planen);
	if (fabs(denominador) < 0.001)
	{
		t.t0 = INFINITY;
		t.t1 = INFINITY;
		return (t);
	}
	numerator = dot(sub(planep, ray.o), planen);
	t.t0 = numerator / denominador;
	t.t1 = INFINITY;
	intersectionpoint = add(ray.o, mul(ray.d, t.t0));
	distance = len(sub(intersectionpoint, planep));
	if (distance > radius)
		t.t0 = INFINITY;
	return (t);
}

t_values	calculatetvalues(t_vector oc, t_ray ray, t_cy *cylinder)
{
	double		radius;

	radius = cylinder->diameter / 2;
	return (quadraticsolver(dot(ray.d, ray.d) - dot(ray.d, cylinder->d) \
		* dot(ray.d, cylinder->d) \
		, 2 * (dot(ray.d, oc) - dot(ray.d, cylinder->d) * \
		dot(oc, cylinder->d)) \
		, dot(oc, oc) - dot(oc, cylinder->d) * dot(oc, cylinder->d) \
		- radius * radius));
}

void	checkheight(t_values *t, t_vector p1, t_vector p2, t_cy *cylinder)
{
	double	h1;
	double	h2;

	h1 = dot(sub(p1, cylinder->o), cylinder->d);
	h2 = dot(sub(p2, cylinder->o), cylinder->d);
	if (h1 < 0 || h1 > cylinder->height)
		t->t0 = INFINITY;
	if (h2 < 0 || h2 > cylinder->height)
		t->t1 = INFINITY;
}

t_values	calculatetopplanecolision(t_ray ray, t_cy *cylinder)
{
	t_vector	topcenter;

	topcenter = add(cylinder->o, mul(cylinder->d, cylinder->height));
	return (planecolisioncylinder(topcenter, cylinder->d, ray, \
	cylinder->diameter / 2));
}
