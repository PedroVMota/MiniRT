/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParaboloidColision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:23:16 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 15:23:26 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

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