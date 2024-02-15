/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SphereColision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:21:47 by pedro             #+#    #+#             */
/*   Updated: 2024/02/15 15:21:51 by pedro            ###   ########.fr       */
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