/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:26:52 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/19 19:37:41 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

t_vec4	mul4(t_vec4 a, double b)
{
	t_vec4	result;

	result.r = a.r * b;
	result.g = a.g * b;
	result.b = a.b * b;
	return (result);
}

t_vector	reflect(t_vector incident, t_vector normal)
{
	return (sub(incident, mul(normal, 2 * dot(incident, normal))));
}
