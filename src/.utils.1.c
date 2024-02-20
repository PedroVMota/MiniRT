/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .utils.1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:36:02 by psoares-          #+#    #+#             */
/*   Updated: 2024/02/20 00:56:15 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "center.h"

void	lights(t_li *l, t_li **lst)
{
	t_li	*head;

	printf("ADDRESS\n\n\n");
	printf("%p\n", l);
	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while (*lst && (*lst)->next)
		(*lst) = (t_li *)(*lst)->next;
	(*lst)->next = l;
	*lst = head;
}

void	objects(t_obj *l, t_obj **lst)
{
	t_obj	*head;

	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while ((*lst)->next)
		(*lst) = ((t_obj *)(*lst)->next);
	(*lst)->next = l;
	*lst = head;
}

void	camera(t_cam *l, t_cam **lst)
{
	t_cam	*head;

	head = *lst;
	if (!*lst)
	{
		*lst = l;
		return ;
	}
	while ((*lst)->next)
		(*lst) = (t_cam *)(*lst)->next;
	(*lst)->next = l;
	*lst = head;
}

void	oadd(t_obj *nObj, void **list)
{
	if (!nObj)
		return ;
	if (nObj->type == POINT || nObj->type == AMBIENT)
		lights((t_li *)nObj, (t_li **)list);
	else if (nObj->type == CAMERA)
		camera((t_cam *)nObj, (t_cam **)list);
	else if (nObj->type == SPHERE || nObj->type == PLANE || \
	nObj->type == CYLINDER || nObj->type == PARABOLOID)
		objects(nObj, (t_obj **)list);
}

void	del(t_obj **lsg)
{
	if (!lsg)
		return ;
	if (!*lsg)
		return ;
	del(&(*lsg)->next);
	free(*lsg);
	*lsg = NULL;
}
