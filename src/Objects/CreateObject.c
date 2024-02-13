/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateObject.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:37:19 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 19:38:56 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	*object_error_handler(Object *obj, void **ptr, char *msg)
{
	if (g_scene->error)
	{
		if (msg)
			uptadeerror(msg);
		return (free(obj), NULL);
	}
	return ((void *)obj);
}

Object	*newobject(size_t targetsize, tValues (*colision)(struct Object *, Ray))
{
	Object	*obj;

	(obj) = ft_calloc(targetsize, 1);
	(obj)->colision = colision;
	(obj)->d = (Vec3){0, 0, 0};
	(obj)->next = NULL;
	return (obj);
}
