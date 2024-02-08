/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:39:02 by pedro             #+#    #+#             */
/*   Updated: 2024/02/08 00:02:42 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

double	clamp(double n, double min, double max)
{
	if (n < min)
		return (min);
	if (n > max)
		return (max);
	return (n);
}

double	maxval(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	minval(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	tocanvas(double x, bool isheight)
{
	if (isheight)
		return ((double)scene->height / 2 - x);
	return (x + (double)scene->width / 2);
}
