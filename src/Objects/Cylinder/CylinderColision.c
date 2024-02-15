/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CylinderColision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:22:32 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 15:22:46 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

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