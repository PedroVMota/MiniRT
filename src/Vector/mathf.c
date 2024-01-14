/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 16:56:45 by pedro             #+#    #+#             */
/*   Updated: 2023/12/25 16:56:47 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"


/// @brief Dot Product Math
float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}


/// @brief Normilize Math
/// @param a 
void	normalized(t_vector *a)
{
	float	length;

	length = sqrt(dot(*a, *a));
	a->x /= length;
	a->y /= length;
	a->z /= length;
}

// Max 
float Max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}