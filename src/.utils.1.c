/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .utils.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:36:02 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/13 19:56:27 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

void	lights(Light *l, Light **lst)
{
	Light	*head;

	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while (*lst && (*lst)->next)
		(*lst) = (Object *)(*lst)->next;
	(*lst)->next = l;
	*lst = head;
}

void	objects(Object *l, Object **lst)
{
	Object	*head;

	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = l;
	*lst = head;
}

void	camera(Camera *l, Camera **lst)
{
	Camera	*head;

	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while ((*lst)->next)
		(*lst) = (Camera *)(*lst)->next;
	(*lst)->next = l;
	*lst = head;
}

void	objectadd(Object *nObj, void **list)
{
	if (!nObj)
		return ;
	if (nObj->type == POINT || nObj->type == AMBIENT)
		lights((Light *)nObj, (Light **)list);
	else if (nObj->type == CAMERA)
		camera((Camera *)nObj, (Camera **)list);
	else if (nObj->type == SPHERE || nObj->type == PLANE || \
	nObj->type == CYLINDER || nObj->type == PARABOLOID)
		objects(nObj, (Object **)list);
}

void	del(Object **lsg)
{
	if (!lsg)
		return ;
	if (!*lsg)
		return ;
	del(&(*lsg)->next);
	free(*lsg);
	*lsg = NULL;
}
