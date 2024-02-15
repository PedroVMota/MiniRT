/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlaneColision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:22:07 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 15:22:14 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

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