/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:43:14 by pvital-m          #+#    #+#             */
/*   Updated: 2024/01/25 20:47:56 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <center.h>

static void	addlastcamera(t_object **lst, t_object *new)
{
	t_object	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void	addlastlight(t_object **lst, t_object *new)
{
	t_object	*tmp;

	printf("Adding light\n");
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void	addlastobject(t_object **lst, t_object *new)
{
	t_object	*tmp;
	
	if(!new)
		return ;
	

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/// @brief This function will add a element to the link list
/// @param object list
void	objectaddlast(t_object *object)
{
	if (object->type == CAMERA)
	{
		addlastcamera(&scene()->camera, object);
	}
	if (object->type == POINT || object->type == AMBIENT)
		addlastlight(&scene()->lights, object);
	if (object->type == SPHERE || object->type == PLANE
		|| object->type == CYLINDER || object->type == CONE)
		addlastobject(&scene()->objects, object);
}

/// @brief Static Pointer of scene
/// @param
/// @return
t_scene	*scene(void)
{
	static t_scene	scene;

	return (&scene);
}
