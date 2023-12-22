/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:43:14 by pvital-m          #+#    #+#             */
/*   Updated: 2023/12/22 18:43:34 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

/// @brief This function will add a element to the link list
/// @param object list
void	objectaddlast(t_object *object)
{
	t_object	*tmp;

	if (!scene()->objects)
	{
		scene()->objects = object;
		return ;
	}
	tmp = scene()->objects;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = object;
}

/// @brief Static Pointer of scene
/// @param  
/// @return 
t_scene	*scene(void)
{
	static t_scene	scene;

	return (&scene);
}
