/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateObject.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:37:19 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/20 00:41:07 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

void	*errhandler(t_obj *obj, char *msg)
{
	if ((gscene())->error)
	{
		if (msg)
			uptadeerror(msg);
		return (free(obj), NULL);
	}
	return ((void *)obj);
}

t_obj	*newobject(size_t targetsize, t_values (*colision)(t_obj *, t_ray))
{
	t_obj	*obj;

	(obj) = ft_calloc(targetsize, 1);
	(obj)->colision = colision;
	(obj)->d = (t_vector){0, 0, 0};
	(obj)->next = NULL;
	return (obj);
}
