/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:39:02 by pedro             #+#    #+#             */
/*   Updated: 2024/02/05 21:47:17 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

double	randomlimited(double min, double max)
{
	return ((min + \
		(max - min) * \
		((rand() / (RAND_MAX + 1.0)) \
	)));
}

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

double	tocanvas(double x, bool isHeight)
{
	if (isHeight)
		return ((double)scene->height / 2 - x);
	return (x + (double)scene->width / 2);
}
