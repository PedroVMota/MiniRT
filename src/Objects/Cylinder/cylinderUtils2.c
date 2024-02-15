/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinderUtils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:59:06 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/15 11:32:50 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_values	calculatebotplanecolision(t_ray ray, t_cy *cylinder)
{
	t_vector	botcenter;

	botcenter = cylinder->o;
	return (planecolisioncylinder(botcenter, cylinder->d, ray, \
	cylinder->diameter / 2));
}

t_values	calculateplanecolisions(t_ray ray, t_cy *cylinder)
{
	t_values	top;
	t_values	bot;
	t_values	result;

	top = calculatetopplanecolision(ray, cylinder);
	bot = calculatebotplanecolision(ray, cylinder);
	result.t0 = minval(top.t0, bot.t0);
	result.t1 = INFINITY;
	return (result);
}

t_vector	calculatenormalone(t_values t, t_vector p1, t_cy *cylinder)
{
	t_vector	normal;
	double		dotc;

	normal = sub(p1, cylinder->o);
	dotc = dot(normal, cylinder->d);
	(void)t;
	return (norm(sub(normal, mul(cylinder->d, dotc))));
}

t_vector	calculatenormaltwo(t_values t, t_vector p2, t_cy *cylinder)
{
	t_vector	normal;
	double		dotc;

	normal = sub(p2, cylinder->o);
	dotc = dot(normal, cylinder->d);
	(void)t;
	return (norm(sub(normal, mul(cylinder->d, dotc))));
}

t_values	calculatenormals(t_values t, t_vector p1, t_vector p2,
	t_cy *cylinder)
{
	t_values	result;

	result.t0 = t.t0;
	result.t1 = t.t1;
	result.normal0 = calculatenormalone(t, p1, cylinder);
	result.normal1 = calculatenormaltwo(t, p2, cylinder);
	return (result);
}
