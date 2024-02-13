/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloidUtils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:02:24 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 14:58:29 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

bool	iswithintopdisk(Paraboloid *paraboloid, Vec3 intersection)
{
	double	rmax;
	double	dx;
	double	dy;
	double	distance;

	rmax = paraboloid->diameter / 2;
	dx = intersection.x - paraboloid->o.x;
	dy = intersection.y - paraboloid->o.y;
	distance = sqrt (dx * dx + dy * dy);
	return (intersection.z >= paraboloid->height && distance <= rmax);
}

bool	iswithinbounds(Paraboloid *paraboloid, Vec3 intersection)
{
	double	zmin;
	double	zmax;

	zmin = 10;
	zmax = 10000;
	return (intersection.z >= zmin && intersection.z <= zmax);
}

tValues	calculatevaluespbld(Paraboloid *paraboloid, Ray ray)
{
	tValues	t;
	Vec3	oc;
	double	a;
	double	b;
	double	c;

	oc = sub(ray.o, paraboloid->o);
	a = pow(ray.d.x, 2) / pow(paraboloid->diameter, 2) + pow(ray.d.y, 2) \
	/ pow(paraboloid->height, 2);
	b = 2 * (ray.d.x * oc.x / pow(paraboloid->diameter, 2) + ray.d.y * oc.y \
	/ pow(paraboloid->height, 2) - ray.d.z);
	c = pow(oc.x, 2) / pow(paraboloid->diameter, 2) + pow(oc.y, 2) \
	/ pow(paraboloid->height, 2) - oc.z;
	t = quadraticsolver(a, b, c);
	return (t);
}
